cmake_minimum_required(VERSION 3.13.3)
project(MinerGame VERSION 1.0.0)

include_directories(
	include/
	include/imgui
	include/imgui-sfml
	include/nlohmann
)

if(NOT WINDOWS)
	link_libraries(
		sfml-graphics
		sfml-window
		sfml-audio
		sfml-network
		sfml-system
		stdc++
		GL
	)
endif()

add_compile_options("-std=c++17")

set(CMAKE_CXX_FLAGS "-g -Wall -Wno-unused-variable")

file(GLOB_RECURSE MAIN_SRC "src/*.cpp")
file(GLOB IMGUI_SRC "include/imgui/*.cpp")
file(GLOB IMGUI_SFML_SRC "include/imgui-sfml/*.cpp")

file(COPY resource DESTINATION ${CMAKE_BINARY_DIR})

if(WINDOWS)
	set(CMAKE_BINARY_DIR bin/windows/)
else()
	set(CMAKE_BINARY_DIR bin/linux/)
endif()

add_executable(a.out ${MAIN_SRC} ${IMGUI_SRC} ${IMGUI_SFML_SRC})