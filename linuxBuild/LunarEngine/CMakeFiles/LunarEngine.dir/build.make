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
CMAKE_SOURCE_DIR = /home/akshantlanjewar/code/LunarEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/akshantlanjewar/code/LunarEngine/linuxBuild

# Include any dependencies generated for this target.
include LunarEngine/CMakeFiles/LunarEngine.dir/depend.make

# Include the progress variables for this target.
include LunarEngine/CMakeFiles/LunarEngine.dir/progress.make

# Include the compile flags for this target's objects.
include LunarEngine/CMakeFiles/LunarEngine.dir/flags.make

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.o: ../LunarEngine/source/LunarBatching/StaticSquareBatch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarBatching/StaticSquareBatch.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarBatching/StaticSquareBatch.cpp > CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarBatching/StaticSquareBatch.cpp -o CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.o: ../LunarEngine/source/LunarEngine/LunarEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarEngine/LunarEngine.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarEngine/LunarEngine.cpp > CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarEngine/LunarEngine.cpp -o CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.o: ../LunarEngine/source/LunarManager/LunarAnimationManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarManager/LunarAnimationManager.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarManager/LunarAnimationManager.cpp > CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarManager/LunarAnimationManager.cpp -o CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.o: ../LunarEngine/source/LunarRenderer/LunarLayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarLayer.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarLayer.cpp > CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarLayer.cpp -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.o: ../LunarEngine/source/LunarRenderer/LunarObject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarObject.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarObject.cpp > CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarObject.cpp -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.o: ../LunarEngine/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp > CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.o: ../LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp > CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.o: ../LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp > CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.o: ../LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp > CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.o: ../LunarEngine/source/LunarRenderer/LunarShader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarShader.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarShader.cpp > CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarRenderer/LunarShader.cpp -o CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.o: ../LunarEngine/source/LunarUtils/LunarLogger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarLogger.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarLogger.cpp > CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarLogger.cpp -o CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.o: ../LunarEngine/source/LunarUtils/LunarShaderGen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarShaderGen.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarShaderGen.cpp > CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarShaderGen.cpp -o CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.o: ../LunarEngine/source/LunarUtils/LunarShaderManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarShaderManager.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarShaderManager.cpp > CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarShaderManager.cpp -o CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.o: ../LunarEngine/source/LunarUtils/LunarUtils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.o -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarUtils.cpp

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarUtils.cpp > CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/LunarUtils/LunarUtils.cpp -o CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.s

LunarEngine/CMakeFiles/LunarEngine.dir/source/glad.c.o: LunarEngine/CMakeFiles/LunarEngine.dir/flags.make
LunarEngine/CMakeFiles/LunarEngine.dir/source/glad.c.o: ../LunarEngine/source/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object LunarEngine/CMakeFiles/LunarEngine.dir/source/glad.c.o"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LunarEngine.dir/source/glad.c.o   -c /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/glad.c

LunarEngine/CMakeFiles/LunarEngine.dir/source/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LunarEngine.dir/source/glad.c.i"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/glad.c > CMakeFiles/LunarEngine.dir/source/glad.c.i

LunarEngine/CMakeFiles/LunarEngine.dir/source/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LunarEngine.dir/source/glad.c.s"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/akshantlanjewar/code/LunarEngine/LunarEngine/source/glad.c -o CMakeFiles/LunarEngine.dir/source/glad.c.s

# Object files for target LunarEngine
LunarEngine_OBJECTS = \
"CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.o" \
"CMakeFiles/LunarEngine.dir/source/glad.c.o"

# External object files for target LunarEngine
LunarEngine_EXTERNAL_OBJECTS =

LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarBatching/StaticSquareBatch.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarEngine/LunarEngine.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarManager/LunarAnimationManager.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarLayer.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarObject.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/LunarTexture.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteManager.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarPrimitives/SpriteSheetRenderer.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarRenderer/LunarShader.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarLogger.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderGen.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarShaderManager.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/LunarUtils/LunarUtils.cpp.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/source/glad.c.o
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/build.make
LunarEngine/libLunarEngine.a: LunarEngine/CMakeFiles/LunarEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/akshantlanjewar/code/LunarEngine/linuxBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX static library libLunarEngine.a"
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && $(CMAKE_COMMAND) -P CMakeFiles/LunarEngine.dir/cmake_clean_target.cmake
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LunarEngine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
LunarEngine/CMakeFiles/LunarEngine.dir/build: LunarEngine/libLunarEngine.a

.PHONY : LunarEngine/CMakeFiles/LunarEngine.dir/build

LunarEngine/CMakeFiles/LunarEngine.dir/clean:
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine && $(CMAKE_COMMAND) -P CMakeFiles/LunarEngine.dir/cmake_clean.cmake
.PHONY : LunarEngine/CMakeFiles/LunarEngine.dir/clean

LunarEngine/CMakeFiles/LunarEngine.dir/depend:
	cd /home/akshantlanjewar/code/LunarEngine/linuxBuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/akshantlanjewar/code/LunarEngine /home/akshantlanjewar/code/LunarEngine/LunarEngine /home/akshantlanjewar/code/LunarEngine/linuxBuild /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine /home/akshantlanjewar/code/LunarEngine/linuxBuild/LunarEngine/CMakeFiles/LunarEngine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : LunarEngine/CMakeFiles/LunarEngine.dir/depend

