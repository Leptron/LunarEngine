# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/akshantlanjewar/Downloads/glfw-3.3.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/akshantlanjewar/Downloads/glfw-3.3.2

# Include any dependencies generated for this target.
include examples/CMakeFiles/sharing.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/sharing.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/sharing.dir/flags.make

examples/CMakeFiles/sharing.dir/sharing.c.o: examples/CMakeFiles/sharing.dir/flags.make
examples/CMakeFiles/sharing.dir/sharing.c.o: examples/sharing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/Downloads/glfw-3.3.2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/sharing.dir/sharing.c.o"
	cd /home/akshantlanjewar/Downloads/glfw-3.3.2/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sharing.dir/sharing.c.o   -c /home/akshantlanjewar/Downloads/glfw-3.3.2/examples/sharing.c

examples/CMakeFiles/sharing.dir/sharing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sharing.dir/sharing.c.i"
	cd /home/akshantlanjewar/Downloads/glfw-3.3.2/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/akshantlanjewar/Downloads/glfw-3.3.2/examples/sharing.c > CMakeFiles/sharing.dir/sharing.c.i

examples/CMakeFiles/sharing.dir/sharing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sharing.dir/sharing.c.s"
	cd /home/akshantlanjewar/Downloads/glfw-3.3.2/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/akshantlanjewar/Downloads/glfw-3.3.2/examples/sharing.c -o CMakeFiles/sharing.dir/sharing.c.s

examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o: examples/CMakeFiles/sharing.dir/flags.make
examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o: deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/Downloads/glfw-3.3.2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o"
	cd /home/akshantlanjewar/Downloads/glfw-3.3.2/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sharing.dir/__/deps/glad_gl.c.o   -c /home/akshantlanjewar/Downloads/glfw-3.3.2/deps/glad_gl.c

examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sharing.dir/__/deps/glad_gl.c.i"
	cd /home/akshantlanjewar/Downloads/glfw-3.3.2/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/akshantlanjewar/Downloads/glfw-3.3.2/deps/glad_gl.c > CMakeFiles/sharing.dir/__/deps/glad_gl.c.i

examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sharing.dir/__/deps/glad_gl.c.s"
	cd /home/akshantlanjewar/Downloads/glfw-3.3.2/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/akshantlanjewar/Downloads/glfw-3.3.2/deps/glad_gl.c -o CMakeFiles/sharing.dir/__/deps/glad_gl.c.s

# Object files for target sharing
sharing_OBJECTS = \
"CMakeFiles/sharing.dir/sharing.c.o" \
"CMakeFiles/sharing.dir/__/deps/glad_gl.c.o"

# External object files for target sharing
sharing_EXTERNAL_OBJECTS =

examples/sharing: examples/CMakeFiles/sharing.dir/sharing.c.o
examples/sharing: examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o
examples/sharing: examples/CMakeFiles/sharing.dir/build.make
examples/sharing: src/libglfw3.a
examples/sharing: /usr/lib/libm.so
examples/sharing: /usr/lib/librt.so
examples/sharing: /usr/lib/libm.so
examples/sharing: /usr/lib/libX11.so
examples/sharing: examples/CMakeFiles/sharing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/akshantlanjewar/Downloads/glfw-3.3.2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable sharing"
	cd /home/akshantlanjewar/Downloads/glfw-3.3.2/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sharing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/sharing.dir/build: examples/sharing

.PHONY : examples/CMakeFiles/sharing.dir/build

examples/CMakeFiles/sharing.dir/clean:
	cd /home/akshantlanjewar/Downloads/glfw-3.3.2/examples && $(CMAKE_COMMAND) -P CMakeFiles/sharing.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/sharing.dir/clean

examples/CMakeFiles/sharing.dir/depend:
	cd /home/akshantlanjewar/Downloads/glfw-3.3.2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/akshantlanjewar/Downloads/glfw-3.3.2 /home/akshantlanjewar/Downloads/glfw-3.3.2/examples /home/akshantlanjewar/Downloads/glfw-3.3.2 /home/akshantlanjewar/Downloads/glfw-3.3.2/examples /home/akshantlanjewar/Downloads/glfw-3.3.2/examples/CMakeFiles/sharing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/sharing.dir/depend
