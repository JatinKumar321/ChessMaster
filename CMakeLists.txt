cmake_minimum_required(VERSION 3.10)

project(ChessGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(include)

add_executable(chess ${SOURCES})
