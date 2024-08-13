# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/george/Projects/CameraZynq/platform/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/george/Projects/CameraZynq/platform/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {platform}\
-hw {/home/george/Projects/CameraFPGA/camera.xsa}\
-proc {ps7_cortexa9_0} -os {freertos10_xilinx} -out {/home/george/Projects/CameraZynq}

platform write
platform generate -domains 
platform active {platform}
platform generate
bsp reload
bsp setlib -name xilffs -ver 5.2
bsp setlib -name lwip220 -ver 1.0
bsp config api_mode "SOCKET_API"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_domain 
