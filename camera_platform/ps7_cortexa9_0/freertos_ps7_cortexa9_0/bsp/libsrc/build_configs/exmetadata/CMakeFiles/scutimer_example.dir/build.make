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
CMAKE_SOURCE_DIR = /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata

# Utility rule file for scutimer_example.

# Include any custom commands dependencies for this target.
include CMakeFiles/scutimer_example.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/scutimer_example.dir/progress.make

CMakeFiles/scutimer_example:
	lopper -f -O /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/scutimer /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/hw_artifacts/ps7_cortexa9_0_baremetal.dts -- bmcmake_metadata_xlnx ps7_cortexa9_0 /home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/scutimer_v2_5/examples drvcmake_metadata

scutimer_example: CMakeFiles/scutimer_example
scutimer_example: CMakeFiles/scutimer_example.dir/build.make
.PHONY : scutimer_example

# Rule to build all files generated by this target.
CMakeFiles/scutimer_example.dir/build: scutimer_example
.PHONY : CMakeFiles/scutimer_example.dir/build

CMakeFiles/scutimer_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/scutimer_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/scutimer_example.dir/clean

CMakeFiles/scutimer_example.dir/depend:
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata/CMakeFiles/scutimer_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/scutimer_example.dir/depend

