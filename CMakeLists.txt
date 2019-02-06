cmake_minimum_required(VERSION 3.13.3)
project(MinerGame VERSION 1.0.0)

include_directories(
	include/
	include/imgui
	include/imgui-sfml
	include/nlohmann
)

link_libraries(
	sfml-s
)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB SOURCES "include/imgui/*.cpp")
file(GLOB SOURCES "include/imgui-sfml/*.cpp")

add_executable(MinerGame ${SOURCES})