#-----------------------------------------------------------------
# Vitis v2023.1 (64-bit)
# Start of session at: Sat Mar 30 22:20:25 2024
# Current directory: /home/test/Projects/CameraZynq
# Command line: vitis -i
# Journal file: vitis_journal.py
# Batch mode: $XILINX_VITIS/bin/vitis -new -s /home/test/Projects/CameraZynq/vitis_journal.py
#-----------------------------------------------------------------

#!/usr/bin/env python3
import vitis
import vitis
client = vitis.create_client()
client.set_workspace(".")
client.set_workspace(".")
#[Out]# True
client.list_components()
#[Out]# component {
#[Out]#   component_location: "/home/test/Projects/CameraZynq/camera_program"
#[Out]#   component_name: "camera_program"
#[Out]#   component_type: HOST
#[Out]#   platform: "/home/test/Projects/CameraZynq/camera_platform/export/camera_platform/camera_platform.xpfm"
#[Out]#   domain: "freertos_ps7_cortexa9_0"
#[Out]#   cpu_instance: "ps7_cortexa9_0"
#[Out]#   cpu_type: "cortex-a9"
#[Out]#   os: "freertos"
#[Out]#   application_flow: EMBEDDED
#[Out]#   domainRealName: "freertos_ps7_cortexa9_0"
#[Out]# }
#[Out]# component {
#[Out]#   component_location: "/home/test/Projects/CameraZynq/camera_platform"
#[Out]#   component_name: "camera_platform"
#[Out]#   component_type: PLATFORM
#[Out]# }
client.get_component("camera_program")
#[Out]# 'component_location': '/home/test/Projects/CameraZynq/camera_program'
#[Out]# 'component_name': 'camera_program'
app = client.get_component("camera_program")
app
#[Out]# 'component_location': '/home/test/Projects/CameraZynq/camera_program'
#[Out]# 'component_name': 'camera_program'
app.build()
#[Out]# 1
q
vitis.dispose()
