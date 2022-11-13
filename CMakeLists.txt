cmake_Minimum_required(VERSION 3.8)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(This opencv-hood-detection)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(Dart)

set(TOOLS_FOLDER "D:/Tools/")

enable_testing()

add_subdirectory(${TOOLS_FOLDER}/googletest googletest_build)

set(HEADERS
	OHD_statemachine.hpp
	OHD_types.hpp
)
set(SOURCES
	OHD_main.cpp
	OHD_statemachine.cpp
)

add_library(${This} STATIC ${SOURCES} ${HEADERS})
add_executable(opencv-hood-detection-exec ${SOURCES} ${HEADERS})

add_subdirectory(test)