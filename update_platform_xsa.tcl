# Check if at least one argument is provided
if {[llength $argv] < 1} {
    puts "Usage: script_name.tcl <xsa_file>"
    exit 1
}

# Get the first command line argument and assign it to the variable XSA_FILE
set XSA_FILE [lindex $argv 0]

# Output the value of XSA_FILE for confirmation
puts "XSA_FILE is set to: $XSA_FILE"

platform read {platform/platform.spr}
platform active {platform}
platform config -updatehw $XSA_FILE