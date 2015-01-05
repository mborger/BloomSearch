cmake_minimum_required(VERSION 2.6)

project(BloomSearch)

add_definitions(-std=c++11)

add_library(util util.cpp MurmurHash3.cpp)

add_executable(search search.cpp)
target_link_libraries(search util pqxx pq)
