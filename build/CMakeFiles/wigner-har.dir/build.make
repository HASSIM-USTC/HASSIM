# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/dhem/deom_git/HASSIM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dhem/deom_git/HASSIM/b

# Include any dependencies generated for this target.
include CMakeFiles/wigner-har.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wigner-har.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wigner-har.dir/flags.make

CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.o: CMakeFiles/wigner-har.dir/flags.make
CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.o: ../src/apps/wigner-har.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dhem/deom_git/HASSIM/b/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.o -c /home/dhem/deom_git/HASSIM/src/apps/wigner-har.cpp

CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dhem/deom_git/HASSIM/src/apps/wigner-har.cpp > CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.i

CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dhem/deom_git/HASSIM/src/apps/wigner-har.cpp -o CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.s

# Object files for target wigner-har
wigner__har_OBJECTS = \
"CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.o"

# External object files for target wigner-har
wigner__har_EXTERNAL_OBJECTS =

../bin/wigner-har: CMakeFiles/wigner-har.dir/src/apps/wigner-har.cpp.o
../bin/wigner-har: CMakeFiles/wigner-har.dir/build.make
../bin/wigner-har: ../lib/libdeom.a
../bin/wigner-har: ../lib/libblockdeom.a
../bin/wigner-har: ../lib/libdeom2.a
../bin/wigner-har: ../lib/libideom.a
../bin/wigner-har: ../lib/libblockdeom2.a
../bin/wigner-har: CMakeFiles/wigner-har.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dhem/deom_git/HASSIM/b/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/wigner-har"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wigner-har.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wigner-har.dir/build: ../bin/wigner-har

.PHONY : CMakeFiles/wigner-har.dir/build

CMakeFiles/wigner-har.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wigner-har.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wigner-har.dir/clean

CMakeFiles/wigner-har.dir/depend:
	cd /home/dhem/deom_git/HASSIM/b && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dhem/deom_git/HASSIM /home/dhem/deom_git/HASSIM /home/dhem/deom_git/HASSIM/b /home/dhem/deom_git/HASSIM/b /home/dhem/deom_git/HASSIM/b/CMakeFiles/wigner-har.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wigner-har.dir/depend
