# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/rickeee/Nutstore Files/我的坚果云/AST"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/rickeee/Nutstore Files/我的坚果云/AST"

# Include any dependencies generated for this target.
include CMakeFiles/AST.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AST.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AST.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AST.dir/flags.make

CMakeFiles/AST.dir/main.c++.o: CMakeFiles/AST.dir/flags.make
CMakeFiles/AST.dir/main.c++.o: main.c++
CMakeFiles/AST.dir/main.c++.o: CMakeFiles/AST.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/rickeee/Nutstore Files/我的坚果云/AST/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AST.dir/main.c++.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AST.dir/main.c++.o -MF CMakeFiles/AST.dir/main.c++.o.d -o CMakeFiles/AST.dir/main.c++.o -c "/home/rickeee/Nutstore Files/我的坚果云/AST/main.c++"

CMakeFiles/AST.dir/main.c++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AST.dir/main.c++.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/rickeee/Nutstore Files/我的坚果云/AST/main.c++" > CMakeFiles/AST.dir/main.c++.i

CMakeFiles/AST.dir/main.c++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AST.dir/main.c++.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/rickeee/Nutstore Files/我的坚果云/AST/main.c++" -o CMakeFiles/AST.dir/main.c++.s

# Object files for target AST
AST_OBJECTS = \
"CMakeFiles/AST.dir/main.c++.o"

# External object files for target AST
AST_EXTERNAL_OBJECTS =

AST: CMakeFiles/AST.dir/main.c++.o
AST: CMakeFiles/AST.dir/build.make
AST: src/libsource.a
AST: CMakeFiles/AST.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/rickeee/Nutstore Files/我的坚果云/AST/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AST"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AST.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AST.dir/build: AST
.PHONY : CMakeFiles/AST.dir/build

CMakeFiles/AST.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AST.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AST.dir/clean

CMakeFiles/AST.dir/depend:
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/rickeee/Nutstore Files/我的坚果云/AST" "/home/rickeee/Nutstore Files/我的坚果云/AST" "/home/rickeee/Nutstore Files/我的坚果云/AST" "/home/rickeee/Nutstore Files/我的坚果云/AST" "/home/rickeee/Nutstore Files/我的坚果云/AST/CMakeFiles/AST.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/AST.dir/depend
