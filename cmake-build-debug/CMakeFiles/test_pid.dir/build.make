# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/Users/Administrator/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Administrator/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/d/documents/code/toy-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/d/documents/code/toy-project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/test_pid.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_pid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_pid.dir/flags.make

CMakeFiles/test_pid.dir/main/test_pid.cpp.o: CMakeFiles/test_pid.dir/flags.make
CMakeFiles/test_pid.dir/main/test_pid.cpp.o: ../main/test_pid.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/d/documents/code/toy-project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_pid.dir/main/test_pid.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_pid.dir/main/test_pid.cpp.o -c /cygdrive/d/documents/code/toy-project/main/test_pid.cpp

CMakeFiles/test_pid.dir/main/test_pid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_pid.dir/main/test_pid.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/d/documents/code/toy-project/main/test_pid.cpp > CMakeFiles/test_pid.dir/main/test_pid.cpp.i

CMakeFiles/test_pid.dir/main/test_pid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_pid.dir/main/test_pid.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/d/documents/code/toy-project/main/test_pid.cpp -o CMakeFiles/test_pid.dir/main/test_pid.cpp.s

# Object files for target test_pid
test_pid_OBJECTS = \
"CMakeFiles/test_pid.dir/main/test_pid.cpp.o"

# External object files for target test_pid
test_pid_EXTERNAL_OBJECTS =

test_pid.exe: CMakeFiles/test_pid.dir/main/test_pid.cpp.o
test_pid.exe: CMakeFiles/test_pid.dir/build.make
test_pid.exe: CMakeFiles/test_pid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/d/documents/code/toy-project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_pid.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_pid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_pid.dir/build: test_pid.exe

.PHONY : CMakeFiles/test_pid.dir/build

CMakeFiles/test_pid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_pid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_pid.dir/clean

CMakeFiles/test_pid.dir/depend:
	cd /cygdrive/d/documents/code/toy-project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/d/documents/code/toy-project /cygdrive/d/documents/code/toy-project /cygdrive/d/documents/code/toy-project/cmake-build-debug /cygdrive/d/documents/code/toy-project/cmake-build-debug /cygdrive/d/documents/code/toy-project/cmake-build-debug/CMakeFiles/test_pid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_pid.dir/depend

