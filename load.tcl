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
connect
# -url tcp:localhost:3121

# Set up the device
set device [lindex [targets] 0]
puts "Using device: $device"

# Select the Zynq PS device
targets -set -nocase -filter {name =~ "ARM Cortex-A9 MPCore #0"}

# Reset the target
rst -system

# Source the ps7_init.tcl script for PS initialization
puts "Initializing Zynq PS using ps7_init.tcl..."
source platform/hw/ps7_init.tcl

ps7_init

# Load the FPGA bitstream
puts "Loading FPGA bitstream..."
fpga -f platform/hw/camera.bit

# Load the application binary to DDR
puts "Loading application binary..."
dow build/camera.elf

# # Set the PC to the entry point of the application
# puts "Setting PC to entry point..."
# # This assumes the entry point is at 0x00100000, adjust as needed
# mwr 0x00000030 0x00100000

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
    exit
} else {
    puts "XSDB session remains open as per the exit_after parameter."
}

puts "Done."
