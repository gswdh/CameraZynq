# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /home/test/Xilinx/Vitis/2023.2/tps/lnx64/cmake-3.24.2/bin/cmake

# The command to remove a file.
RM = /home/test/Xilinx/Vitis/2023.2/tps/lnx64/cmake-3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp

# Utility rule file for ttcps.

# Include any custom commands dependencies for this target.
include CMakeFiles/ttcps.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ttcps.dir/progress.make

CMakeFiles/ttcps:
	lopper -O /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/ttcps/src /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/hw_artifacts/ps7_cortexa9_1_baremetal.dts -- baremetalconfig_xlnx ps7_cortexa9_1 /home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/ttcps_v3_18/src

ttcps: CMakeFiles/ttcps
ttcps: CMakeFiles/ttcps.dir/build.make
.PHONY : ttcps

# Rule to build all files generated by this target.
CMakeFiles/ttcps.dir/build: ttcps
.PHONY : CMakeFiles/ttcps.dir/build

CMakeFiles/ttcps.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ttcps.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ttcps.dir/clean

CMakeFiles/ttcps.dir/depend:
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/CMakeFiles/ttcps.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ttcps.dir/depend

