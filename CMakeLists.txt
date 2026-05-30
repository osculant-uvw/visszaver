cmake_minimum_required(VERSION 3.22)

project(visszaver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

add_compile_options(
		-Wall
		-Wextra
		-Wpedantic
)

# app/visszaver-api
add_executable(visszaver_api
		app/visszaver-api/main.cpp
)

target_include_directories(visszaver_api
		PRIVATE
		${PROJECT_SOURCE_DIR}
		${PQXX_INCLUDE_DIRS}
)

target_link_libraries(visszaver_api
		PRIVATE
		${PQXX_LIBRARIES}
)


# app/visszaver-satellite-receiver
add_executable(visszaver_satellite_receiver
		app/visszaver-satellite-receiver/main.cpp
)

target_include_directories(visszaver_satellite_receiver
		PRIVATE
		${PROJECT_SOURCE_DIR}
		${PQXX_INCLUDE_DIRS}
)

target_link_libraries(visszaver_satellite_receiver
		PRIVATE
		${PQXX_LIBRARIES}
)
