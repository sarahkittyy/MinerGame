set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
include(CMakeForceCompiler)

set(TOOLCHAIN_PREFIX /usr/binx86_64-w64-mingw32)

set(WINDOWS TRUE)

set(CMAKE_C_COMPILER /usr/bin/${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_MAKE_PROGRAM /usr/bin/make)
set(CMAKE_AR_COMPILER /usr/bin/${TOOLCHAIN_PREFIX}-windres)

set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

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
	stdc++
)

add_definitions("-g -DSFML_STATIC -Wall -Wno-unused-variable")

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)