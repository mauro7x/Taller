# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/build"

# Include any dependencies generated for this target.
include CMakeFiles/sdl_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sdl_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sdl_test.dir/flags.make

CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o: CMakeFiles/sdl_test.dir/flags.make
CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o: ../36_multiple_windows.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o -c "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/36_multiple_windows.cpp"

CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/36_multiple_windows.cpp" > CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.i

CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/36_multiple_windows.cpp" -o CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.s

CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o.requires:

.PHONY : CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o.requires

CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o.provides: CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o.requires
	$(MAKE) -f CMakeFiles/sdl_test.dir/build.make CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o.provides.build
.PHONY : CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o.provides

CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o.provides.build: CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o


# Object files for target sdl_test
sdl_test_OBJECTS = \
"CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o"

# External object files for target sdl_test
sdl_test_EXTERNAL_OBJECTS =

sdl_test: CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o
sdl_test: CMakeFiles/sdl_test.dir/build.make
sdl_test: CMakeFiles/sdl_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sdl_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sdl_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sdl_test.dir/build: sdl_test

.PHONY : CMakeFiles/sdl_test.dir/build

CMakeFiles/sdl_test.dir/requires: CMakeFiles/sdl_test.dir/36_multiple_windows.cpp.o.requires

.PHONY : CMakeFiles/sdl_test.dir/requires

CMakeFiles/sdl_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sdl_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sdl_test.dir/clean

CMakeFiles/sdl_test.dir/depend:
	cd "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows" "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows" "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/build" "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/build" "/home/mp/Facultad/1C 2020/Taller/Otros/SDL_testing/Tutorial/36_multiple_windows/build/CMakeFiles/sdl_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/sdl_test.dir/depend

