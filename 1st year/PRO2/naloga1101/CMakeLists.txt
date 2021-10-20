cmake_minimum_required(VERSION 3.19)
project(naloga1101)

set(CMAKE_CXX_STANDARD 14)

add_executable(naloga1101 main.cpp View.cpp View.h Position.cpp Position.h Size.cpp Size.h Unit.h Layout.cpp Layout.h ImageView.cpp ImageView.h TextView.cpp TextView.h Button.cpp Button.h ImageButton.cpp ImageButton.h TextInput.cpp TextInput.h)