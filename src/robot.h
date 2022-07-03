#ifndef ROBOT_H
#define ROBOT_H

#include <stdexcept>

// This stores the different possible orientations in a typesafe manner
enum class Orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum class Command
{
	ROTATE_LEFT,
	ROTATE_RIGHT,
	MOVE_FORWARD
};

// Hold a coordinate in our world grid
// The constructor ensures that the proposed x and y values are in-range according to the spec
static constexpr int MAX_COORD = 50;
struct Coordinate
{
	Coordinate(int _x, int _y)
	:x(_x), y(_y)
	{
		if(x > MAX_COORD || y > MAX_COORD || x < 0 || y < 0)
		{
			throw std::runtime_error("Attempt to construct coordinate with out of range value");
		}
	}
	int x;
	int y;
	// Check if another coordinate is inside the grid defined by us
	bool is_inside(Coordinate other) const;
};

struct Robot
{
	Robot(Coordinate _coordinate, Orientation _orientation, Coordinate _grid_max)
	:coordinate(_coordinate), orientation(_orientation), grid_max(_grid_max)
	{
		if(!grid_max.is_inside(coordinate))
		{
			throw std::runtime_error("Attempt to create robot outside of defined grid");
		}
	}

	void act(Command c);

	Coordinate coordinate;
	Orientation orientation;
	const Coordinate grid_max;
	bool lost=false;

private:
};

#endif
