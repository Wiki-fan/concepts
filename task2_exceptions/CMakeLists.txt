cmake_minimum_required(VERSION 3.9)
project(exceptions)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-fno-exceptions")
add_executable(main main.cpp Exceptions.h Exceptions.cpp Object.h Object.cpp Destroyer.h Destroyer.cpp)
#target_link_libraries (parser LINK_PUBLIC midifile)
