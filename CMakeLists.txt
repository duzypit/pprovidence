cmake_minimum_required(VERSION 2.8.9)
project(pprovidence)

#set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 -g")
#headers
include_directories(include)
include_directories(lib)

#set global var SOURCE with all source file names
file(GLOB SOURCES "src/*.cpp")

add_executable(pprovidence ${SOURCES})

target_link_libraries(pprovidence pthread ssl crypto readline)
