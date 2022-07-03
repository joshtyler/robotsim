#include <iostream>
#include <sstream>

#include "parsing.h"
#include "robot.h"

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
			auto robot = parse_robot_position(line, grid_max);

			// Now the user provides a list of commands
			read_next_nonwhitespace_line(line);
			for(const auto cmd_char : line)
			{
				// Skip whitespace, not part of spec but seems implicit
				if(isspace(cmd_char))
				{
					continue;
				}
				robot.act(char_to_command(cmd_char));
			}

			// Now we print the final robot state
			std::cout << robot.coordinate.x << ' ' << robot.coordinate.y << ' ' << orientation_to_char(robot.orientation) << (robot.lost? " LOST" : "") << '\n';
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
