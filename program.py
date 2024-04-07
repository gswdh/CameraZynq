import xsdb
import time

session = xsdb.start_debug_session()
session.connect(url="TCP:127.0.0.1:3121")

# Add the ARM core to the jtag connection
#jtag = session.jtag_target(filter='name==arm_dap')

# Download FSBL to A9 #0, block untill FSBL completes
a9_0 = session.targets("--set", filter="name =~ *MPCore #0*")
session.rst(type='cores')
a9_0.dow("camera_platform/zynq_fsbl/build/fsbl.elf")
a9_0.con()

# Wait for the FSBL to run
time.sleep(3)

# Download hello world to A53 #0
a9_0.dow("camera_program/build/camera_program.elf")
a9_0.con()
