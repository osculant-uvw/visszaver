cmake_minimum_required(VERSION 3.22)

project(visszaver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

add_executable(visszaver
		app/main.cpp
		app/app.cpp
)

target_include_directories(visszaver
		PRIVATE
		${PROJECT_SOURCE_DIR}
		${PQXX_INCLUDE_DIRS}
)

target_link_libraries(visszaver
		PRIVATE
		${PQXX_LIBRARIES}
)

add_compile_options(
		-Wall
		-Wextra
		-Wpedantic
)
