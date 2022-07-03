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
				lost = true;
				return;
			}

			// The move was successful! Save to our new state
			coordinate = temp;

			break;
		}
	}
}
