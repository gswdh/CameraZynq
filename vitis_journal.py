#-----------------------------------------------------------------
# Vitis v2023.1 (64-bit)
# Start of session at: Sun Apr  7 12:20:08 2024
# Current directory: /home/test/Projects/CameraZynq
# Command line: vitis -i
# Journal file: vitis_journal.py
# Batch mode: $XILINX_VITIS/bin/vitis -new -s /home/test/Projects/CameraZynq/vitis_journal.py
#-----------------------------------------------------------------

#!/usr/bin/env python3
import vitis
import vitias
import vitis
client = vitis.create_client()
client.set_workspace(".")
#[Out]# True
program = client.get_component("camera_program")
program
#[Out]# 'component_location': '/home/test/Projects/CameraZynq/camera_program'
#[Out]# 'component_name': 'camera_program'
program.report()
program.get_app_config
#[Out]# <bound method HostComponent.get_app_config of 'component_location': '/home/test/Projects/CameraZynq/camera_program'
#[Out]# 'component_name': 'camera_program'
#[Out]# >
program.get_app_config()
:q
vitis.dispose()
