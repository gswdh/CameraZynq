import xsdb
session = xsdb.start_debug_session()
session.connect(url="TCP:127.0.0.1:3121")

# Add the ARM core to the jtag connection
#jtag = session.jtag_target(filter='name==arm_dap')

# Load the FPGA bitstream
session.targets("--set", filter="name =~ *xc7*")
session.fpga(file="camera_platform/hw/sdt/top_wrapper.bit")

# Download FSBL to A9 #0, block untill FSBL completes
a9_0 = session.targets("--set", filter="name =~ *MPCore #0*")
session.rst(type='cores')
a9_0.dow("camera_platform/zynq_fsbl/build/fsbl.elf")
#a9_0.con("--block", timeout=3)
a9_0.con()

# Download hello world to A53 #0
a9_0.dow("camera_program/build/camera_program.elf")
a9_0.con()
