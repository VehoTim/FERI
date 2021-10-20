cmake_minimum_required(VERSION 3.19)
project(naloga0902)

set(CMAKE_CXX_STANDARD 14)

add_executable(naloga0902 main.cpp Board.cpp Board.h Date.cpp Date.h DateTime.cpp DateTime.h ExpirationTask.cpp ExpirationTask.h Task.cpp Task.h Time.cpp Time.h)