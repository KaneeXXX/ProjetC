# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /opt/clion-2021.1.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2021.1.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/two048.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/two048.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/two048.dir/flags.make

CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.o: CMakeFiles/two048.dir/flags.make
CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.o: /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.o -c /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c

CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c > CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.i

CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c -o CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.s

# Object files for target two048
two048_OBJECTS = \
"CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.o"

# External object files for target two048
two048_EXTERNAL_OBJECTS =

two048: CMakeFiles/two048.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/two048.c.o
two048: CMakeFiles/two048.dir/build.make
two048: libei.a
two048: /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/_x11/libeibase.a
two048: CMakeFiles/two048.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable two048"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/two048.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/two048.dir/build: two048

.PHONY : CMakeFiles/two048.dir/build

CMakeFiles/two048.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/two048.dir/cmake_clean.cmake
.PHONY : CMakeFiles/two048.dir/clean

CMakeFiles/two048.dir/depend:
	cd /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release/CMakeFiles/two048.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/two048.dir/depend

