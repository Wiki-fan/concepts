cmake_minimum_required(VERSION 3.9)
project(rtti)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "-fno-rtti -std=c++2a -Wwritable-strings")
add_executable(task3 main.cpp DynamicCast.h DynamicCast.cpp TypeInfo.h TypeInfo.cpp)
#target_link_libraries (parser LINK_PUBLIC midifile)
