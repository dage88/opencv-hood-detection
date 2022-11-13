cmake_minimum_required(VERSION 3.8)

set(This opencv-hood-detection-tests)

project(${This} C CXX)

set(HEADERS
	OHD_mock.hpp
)
set(SOURCES
	OHD_test.cpp
)

add_executable(${This} ${SOURCES} ${HEADERS})

target_link_libraries(${This} PUBLIC
	gtest_main
	gmock
	opencv-hood-detection
)

#In VS Code, with "Ctrl+Shift+P -> Cmake: Run Tests" these tests will be executed (if CMakeLists.txt in ../ was detected)
add_test(
	NAME ${This}
	COMMAND ${This}
)