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

# Utility rule file for usbps_example.

# Include any custom commands dependencies for this target.
include CMakeFiles/usbps_example.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/usbps_example.dir/progress.make

CMakeFiles/usbps_example:
	lopper -f -O /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/usbps /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/hw_artifacts/ps7_cortexa9_0_baremetal.dts -- bmcmake_metadata_xlnx ps7_cortexa9_0 /home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/usbps_v2_8/examples drvcmake_metadata

usbps_example: CMakeFiles/usbps_example
usbps_example: CMakeFiles/usbps_example.dir/build.make
.PHONY : usbps_example

# Rule to build all files generated by this target.
CMakeFiles/usbps_example.dir/build: usbps_example
.PHONY : CMakeFiles/usbps_example.dir/build

CMakeFiles/usbps_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/usbps_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/usbps_example.dir/clean

CMakeFiles/usbps_example.dir/depend:
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/build_configs/exmetadata/CMakeFiles/usbps_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/usbps_example.dir/depend

