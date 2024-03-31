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

# Include any dependencies generated for this target.
include libsrc/xilffs/src/CMakeFiles/xilffs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include libsrc/xilffs/src/CMakeFiles/xilffs.dir/compiler_depend.make

# Include the progress variables for this target.
include libsrc/xilffs/src/CMakeFiles/xilffs.dir/progress.make

# Include the compile flags for this target's objects.
include libsrc/xilffs/src/CMakeFiles/xilffs.dir/flags.make

libsrc/xilffs/src/CMakeFiles/xilffs.dir/diskio.c.obj: libsrc/xilffs/src/CMakeFiles/xilffs.dir/flags.make
libsrc/xilffs/src/CMakeFiles/xilffs.dir/diskio.c.obj: /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/diskio.c
libsrc/xilffs/src/CMakeFiles/xilffs.dir/diskio.c.obj: libsrc/xilffs/src/CMakeFiles/xilffs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libsrc/xilffs/src/CMakeFiles/xilffs.dir/diskio.c.obj"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT libsrc/xilffs/src/CMakeFiles/xilffs.dir/diskio.c.obj -MF CMakeFiles/xilffs.dir/diskio.c.obj.d -o CMakeFiles/xilffs.dir/diskio.c.obj -c /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/diskio.c

libsrc/xilffs/src/CMakeFiles/xilffs.dir/diskio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xilffs.dir/diskio.c.i"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/diskio.c > CMakeFiles/xilffs.dir/diskio.c.i

libsrc/xilffs/src/CMakeFiles/xilffs.dir/diskio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xilffs.dir/diskio.c.s"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/diskio.c -o CMakeFiles/xilffs.dir/diskio.c.s

libsrc/xilffs/src/CMakeFiles/xilffs.dir/ff.c.obj: libsrc/xilffs/src/CMakeFiles/xilffs.dir/flags.make
libsrc/xilffs/src/CMakeFiles/xilffs.dir/ff.c.obj: /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ff.c
libsrc/xilffs/src/CMakeFiles/xilffs.dir/ff.c.obj: libsrc/xilffs/src/CMakeFiles/xilffs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libsrc/xilffs/src/CMakeFiles/xilffs.dir/ff.c.obj"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT libsrc/xilffs/src/CMakeFiles/xilffs.dir/ff.c.obj -MF CMakeFiles/xilffs.dir/ff.c.obj.d -o CMakeFiles/xilffs.dir/ff.c.obj -c /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ff.c

libsrc/xilffs/src/CMakeFiles/xilffs.dir/ff.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xilffs.dir/ff.c.i"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ff.c > CMakeFiles/xilffs.dir/ff.c.i

libsrc/xilffs/src/CMakeFiles/xilffs.dir/ff.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xilffs.dir/ff.c.s"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ff.c -o CMakeFiles/xilffs.dir/ff.c.s

libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffsystem.c.obj: libsrc/xilffs/src/CMakeFiles/xilffs.dir/flags.make
libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffsystem.c.obj: /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ffsystem.c
libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffsystem.c.obj: libsrc/xilffs/src/CMakeFiles/xilffs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffsystem.c.obj"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffsystem.c.obj -MF CMakeFiles/xilffs.dir/ffsystem.c.obj.d -o CMakeFiles/xilffs.dir/ffsystem.c.obj -c /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ffsystem.c

libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffsystem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xilffs.dir/ffsystem.c.i"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ffsystem.c > CMakeFiles/xilffs.dir/ffsystem.c.i

libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffsystem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xilffs.dir/ffsystem.c.s"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ffsystem.c -o CMakeFiles/xilffs.dir/ffsystem.c.s

libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffunicode.c.obj: libsrc/xilffs/src/CMakeFiles/xilffs.dir/flags.make
libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffunicode.c.obj: /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ffunicode.c
libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffunicode.c.obj: libsrc/xilffs/src/CMakeFiles/xilffs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffunicode.c.obj"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffunicode.c.obj -MF CMakeFiles/xilffs.dir/ffunicode.c.obj.d -o CMakeFiles/xilffs.dir/ffunicode.c.obj -c /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ffunicode.c

libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffunicode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xilffs.dir/ffunicode.c.i"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ffunicode.c > CMakeFiles/xilffs.dir/ffunicode.c.i

libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffunicode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xilffs.dir/ffunicode.c.s"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && /home/test/Xilinx/Vitis/2023.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src/ffunicode.c -o CMakeFiles/xilffs.dir/ffunicode.c.s

# Object files for target xilffs
xilffs_OBJECTS = \
"CMakeFiles/xilffs.dir/diskio.c.obj" \
"CMakeFiles/xilffs.dir/ff.c.obj" \
"CMakeFiles/xilffs.dir/ffsystem.c.obj" \
"CMakeFiles/xilffs.dir/ffunicode.c.obj"

# External object files for target xilffs
xilffs_EXTERNAL_OBJECTS =

libsrc/xilffs/src/libxilffs.a: libsrc/xilffs/src/CMakeFiles/xilffs.dir/diskio.c.obj
libsrc/xilffs/src/libxilffs.a: libsrc/xilffs/src/CMakeFiles/xilffs.dir/ff.c.obj
libsrc/xilffs/src/libxilffs.a: libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffsystem.c.obj
libsrc/xilffs/src/libxilffs.a: libsrc/xilffs/src/CMakeFiles/xilffs.dir/ffunicode.c.obj
libsrc/xilffs/src/libxilffs.a: libsrc/xilffs/src/CMakeFiles/xilffs.dir/build.make
libsrc/xilffs/src/libxilffs.a: libsrc/xilffs/src/CMakeFiles/xilffs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libxilffs.a"
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && $(CMAKE_COMMAND) -P CMakeFiles/xilffs.dir/cmake_clean_target.cmake
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xilffs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libsrc/xilffs/src/CMakeFiles/xilffs.dir/build: libsrc/xilffs/src/libxilffs.a
.PHONY : libsrc/xilffs/src/CMakeFiles/xilffs.dir/build

libsrc/xilffs/src/CMakeFiles/xilffs.dir/clean:
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src && $(CMAKE_COMMAND) -P CMakeFiles/xilffs.dir/cmake_clean.cmake
.PHONY : libsrc/xilffs/src/CMakeFiles/xilffs.dir/clean

libsrc/xilffs/src/CMakeFiles/xilffs.dir/depend:
	cd /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/xilffs/src /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_1/george/bsp/libsrc/build_configs/gen_bsp/libsrc/xilffs/src/CMakeFiles/xilffs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libsrc/xilffs/src/CMakeFiles/xilffs.dir/depend

