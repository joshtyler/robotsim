#include "parsing.h"
#include <iostream>
#include <sstream>

Orientation char_to_orientation(char c)
{
	switch(c)
	{
		case 'N' : return Orientation::NORTH;
		case 'S' : return Orientation::SOUTH;
		case 'E' : return Orientation::EAST;
		case 'W' : return Orientation::WEST;
		default: throw std::runtime_error("Could not parse orientation");
	}
}

char orientation_to_char(Orientation o)
{
	switch(o)
	{
		case Orientation::NORTH: return 'N';
		case Orientation::SOUTH: return 'S';
		case Orientation::EAST: return 'E';
		case Orientation::WEST: return 'W';
	}
	throw std::runtime_error("Intrernal program error");
}

Command char_to_command(char c)
{
	switch(c)
	{
		case 'L' : return Command::ROTATE_LEFT;
		case 'R' : return Command::ROTATE_RIGHT;
		case 'F' : return Command::MOVE_FORWARD;
		default: throw std::runtime_error("Could not parse command");
	}
}


Coordinate parse_initial_coordinates(const std::string &s)
{
	// This is slightly inefficient since we read a line, then immediately construct a temporary stringstream
	// But this enforces the semantics that both coordinates are on one line in a simple way
	std::stringstream ss(s);
	int x=0;
	int y=0;
	ss >> x;
	ss >> y;
	if(!ss)
	{
		throw std::runtime_error("Could not parse initial coordinates");
	}

	const Coordinate ret(x,y);
	return ret;
}

Robot parse_robot_position(const std::string &s, const Coordinate grid_max)
{
	// This is slightly inefficient since we read a line, then immediately construct a temporary stringstream
	// But this enforces the semantics that both coordinates are on one line in a simple way
	std::stringstream ss(s);
	int x=0;
	int y=0;
	char c='\0';
	ss >> x;
	ss >> y;
	ss >> c;
	if(!ss)
	{
		throw std::runtime_error("Could not parse robot position");
	}

	const Robot ret(Coordinate(x,y),char_to_orientation(c), grid_max);
	return ret;
}

bool try_read_next_nonwhitespace_line(std::string &line)
{
	do
	{
		std::getline(std::cin, line);

		// If the string is not just whitespace, we are good!
		if(line.find_first_not_of(" \t\v\f\r") != std::string::npos)
		{
			return true;
		}
	// Continue trying whilst std::cin has more to give us
	} while(std::cin);

	// If we got to here, it is bad news
	return false;
}

void read_next_nonwhitespace_line(std::string &line)
{
	if(!try_read_next_nonwhitespace_line(line))
	{
		throw std::runtime_error("Expected input, but none was found");
	}
}
