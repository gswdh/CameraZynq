

proc generate {drv_handle} {
	xdefine_include_file $drv_handle "xparameters.h" "spi_dma" "NUM_INSTANCES" "DEVICE_ID"  "C_CONTROL_BASEADDR" "C_CONTROL_HIGHADDR"
}
