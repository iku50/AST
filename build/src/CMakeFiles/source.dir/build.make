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
CMAKE_BINARY_DIR = "/home/rickeee/Nutstore Files/我的坚果云/AST/build"

# Include any dependencies generated for this target.
include src/CMakeFiles/source.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/source.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/source.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/source.dir/flags.make

src/CMakeFiles/source.dir/ASTgenerate.c++.o: src/CMakeFiles/source.dir/flags.make
src/CMakeFiles/source.dir/ASTgenerate.c++.o: ../src/ASTgenerate.c++
src/CMakeFiles/source.dir/ASTgenerate.c++.o: src/CMakeFiles/source.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/rickeee/Nutstore Files/我的坚果云/AST/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/source.dir/ASTgenerate.c++.o"
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/source.dir/ASTgenerate.c++.o -MF CMakeFiles/source.dir/ASTgenerate.c++.o.d -o CMakeFiles/source.dir/ASTgenerate.c++.o -c "/home/rickeee/Nutstore Files/我的坚果云/AST/src/ASTgenerate.c++"

src/CMakeFiles/source.dir/ASTgenerate.c++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source.dir/ASTgenerate.c++.i"
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/rickeee/Nutstore Files/我的坚果云/AST/src/ASTgenerate.c++" > CMakeFiles/source.dir/ASTgenerate.c++.i

src/CMakeFiles/source.dir/ASTgenerate.c++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source.dir/ASTgenerate.c++.s"
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/rickeee/Nutstore Files/我的坚果云/AST/src/ASTgenerate.c++" -o CMakeFiles/source.dir/ASTgenerate.c++.s

src/CMakeFiles/source.dir/src.c++.o: src/CMakeFiles/source.dir/flags.make
src/CMakeFiles/source.dir/src.c++.o: ../src/src.c++
src/CMakeFiles/source.dir/src.c++.o: src/CMakeFiles/source.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/rickeee/Nutstore Files/我的坚果云/AST/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/source.dir/src.c++.o"
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/source.dir/src.c++.o -MF CMakeFiles/source.dir/src.c++.o.d -o CMakeFiles/source.dir/src.c++.o -c "/home/rickeee/Nutstore Files/我的坚果云/AST/src/src.c++"

src/CMakeFiles/source.dir/src.c++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source.dir/src.c++.i"
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/rickeee/Nutstore Files/我的坚果云/AST/src/src.c++" > CMakeFiles/source.dir/src.c++.i

src/CMakeFiles/source.dir/src.c++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source.dir/src.c++.s"
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/rickeee/Nutstore Files/我的坚果云/AST/src/src.c++" -o CMakeFiles/source.dir/src.c++.s

# Object files for target source
source_OBJECTS = \
"CMakeFiles/source.dir/ASTgenerate.c++.o" \
"CMakeFiles/source.dir/src.c++.o"

# External object files for target source
source_EXTERNAL_OBJECTS =

src/libsource.a: src/CMakeFiles/source.dir/ASTgenerate.c++.o
src/libsource.a: src/CMakeFiles/source.dir/src.c++.o
src/libsource.a: src/CMakeFiles/source.dir/build.make
src/libsource.a: src/CMakeFiles/source.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/rickeee/Nutstore Files/我的坚果云/AST/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libsource.a"
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/source.dir/cmake_clean_target.cmake
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/source.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/source.dir/build: src/libsource.a
.PHONY : src/CMakeFiles/source.dir/build

src/CMakeFiles/source.dir/clean:
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/source.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/source.dir/clean

src/CMakeFiles/source.dir/depend:
	cd "/home/rickeee/Nutstore Files/我的坚果云/AST/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/rickeee/Nutstore Files/我的坚果云/AST" "/home/rickeee/Nutstore Files/我的坚果云/AST/src" "/home/rickeee/Nutstore Files/我的坚果云/AST/build" "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src" "/home/rickeee/Nutstore Files/我的坚果云/AST/build/src/CMakeFiles/source.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/CMakeFiles/source.dir/depend

