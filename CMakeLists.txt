cmake_Minimum_required(VERSION 3.8)
project(opencv-hood-detection VERSION 0.1.0)

set(This opencv-hood-detection)


project(${This} C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(TOOLS_FOLDER "D:/Tools")

################# GTEST #################
include(Dart)
include(CTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()
add_subdirectory(${TOOLS_FOLDER}/googletest googletest_build)

################# OpenCV #################
set(OpenCV_DIR ${TOOLS_FOLDER}/opencv/build)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

################# Creating executables/libraries #################
set(HEADERS
	OHD_statemachine.hpp
	OHD_types.hpp
)
set(SOURCES
	OHD_main.cpp
	OHD_statemachine.cpp
)

add_library(opencv-hood-detection-lib STATIC
	${SOURCES}
	${HEADERS}
)

add_executable(${This} ${SOURCES} ${HEADERS} )
target_link_libraries(${This} ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(test)