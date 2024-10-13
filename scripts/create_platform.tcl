# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/george/Projects/zynq_debug/platform/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/george/Projects/zynq_debug/platform/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {platform}\
-hw {submodules/CameraFPGA/camera.xsa}\
-proc {ps7_cortexa9_0} -os {freertos10_xilinx} -out {.}

platform write
platform generate -domains 
bsp reload
bsp setlib -name xilffs -ver 5.2
bsp setlib -name lwip220 -ver 1.0
bsp config tick_rate "1000"
bsp config total_heap_size "1048576"
bsp config stream_buffer "true"
bsp config support_static_allocation "false"
bsp config num_logical_vol "2"
bsp config api_mode "SOCKET_API"
bsp config lwip_dhcp "true"
bsp config max_task_name_len "64"
bsp write
bsp reload
catch {bsp regenerate}