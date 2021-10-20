cmake_minimum_required(VERSION 3.19)
project(naloga1201)

set(CMAKE_CXX_STANDARD 14)

add_executable(naloga1201 main.cpp UnparseableDateException.cpp UnparseableDateException.h FileNotFoundException.cpp FileNotFoundException.h Date.cpp Date.h Fuel.cpp Fuel.h)