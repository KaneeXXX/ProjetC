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
include CMakeFiles/button.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/button.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/button.dir/flags.make

CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.o: CMakeFiles/button.dir/flags.make
CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.o: /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.o -c /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c

CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c > CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.i

CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c -o CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.s

# Object files for target button
button_OBJECTS = \
"CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.o"

# External object files for target button
button_EXTERNAL_OBJECTS =

button: CMakeFiles/button.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/button.c.o
button: CMakeFiles/button.dir/build.make
button: libei.a
button: /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/_x11/libeibase.a
button: CMakeFiles/button.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable button"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/button.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/button.dir/build: button

.PHONY : CMakeFiles/button.dir/build

CMakeFiles/button.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/button.dir/cmake_clean.cmake
.PHONY : CMakeFiles/button.dir/clean

CMakeFiles/button.dir/depend:
	cd /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-release/CMakeFiles/button.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/button.dir/depend

