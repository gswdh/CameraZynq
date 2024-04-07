#-----------------------------------------------------------------
# Vitis v2023.1 (64-bit)
# Start of session at: Sun Apr  7 20:09:50 2024
# Current directory: /home/test/Projects/CameraZynq
# Command line: vitis -i
# Journal file: vitis_journal.py
# Batch mode: $XILINX_VITIS/bin/vitis -new -s /home/test/Projects/CameraZynq/vitis_journal.py
#-----------------------------------------------------------------

#!/usr/bin/env python3
import vitis
import xsdb
session = xsdb.start_debug_session()
session.connect(url="TCP:127.0.0.1:3121")
#[Out]# 'tcfchan#0'
targets
session.targets
#[Out]# <bound method Session.targets of <xsdb.Session object at 0x7fb56f4550d0>>
session.targets()
session.fpga()
session.fpga
#[Out]# <bound method Target.fpga of <xsdb.Session object at 0x7fb56f4550d0>>
session.targets("--set", filter="name =~ *xc7z020*")
#[Out]# <xsdb._target.Target at 0x7fb56fcb68e0>
session.fpga()
session.fpga(file="/camera_platform/hw/sdt/top_wrapper.bit")
session.fpga(file="camera_platform/hw/sdt/top_wrapper.bit")
vitis.dispose()
