# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/johanna/catkin_mmc/src/mavlink

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/johanna/catkin_mmc/build/mavlink

# Utility rule file for paparazzi.xml-v1.0.

# Include any custom commands dependencies for this target.
include CMakeFiles/paparazzi.xml-v1.0.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/paparazzi.xml-v1.0.dir/progress.make

CMakeFiles/paparazzi.xml-v1.0: include/v1.0/paparazzi/paparazzi.h

include/v1.0/paparazzi/paparazzi.h: /home/johanna/catkin_mmc/src/mavlink/message_definitions/v1.0/paparazzi.xml
include/v1.0/paparazzi/paparazzi.h: /home/johanna/catkin_mmc/src/mavlink/message_definitions/v1.0/common.xml
include/v1.0/paparazzi/paparazzi.h: /home/johanna/catkin_mmc/src/mavlink/pymavlink/tools/mavgen.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/johanna/catkin_mmc/build/mavlink/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating include/v1.0/paparazzi/paparazzi.h"
	/usr/bin/env PYTHONPATH="/home/johanna/catkin_mmc/src/mavlink:/opt/ros/melodic/lib/python2.7/dist-packages" /usr/bin/python2.7 /home/johanna/catkin_mmc/src/mavlink/pymavlink/tools/mavgen.py --lang=C --wire-protocol=1.0 --output=include/v1.0 /home/johanna/catkin_mmc/src/mavlink/message_definitions/v1.0/paparazzi.xml

paparazzi.xml-v1.0: CMakeFiles/paparazzi.xml-v1.0
paparazzi.xml-v1.0: include/v1.0/paparazzi/paparazzi.h
paparazzi.xml-v1.0: CMakeFiles/paparazzi.xml-v1.0.dir/build.make
.PHONY : paparazzi.xml-v1.0

# Rule to build all files generated by this target.
CMakeFiles/paparazzi.xml-v1.0.dir/build: paparazzi.xml-v1.0
.PHONY : CMakeFiles/paparazzi.xml-v1.0.dir/build

CMakeFiles/paparazzi.xml-v1.0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/paparazzi.xml-v1.0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/paparazzi.xml-v1.0.dir/clean

CMakeFiles/paparazzi.xml-v1.0.dir/depend:
	cd /home/johanna/catkin_mmc/build/mavlink && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/johanna/catkin_mmc/src/mavlink /home/johanna/catkin_mmc/src/mavlink /home/johanna/catkin_mmc/build/mavlink /home/johanna/catkin_mmc/build/mavlink /home/johanna/catkin_mmc/build/mavlink/CMakeFiles/paparazzi.xml-v1.0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/paparazzi.xml-v1.0.dir/depend

