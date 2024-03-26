cmake_minimum_required(VERSION 3.23)
project(Project_Hexagon_v2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(Project_Hexagon_v2 main.cpp Field.cpp Field.h StartScreen.cpp StartScreen.h Game.cpp Game.h ModePlayer.cpp ModePlayer.h ModeComputer.cpp ModeComputer.h)
