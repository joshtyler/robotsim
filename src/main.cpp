#include <iostream>
#include <sstream>


// Hold a coordinate in our world grid
// The constructor ensures that the proposed x and y values are in-range
struct Coordinate
{
	Coordinate(const std::string &s)
	{

	}


	Coordinate(int _x, int _y)
	:x(_x), y(_y)
	{
		if(x > 50 || y > 50 || x < 0 || y < 0)
		{
			throw std::runtime_error("Attempt to construct coordinate with out of range value");
		}
	}
	int x;
	int y;
};

struct RobotPosition
{
	RobotPosition(int coordinate_x, int coordinate_y, char _orientation)
	:coordinate(coordinate_x, coordinate_y), orientation(char_to_orientation(_orientation))
	{
	}

	Coordinate coordinate;
	enum class Orientation
	{
		N,
		S,
		E,
		W
	};
	Orientation orientation;

private:
	// Parse a direction enum from a char
	static Orientation char_to_orientation(char c)
	{
		switch(c)
		{
			case 'N' : return Orientation::N;
			case 'S' : return Orientation::S;
			case 'E' : return Orientation::E;
			case 'W' : return Orientation::W;
			default: throw std::runtime_error("Could not parse orientation");
		}
	}
};

// The user input provides the X and Y coordinate on a single line
// Parse this into our coordinate struct
[[nodiscard]] Coordinate parse_initial_coordinates(const std::string &s)
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

// Similar to the initial coordinates, the user provides robot position on one line
// This fuction parses that format, and provides back our struct
[[nodiscard]] RobotPosition parse_robot_position(const std::string &s)
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

	const RobotPosition ret(x,y,c);
	return ret;
}


// Try and read the next line that isn't entirely whitespace
// The problem spec doesn't mention that whitespace lines can be safely ingored,
// but the example input shows that they can!
// Return true if we could get such a line, false if we could not
[[nodiscard]] bool try_read_next_nonwhitespace_line(std::string &line)
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

int main(void)
{
	try
	{
		std::string line;

		// The first line contains our maximum grid size
		read_next_nonwhitespace_line(line);
		const auto grid_max = parse_initial_coordinates(line);

		// Following that we get two lines per robot
		// The first is initial position
		// Then comes commands
		// Following this we print out final position
		while(try_read_next_nonwhitespace_line(line))
		{
			auto pos = parse_robot_position(line);
			// Now the user provides a list of commands
			read_next_nonwhitespace_line(line);
		}

	} catch(std::runtime_error &e) {
		std::cout << "ERROR: " << e.what() << '\n';
		return 1;
	} catch(...) {
		std::cout << "Unknown error occurred\n";
		return 1;
	}
	return 0;
}
