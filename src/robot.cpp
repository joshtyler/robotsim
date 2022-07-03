#include "robot.h"

// Check if another coordinate is inside the grid defined by us
bool Coordinate::is_inside(Coordinate other) const
{
	return !((other.x > x) || (other.y > y) || (other.x < 0) || (other.y < 0));
}


void Robot::act(Command c)
{
	// Don't take any action if we are lost
	if(lost)
	{
		return;
	}

	switch(c)
	{
		case Command::ROTATE_LEFT:
		{
			switch(orientation)
			{
				case Orientation::NORTH: orientation = Orientation::WEST; break;
				case Orientation::EAST: orientation = Orientation::NORTH; break;
				case Orientation::SOUTH: orientation = Orientation::EAST; break;
				case Orientation::WEST: orientation = Orientation::SOUTH; break;
			}
			break;
		}
		case Command::ROTATE_RIGHT:
		{
			switch(orientation)
			{
				case Orientation::NORTH: orientation = Orientation::EAST; break;
				case Orientation::EAST: orientation = Orientation::SOUTH; break;
				case Orientation::SOUTH: orientation = Orientation::WEST; break;
				case Orientation::WEST: orientation = Orientation::NORTH; break;
			}
			break;
		}
		case Command::MOVE_FORWARD:
		{
			// Unlike rotate left or rotate right, moving forward has the ability to push us off the grid
			// Therefore we need to see if we would be lost before acting
			auto temp = coordinate;
			switch(orientation)
			{
				case Orientation::NORTH: temp.y++; break;
				case Orientation::EAST:  temp.x++; break;
				case Orientation::SOUTH: temp.y--; break;
				case Orientation::WEST:  temp.x--; break;
			}

			// Check if this update would lose us
			// Don't commit to the new coordinate if so
			if(!grid_max.is_inside(temp))
			{
				// Has another robot got lost here?
				// If so, just ignore the command
				if(scent->is_scent_set(coordinate))
				{
					return;
				}

				// We are the first to get lost - leave our scent for others
				scent->set_scent(coordinate);
				lost = true;
				return;
			}

			// The move was successful! Save to our new state
			coordinate = temp;

			break;
		}
	}
}


size_t get_grid_perimeter_size(Coordinate c)
{
	// If you draw a grid on paper, it becomes quickly clear that the perimeter length
	// is x*y - (x-2)*(y-2)
	// I.e. the difference between the area, and the area of the inner grid
	// This also holds for the edge cases (i.e where there is no inner grid)
	// (if you clamp x-2 and y-2 at zero)

	const int WIDTH = c.x+1;
	const int HEIGHT = c.y+1;

	const int WIDTH_M2  = WIDTH-2  > 0? WIDTH-2:0;
	const int HEIGHT_M2 = HEIGHT-2 > 0? HEIGHT-2:0;

	return WIDTH*HEIGHT - WIDTH_M2*HEIGHT_M2;

}

ScentTracker::ScentTracker(Coordinate _grid_max)
	:grid_max(_grid_max), scent(get_grid_perimeter_size(grid_max),false)
{
}

size_t ScentTracker::get_scent_idx(Coordinate c) const
{
	// We need a consisent way to index our permiter vector
	// Paying attention to the corners - which would overlap if done naively
	// Therefore check if we are on each edge in order, and index from there

	const size_t WIDTH = (grid_max.x+1);
	const size_t HEIGHT = (grid_max.y+1);

	// If on the south edge, index using x coordinate directly
	if(c.y == 0) return c.x;

	// If on the east edge (but not in the SE corner), offset by the length of the bottom edge-1
	// Note the -1, because if we were in the SE corner, that would have been caught in the previous check
	if(c.x == grid_max.x) return WIDTH-1+c.y;

	// Likewise north edge
	// Note, now -2 to avoid double coutinting SE and NE corners
	if(c.y == grid_max.y) return WIDTH+HEIGHT-2+c.x;

	// Finally east edge
	// Now -3 to not double count SE, NE, and NWE corners
	if(c.x == 0) return WIDTH+HEIGHT+WIDTH-3+c.y;

	throw std::runtime_error("Attempt to set scent not on edge");
}
