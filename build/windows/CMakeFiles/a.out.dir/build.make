# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sarahkitty/Code/C++/Miner

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sarahkitty/Code/C++/Miner/build/windows

# Include any dependencies generated for this target.
include CMakeFiles/a.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a.out.dir/flags.make

CMakeFiles/a.out.dir/src/Application.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/Application.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/src/Application.cpp.obj: ../../src/Application.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a.out.dir/src/Application.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/src/Application.cpp.obj -c /home/sarahkitty/Code/C++/Miner/src/Application.cpp

CMakeFiles/a.out.dir/src/Application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/src/Application.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/src/Application.cpp > CMakeFiles/a.out.dir/src/Application.cpp.i

CMakeFiles/a.out.dir/src/Application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/src/Application.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/src/Application.cpp -o CMakeFiles/a.out.dir/src/Application.cpp.s

CMakeFiles/a.out.dir/src/BuildingManager.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/BuildingManager.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/src/BuildingManager.cpp.obj: ../../src/BuildingManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/a.out.dir/src/BuildingManager.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/src/BuildingManager.cpp.obj -c /home/sarahkitty/Code/C++/Miner/src/BuildingManager.cpp

CMakeFiles/a.out.dir/src/BuildingManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/src/BuildingManager.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/src/BuildingManager.cpp > CMakeFiles/a.out.dir/src/BuildingManager.cpp.i

CMakeFiles/a.out.dir/src/BuildingManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/src/BuildingManager.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/src/BuildingManager.cpp -o CMakeFiles/a.out.dir/src/BuildingManager.cpp.s

CMakeFiles/a.out.dir/src/KeyManager.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/KeyManager.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/src/KeyManager.cpp.obj: ../../src/KeyManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/a.out.dir/src/KeyManager.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/src/KeyManager.cpp.obj -c /home/sarahkitty/Code/C++/Miner/src/KeyManager.cpp

CMakeFiles/a.out.dir/src/KeyManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/src/KeyManager.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/src/KeyManager.cpp > CMakeFiles/a.out.dir/src/KeyManager.cpp.i

CMakeFiles/a.out.dir/src/KeyManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/src/KeyManager.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/src/KeyManager.cpp -o CMakeFiles/a.out.dir/src/KeyManager.cpp.s

CMakeFiles/a.out.dir/src/MaterialManager.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/MaterialManager.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/src/MaterialManager.cpp.obj: ../../src/MaterialManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/a.out.dir/src/MaterialManager.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/src/MaterialManager.cpp.obj -c /home/sarahkitty/Code/C++/Miner/src/MaterialManager.cpp

CMakeFiles/a.out.dir/src/MaterialManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/src/MaterialManager.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/src/MaterialManager.cpp > CMakeFiles/a.out.dir/src/MaterialManager.cpp.i

CMakeFiles/a.out.dir/src/MaterialManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/src/MaterialManager.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/src/MaterialManager.cpp -o CMakeFiles/a.out.dir/src/MaterialManager.cpp.s

CMakeFiles/a.out.dir/src/Tilemap.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/Tilemap.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/src/Tilemap.cpp.obj: ../../src/Tilemap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/a.out.dir/src/Tilemap.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/src/Tilemap.cpp.obj -c /home/sarahkitty/Code/C++/Miner/src/Tilemap.cpp

CMakeFiles/a.out.dir/src/Tilemap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/src/Tilemap.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/src/Tilemap.cpp > CMakeFiles/a.out.dir/src/Tilemap.cpp.i

CMakeFiles/a.out.dir/src/Tilemap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/src/Tilemap.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/src/Tilemap.cpp -o CMakeFiles/a.out.dir/src/Tilemap.cpp.s

CMakeFiles/a.out.dir/src/main.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/main.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/src/main.cpp.obj: ../../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/a.out.dir/src/main.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/src/main.cpp.obj -c /home/sarahkitty/Code/C++/Miner/src/main.cpp

CMakeFiles/a.out.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/src/main.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/src/main.cpp > CMakeFiles/a.out.dir/src/main.cpp.i

CMakeFiles/a.out.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/src/main.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/src/main.cpp -o CMakeFiles/a.out.dir/src/main.cpp.s

CMakeFiles/a.out.dir/include/imgui/imgui.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/include/imgui/imgui.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/include/imgui/imgui.cpp.obj: ../../include/imgui/imgui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/a.out.dir/include/imgui/imgui.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/include/imgui/imgui.cpp.obj -c /home/sarahkitty/Code/C++/Miner/include/imgui/imgui.cpp

CMakeFiles/a.out.dir/include/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/include/imgui/imgui.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/include/imgui/imgui.cpp > CMakeFiles/a.out.dir/include/imgui/imgui.cpp.i

CMakeFiles/a.out.dir/include/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/include/imgui/imgui.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/include/imgui/imgui.cpp -o CMakeFiles/a.out.dir/include/imgui/imgui.cpp.s

CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.obj: ../../include/imgui/imgui_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.obj -c /home/sarahkitty/Code/C++/Miner/include/imgui/imgui_demo.cpp

CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/include/imgui/imgui_demo.cpp > CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.i

CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/include/imgui/imgui_demo.cpp -o CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.s

CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.obj: ../../include/imgui/imgui_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.obj -c /home/sarahkitty/Code/C++/Miner/include/imgui/imgui_draw.cpp

CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/include/imgui/imgui_draw.cpp > CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.i

CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/include/imgui/imgui_draw.cpp -o CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.s

CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.obj: ../../include/imgui/imgui_widgets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.obj -c /home/sarahkitty/Code/C++/Miner/include/imgui/imgui_widgets.cpp

CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/include/imgui/imgui_widgets.cpp > CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.i

CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/include/imgui/imgui_widgets.cpp -o CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.s

CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.obj: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.obj: CMakeFiles/a.out.dir/includes_CXX.rsp
CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.obj: ../../include/imgui-sfml/imgui-SFML.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.obj -c /home/sarahkitty/Code/C++/Miner/include/imgui-sfml/imgui-SFML.cpp

CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sarahkitty/Code/C++/Miner/include/imgui-sfml/imgui-SFML.cpp > CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.i

CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sarahkitty/Code/C++/Miner/include/imgui-sfml/imgui-SFML.cpp -o CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.s

# Object files for target a.out
a_out_OBJECTS = \
"CMakeFiles/a.out.dir/src/Application.cpp.obj" \
"CMakeFiles/a.out.dir/src/BuildingManager.cpp.obj" \
"CMakeFiles/a.out.dir/src/KeyManager.cpp.obj" \
"CMakeFiles/a.out.dir/src/MaterialManager.cpp.obj" \
"CMakeFiles/a.out.dir/src/Tilemap.cpp.obj" \
"CMakeFiles/a.out.dir/src/main.cpp.obj" \
"CMakeFiles/a.out.dir/include/imgui/imgui.cpp.obj" \
"CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.obj" \
"CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.obj" \
"CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.obj" \
"CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.obj"

# External object files for target a.out
a_out_EXTERNAL_OBJECTS =

bin/a.out.exe: CMakeFiles/a.out.dir/src/Application.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/src/BuildingManager.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/src/KeyManager.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/src/MaterialManager.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/src/Tilemap.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/src/main.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/include/imgui/imgui.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/include/imgui/imgui_demo.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/include/imgui/imgui_draw.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/include/imgui/imgui_widgets.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/include/imgui-sfml/imgui-SFML.cpp.obj
bin/a.out.exe: CMakeFiles/a.out.dir/build.make
bin/a.out.exe: CMakeFiles/a.out.dir/linklibs.rsp
bin/a.out.exe: CMakeFiles/a.out.dir/objects1.rsp
bin/a.out.exe: CMakeFiles/a.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable bin/a.out.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a.out.dir/build: bin/a.out.exe

.PHONY : CMakeFiles/a.out.dir/build

CMakeFiles/a.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a.out.dir/clean

CMakeFiles/a.out.dir/depend:
	cd /home/sarahkitty/Code/C++/Miner/build/windows && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sarahkitty/Code/C++/Miner /home/sarahkitty/Code/C++/Miner /home/sarahkitty/Code/C++/Miner/build/windows /home/sarahkitty/Code/C++/Miner/build/windows /home/sarahkitty/Code/C++/Miner/build/windows/CMakeFiles/a.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/a.out.dir/depend

