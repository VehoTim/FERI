cmake_minimum_required(VERSION 3.17)
project(naloga0502)

set(CMAKE_CXX_STANDARD 14)

add_executable(naloga0502 main.cpp Time.cpp Time.h Date.cpp Date.h DateTime.cpp DateTime.h Task.cpp Task.h ExpirationTask.cpp ExpirationTask.h Board.cpp Board.h Category.cpp Category.h)