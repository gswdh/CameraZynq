#!/usr/bin/env python3
import vitis
import os
import time
import shutil
from datetime import datetime

print ("\n-----------------------------------------------------")
print ("Application component use case: Component creation and building\n")

# Create a client object -
client = vitis.create_client()

# Set workspace
date = datetime.now().strftime("%Y%m%d%I%M%S")
workspace = '/home/test/Projects/CameraZynq/'
comp_name = "camera_proc"



# Build component
app_test_comp.build()

# Clean the component
app_test_comp.clean()

# Close the client connection and terminate the vitis server
vitis.dispose()
