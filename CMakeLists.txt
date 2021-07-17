cmake_minimum_required(VERSION 3.8)
project(tetris)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(tetris
	src/main.cpp
	src/Location.cpp
	src/Shape.cpp
	src/Tetris.cpp)

target_include_directories(tetris PRIVATE include)
target_link_libraries(tetris ${CONAN_LIBS})

target_compile_features(tetris PRIVATE cxx_std_17)

file(COPY resources DESTINATION bin)
