cmake_minimum_required(VERSION 3.9)
project(exceptions)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp exceptions.h Object.h Object.cpp Destroyer.h Destroyer.cpp)
#target_link_libraries (parser LINK_PUBLIC midifile)
