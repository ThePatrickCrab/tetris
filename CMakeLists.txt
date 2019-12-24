cmake_minimum_required(VERSION 3.1)
project(tetris)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES
	src/main.cpp
	src/Location.cpp
	src/Shape.cpp
	src/Tetris.cpp)

add_executable(tetris ${SOURCES})
target_include_directories(tetris PRIVATE include)

target_link_libraries(tetris ${CONAN_LIBS})
target_compile_features(tetris PRIVATE cxx_std_17)
