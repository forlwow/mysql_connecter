# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug"

# Include any dependencies generated for this target.
include CMakeFiles/ui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ui.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ui.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ui.dir/flags.make

CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.o: CMakeFiles/ui.dir/flags.make
CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.o: ui_autogen/mocs_compilation.cpp
CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.o: CMakeFiles/ui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.o -MF CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.o -c "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug/ui_autogen/mocs_compilation.cpp"

CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug/ui_autogen/mocs_compilation.cpp" > CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.i

CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug/ui_autogen/mocs_compilation.cpp" -o CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.s

# Object files for target ui
ui_OBJECTS = \
"CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.o"

# External object files for target ui
ui_EXTERNAL_OBJECTS =

../bin/libui.a: CMakeFiles/ui.dir/ui_autogen/mocs_compilation.cpp.o
../bin/libui.a: CMakeFiles/ui.dir/build.make
../bin/libui.a: CMakeFiles/ui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../bin/libui.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ui.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ui.dir/build: ../bin/libui.a
.PHONY : CMakeFiles/ui.dir/build

CMakeFiles/ui.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ui.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ui.dir/clean

CMakeFiles/ui.dir/depend:
	cd "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter" "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter" "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug" "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug" "/mnt/d/OneDrive/OneDrive - MSFT/Codes_Qt/mysql_connecter/cmake-build-wsl_debug/CMakeFiles/ui.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ui.dir/depend
