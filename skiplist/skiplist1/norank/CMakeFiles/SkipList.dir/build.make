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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/linux/skiplist/norank

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/linux/skiplist/norank

# Include any dependencies generated for this target.
include CMakeFiles/SkipList.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SkipList.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SkipList.dir/flags.make

CMakeFiles/SkipList.dir/skiplist_test.c.o: CMakeFiles/SkipList.dir/flags.make
CMakeFiles/SkipList.dir/skiplist_test.c.o: skiplist_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/skiplist/norank/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SkipList.dir/skiplist_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SkipList.dir/skiplist_test.c.o   -c /home/linux/skiplist/norank/skiplist_test.c

CMakeFiles/SkipList.dir/skiplist_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SkipList.dir/skiplist_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/linux/skiplist/norank/skiplist_test.c > CMakeFiles/SkipList.dir/skiplist_test.c.i

CMakeFiles/SkipList.dir/skiplist_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SkipList.dir/skiplist_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/linux/skiplist/norank/skiplist_test.c -o CMakeFiles/SkipList.dir/skiplist_test.c.s

# Object files for target SkipList
SkipList_OBJECTS = \
"CMakeFiles/SkipList.dir/skiplist_test.c.o"

# External object files for target SkipList
SkipList_EXTERNAL_OBJECTS =

SkipList: CMakeFiles/SkipList.dir/skiplist_test.c.o
SkipList: CMakeFiles/SkipList.dir/build.make
SkipList: CMakeFiles/SkipList.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/linux/skiplist/norank/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable SkipList"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SkipList.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SkipList.dir/build: SkipList

.PHONY : CMakeFiles/SkipList.dir/build

CMakeFiles/SkipList.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SkipList.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SkipList.dir/clean

CMakeFiles/SkipList.dir/depend:
	cd /home/linux/skiplist/norank && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/linux/skiplist/norank /home/linux/skiplist/norank /home/linux/skiplist/norank /home/linux/skiplist/norank /home/linux/skiplist/norank/CMakeFiles/SkipList.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SkipList.dir/depend

