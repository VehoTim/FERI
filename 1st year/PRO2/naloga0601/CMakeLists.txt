cmake_minimum_required(VERSION 3.17)
project(naloga0601)

set(CMAKE_CXX_STANDARD 14)

add_executable(naloga0601 main.cpp GameObject.cpp GameObject.h Player.cpp Player.h GameState.cpp GameState.h Game.cpp Game.h)