// Functions to parse user input into our program state

// The philosophy for this file is to separate the input parsing from the application logic

#ifndef PARSING_H
#define PARSING_H

#include "robot.h"

// Parse a direction enum from a char
Orientation char_to_orientation(char c);
char orientation_to_char(Orientation o);

Command char_to_command(char c);

// The user input provides the X and Y coordinate on a single line
// Parse this into our coordinate struct
[[nodiscard]] Coordinate parse_initial_coordinates(const std::string &s);

// Similar to the initial coordinates, the user provides robot position on one line
// This fuction parses that format, and provides back our struct
[[nodiscard]] Robot parse_robot_position(const std::string &s, const Coordinate grid_max, ScentTracker *scent);


// Try and read the next line that isn't entirely whitespace
// The problem spec doesn't mention that whitespace lines can be safely ingored,
// but the example input shows that they can!
// Return true if we could get such a line, false if we could not
[[nodiscard]] bool try_read_next_nonwhitespace_line(std::string &line);

void read_next_nonwhitespace_line(std::string &line);




#endif
