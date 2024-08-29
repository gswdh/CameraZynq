# Function to parse named parameters
proc parse_args {argv} {
    # Initialize an empty dictionary
    array set params {}

    # Iterate over the argument list
    foreach arg $argv {
        # Split each argument into key and value
        if {[regexp {([^=]+)=(.*)} $arg -> key value]} {
            # Store in the dictionary
            set params($key) $value
        }
    }
    return [array get params]
}

# Parse the command-line arguments
set params [parse_args $argv]

# Set default values for optional parameters
set run_target "true"
set exit_after "false"

# Override with provided values if they exist
if {[dict exists $params run]} {
    set run_target [dict get $params run]
}
if {[dict exists $params exit]} {
    set exit_after [dict get $params exit]
}

# Connect to the HS3 JTAG debugger
connect -url tcp:127.0.0.1:3121
# -url tcp:localhost:3121

# Select the Zynq PS device
targets -set -nocase -filter {name =~"APU*"}

# Reset the target
rst -system
after 100

# Load the FPGA bitstream
puts "Loading FPGA bitstream..."
fpga -f platform/hw/camera.bit

# Setup the HW
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw /home/george/Projects/zynq_debug/platform/export/platform/hw/camera.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1

# Source the ps7_init.tcl script for PS initialization
puts "Initializing Zynq PS using ps7_init.tcl..."
targets -set -nocase -filter {name =~"APU*"}
source /home/george/Projects/zynq_debug/test/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config

# Load the application binary to DDR
puts "Loading application binary..."
targets -set -nocase -filter {name =~ "*A9*#0"}
dow build/camera.elf
configparams force-mem-access 0

# Run the application based on the run_target parameter
if {$run_target == "true"} {
    puts "Running application..."
    con
} else {
    puts "Application run skipped as per the run_target parameter."
}

# Exit XSDB based on the exit_after parameter
if {$exit_after == "true"} {
    puts "Exiting XSDB as per the exit_after parameter."
    puts "Done."
    exit
} else {
    puts "XSDB session remains open as per the exit_after parameter."
}

puts "Done."
