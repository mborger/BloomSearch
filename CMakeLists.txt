cmake_minimum_required(VERSION 2.6)

project(BloomSearch CXX ASM)

set(CMAKE_BUILD_TYPE RELEASE)

add_definitions(-std=c++0x)

add_library(util
	util.cpp
	hash/MurmurHash3.cpp
	hash/SpookyV2.cpp
	hash/fastfnv64a.s
	)

add_executable(insert insert.cpp)
target_link_libraries(insert util pqxx pq)

add_executable(search search.cpp)
target_link_libraries(search util pqxx pq)
