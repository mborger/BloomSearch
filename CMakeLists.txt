project(BloomSearch CXX ASM)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE RELEASE)

add_definitions(-std=c++0x)

add_library(util
	src/util.cpp
	src/hash/MurmurHash3.cpp
	src/hash/SpookyV2.cpp
	src/hash/fastfnv64a.s
	)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQ REQUIRED libpqxx libpq)

add_executable(insert src/insert.cpp)
target_link_libraries(insert util ${PQ_LIBRARIES})

add_executable(searchBloom src/searchBloom.cpp)
target_link_libraries(searchBloom util ${PQ_LIBRARIES})

add_executable(searchName src/searchName.cpp)
target_link_libraries(searchName util ${PQ_LIBRARIES})
