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
CMAKE_BINARY_DIR = /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/frame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/frame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/frame.dir/flags.make

CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.o: CMakeFiles/frame.dir/flags.make
CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.o: /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.o -c /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c

CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c > CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.i

CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c -o CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.s

# Object files for target frame
frame_OBJECTS = \
"CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.o"

# External object files for target frame
frame_EXTERNAL_OBJECTS =

frame: CMakeFiles/frame.dir/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/tests/frame.c.o
frame: CMakeFiles/frame.dir/build.make
frame: libei.a
frame: /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/_x11/libeibase.a
frame: CMakeFiles/frame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable frame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/frame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/frame.dir/build: frame

.PHONY : CMakeFiles/frame.dir/build

CMakeFiles/frame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/frame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/frame.dir/clean

CMakeFiles/frame.dir/depend:
	cd /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-debug /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-debug /user/7/serafith/C/projetC/projetc/projet_c_ig.3.0.2/projet_c_ig/clion/cmake-build-debug/CMakeFiles/frame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/frame.dir/depend

