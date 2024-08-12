/******************************************************************************
 * Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
 * SPDX-License-Identifier: MIT
 ******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include "platform.h"

#include "xparameters.h"
#include "xil_printf.h"
#include "xiicps.h"

#include <unistd.h>
#include <stdio.h>

int main()
{
    init_platform();

    XIicPs_Config *iic_config = XIicPs_LookupConfig(XPAR_PS7_I2C_0_DEVICE_ID);
    if (iic_config == NULL)
    {
        printf("XIicPs_LookupConfig iic_config = NULL\n");
    }

    XIicPs iic = {0};
    int status = XIicPs_CfgInitialize(&iic, iic_config, iic_config->BaseAddress);
    printf("XIicPs_CfgInitialize status = %d\n", status);

    status = XIicPs_SelfTest(&iic);
    printf("XIicPs_SelfTest status = %d\n", status);

    XIicPs_SetSClk(&iic, 100000);

    uint8_t data[10] = {0};
    status = XIicPs_MasterSendPolled(&iic, (u8 *)data, sizeof(data), 0x83);
    printf("XIicPs_MasterSendPolled status = %d\n", status);

    while (1)
    {
        xil_printf("Hello World\n\r");

        sleep(1);
    }

    cleanup_platform();

    return 0;
}
