cmake_minimum_required(VERSION 3.22)

project(visszaver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
		visszaver
		src/main.cpp
		src/app.cpp
)

target_include_directories(visszaver
		PRIVATE
		${PROJECT_SOURCE_DIR}/include
)

add_compile_options(
		-Wall
		-Wextra
		-Wpedantic
)