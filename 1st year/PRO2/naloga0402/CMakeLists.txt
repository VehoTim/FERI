cmake_minimum_required(VERSION 3.17)
project(naloga0402)

set(CMAKE_CXX_STANDARD 14)

add_executable(naloga0402 main.cpp Athlete.cpp Athlete.h Competitor.cpp Competitor.h Date.cpp Date.h Competition.cpp Competition.h Time.cpp Time.h DateTime.cpp DateTime.h Results.cpp Results.h)