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
CMAKE_COMMAND = /home/peter/.local/share/JetBrains/Toolbox/apps/CLion/ch-1/192.6817.32/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/peter/.local/share/JetBrains/Toolbox/apps/CLion/ch-1/192.6817.32/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/peter/CLionProjects/emu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/peter/CLionProjects/emu/cmake-build-debug

# Include any dependencies generated for this target.
include utility_test/tests/CMakeFiles/testsrun.dir/depend.make

# Include the progress variables for this target.
include utility_test/tests/CMakeFiles/testsrun.dir/progress.make

# Include the compile flags for this target's objects.
include utility_test/tests/CMakeFiles/testsrun.dir/flags.make

utility_test/tests/CMakeFiles/testsrun.dir/main.cpp.o: utility_test/tests/CMakeFiles/testsrun.dir/flags.make
utility_test/tests/CMakeFiles/testsrun.dir/main.cpp.o: ../utility_test/tests/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peter/CLionProjects/emu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object utility_test/tests/CMakeFiles/testsrun.dir/main.cpp.o"
	cd /home/peter/CLionProjects/emu/cmake-build-debug/utility_test/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testsrun.dir/main.cpp.o -c /home/peter/CLionProjects/emu/utility_test/tests/main.cpp

utility_test/tests/CMakeFiles/testsrun.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testsrun.dir/main.cpp.i"
	cd /home/peter/CLionProjects/emu/cmake-build-debug/utility_test/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/peter/CLionProjects/emu/utility_test/tests/main.cpp > CMakeFiles/testsrun.dir/main.cpp.i

utility_test/tests/CMakeFiles/testsrun.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testsrun.dir/main.cpp.s"
	cd /home/peter/CLionProjects/emu/cmake-build-debug/utility_test/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/peter/CLionProjects/emu/utility_test/tests/main.cpp -o CMakeFiles/testsrun.dir/main.cpp.s

# Object files for target testsrun
testsrun_OBJECTS = \
"CMakeFiles/testsrun.dir/main.cpp.o"

# External object files for target testsrun
testsrun_EXTERNAL_OBJECTS =

utility_test/tests/testsrun: utility_test/tests/CMakeFiles/testsrun.dir/main.cpp.o
utility_test/tests/testsrun: utility_test/tests/CMakeFiles/testsrun.dir/build.make
utility_test/tests/testsrun: utility_test/gtest/gtest-1.7.0/libgtest.a
utility_test/tests/testsrun: utility_test/gtest/gtest-1.7.0/libgtest_main.a
utility_test/tests/testsrun: utility/libemutil.so
utility_test/tests/testsrun: utility_test/gtest/gtest-1.7.0/libgtest.a
utility_test/tests/testsrun: utility_test/tests/CMakeFiles/testsrun.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/peter/CLionProjects/emu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testsrun"
	cd /home/peter/CLionProjects/emu/cmake-build-debug/utility_test/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testsrun.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utility_test/tests/CMakeFiles/testsrun.dir/build: utility_test/tests/testsrun

.PHONY : utility_test/tests/CMakeFiles/testsrun.dir/build

utility_test/tests/CMakeFiles/testsrun.dir/clean:
	cd /home/peter/CLionProjects/emu/cmake-build-debug/utility_test/tests && $(CMAKE_COMMAND) -P CMakeFiles/testsrun.dir/cmake_clean.cmake
.PHONY : utility_test/tests/CMakeFiles/testsrun.dir/clean

utility_test/tests/CMakeFiles/testsrun.dir/depend:
	cd /home/peter/CLionProjects/emu/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/peter/CLionProjects/emu /home/peter/CLionProjects/emu/utility_test/tests /home/peter/CLionProjects/emu/cmake-build-debug /home/peter/CLionProjects/emu/cmake-build-debug/utility_test/tests /home/peter/CLionProjects/emu/cmake-build-debug/utility_test/tests/CMakeFiles/testsrun.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utility_test/tests/CMakeFiles/testsrun.dir/depend

