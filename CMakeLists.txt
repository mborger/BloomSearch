cmake_minimum_required(VERSION 2.6)

project(BloomSearch)

add_definitions(-std=c++0x)

add_library(util
	util.cpp
	hash/MurmurHash3.cpp
	hash/SpookyV2.cpp
	)

add_executable(search search.cpp)
target_link_libraries(search util pqxx pq)
