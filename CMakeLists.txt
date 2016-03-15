cmake_minimum_required(VERSION 3.3)
project(gllib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -std=c++11")

set(SOURCE_FILES main.cpp tgaimage.cpp tgaimage.h glLib.cpp glLib.h Model.cpp Model.h Vec.h Errors.h Error.cpp)
add_executable(gllib ${SOURCE_FILES})