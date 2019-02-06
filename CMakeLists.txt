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
		GL
	)
	set(CMAKE_CXX_FLAGS "-g -std=c++17 -Wall -Wno-unused-variable")
else()
	include_directories(
		winbuild/include/SFML/include/
	)

	link_directories(
		winbuild/include/SFML/lib/
	)

	link_libraries(
		sfml-graphics-s
		sfml-window-s
		sfml-audio-s
		sfml-network-s
		sfml-system-s
		opengl32
		winmm
		gdi32
		freetype
		openal32
		FLAC
		vorbisenc
		vorbisfile
		vorbis
		ogg
		ws2_32
	)
	set(CMAKE_CXX_FLAGS"-g -std=c++17 -Wall -Wno-unused-variable")
	set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
	add_definitions(-DSFML_STATIC)
endif()

file(GLOB_RECURSE MAIN_SRC "src/*.cpp")
file(GLOB IMGUI_SRC "include/imgui/*.cpp")
file(GLOB IMGUI_SFML_SRC "include/imgui-sfml/*.cpp")

file(COPY resource DESTINATION ${CMAKE_BINARY_DIR})

add_executable(a.out ${MAIN_SRC} ${IMGUI_SRC} ${IMGUI_SFML_SRC})