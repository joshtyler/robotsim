cmake_minimum_required(VERSION 3.16)
project(robotsim)
set(CMAKE_CXX_STANDARD 17)

add_executable(robotsim src/main.cpp src/robot.cpp src/parsing.cpp)
