
cmake_minimum_required(VERSION 3.15)
project(bsp)
        
set(DRIVER_TARGETS gpio;uartlite;coresightps_dcc;devcfg;dmaps;emacps;scugic;qspips;scutimer;scuwdt;sdps;ttcps;uartps;usbps;xadcps)
set(DRIVER_LOCATIONS /home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/gpio_v4_10;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/uartlite_v3_9;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/coresightps_dcc_v1_9;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/devcfg_v3_8;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/dmaps_v2_9;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/emacps_v3_19;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/scugic_v5_2;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/qspips_v3_11;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/scutimer_v2_5;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/scuwdt_v2_5;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/sdps_v4_2;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/ttcps_v3_18;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/uartps_v3_13;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/usbps_v2_8;/home/test/Xilinx/Vitis/2023.2/data/embeddedsw/XilinxProcessorIPLib/drivers/xadcps_v2_7)

list(LENGTH DRIVER_TARGETS no_of_drivers)
set(index 0)

while(${index} LESS ${no_of_drivers})
    list(GET DRIVER_TARGETS ${index} drv)
    list(GET DRIVER_LOCATIONS ${index} drv_dir)
    set(exp_dir "${drv_dir}/examples")
    add_custom_target(
        ${drv}_example ALL
        COMMAND lopper -f -O /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/libsrc/${drv} /home/test/Projects/CameraZynq/camera_platform/ps7_cortexa9_0/freertos_ps7_cortexa9_0/bsp/hw_artifacts/ps7_cortexa9_0_baremetal.dts -- bmcmake_metadata_xlnx ps7_cortexa9_0 ${exp_dir} drvcmake_metadata
        BYPRODUCTS x${drv}_exlist.yaml)
    MATH(EXPR index "${index}+1")
endwhile()
