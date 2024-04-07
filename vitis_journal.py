#-----------------------------------------------------------------
# Vitis v2023.1 (64-bit)
# Start of session at: Sun Apr  7 08:10:25 2024
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
session.targets()
session.targets("--set", filter="name =~ *MPCore #0*")
#[Out]# <xsdb._target.Target at 0x7f55019b8eb0>
a9_0 = session.targets("--set", filter="name =~ *MPCore #0*")
session.rst(type='cores')
a9_0.dow("camera_platform/zynq_fsbl/build/fsbl.elf")
a9_0.con()
a9_0.dow("camera_program/build/camera_program.elf")
a9_0.con()
vitis.dispose()
