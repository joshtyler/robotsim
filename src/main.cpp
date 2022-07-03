#include <iostream>
#include <sstream>

struct Coordinate
{
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

Coordinate parse_initial_coordinates(const std::string &s)
{
	// This is slightly inefficient since we read a line, then immediately construct a temporary stringstream
	// But this enforces the semantics that both coordinates are on one line in a simple way
	std::stringstream ss(s);
	int x=0;
	int y=0;
	ss >> x;
	ss >> y;
	if(ss.fail())
	{
		throw std::runtime_error("Could not parse initial coordinates");
	}

	const Coordinate ret(x,y);
	return ret;
}

int main(void)
{
	try
	{
		// The first line contains our coordinate pair
		std::string line;
		std::getline(std::cin, line);
		const auto grid_max = parse_initial_coordinates(line);
	} catch(std::runtime_error &e) {
		std::cout << "ERROR: " << e.what() << '\n';
		return 1;
	} catch(...) {
		std::cout << "Unknown error occurred\n";
		return 1;
	}
	return 0;
}
