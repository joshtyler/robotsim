#ifndef ROBOT_H
#define ROBOT_H

#include <stdexcept>
#include <vector>

// This stores the different possible orientations in a typesafe manner
enum class Orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

// Likewise command
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

// Keep track of which robots have previously been lost and left their scent
// Robots can only fall off the edge, so store this state in a vector of bool of the length of the perimeter
// Carefully index this to store/retrieve whether a robot is lost
// N.B. vector<bool> is likely to be size optimised in c++, so this will be only a few ints large
class ScentTracker
{
public:
	ScentTracker(Coordinate _grid_max);

	inline bool is_scent_set(Coordinate c) const {return scent.at(get_scent_idx(c));};

	inline void set_scent(Coordinate c) {scent.at(get_scent_idx(c)) = true;};

private:
	const Coordinate grid_max;
	std::vector<bool> scent;
	size_t get_scent_idx(Coordinate c) const;
};

// Our actual robot state
struct Robot
{
	Robot(Coordinate _coordinate, Orientation _orientation, Coordinate _grid_max, ScentTracker *_scent)
	:coordinate(_coordinate), orientation(_orientation), grid_max(_grid_max), scent(_scent)
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
	ScentTracker *scent;

private:
};


#endif
