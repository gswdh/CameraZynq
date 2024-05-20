#include "uart.h"

#include "xparameters.h"
#include "xstatus.h"
#include "xuartlite.h"
#include "xil_printf.h"

static XUartLite fpga_uart = {0};

void uart_init()
{
    int status = XUartLite_Initialize(&fpga_uart, XPAR_PERIPHERALS_0_AXI_UARTLITE_0_BASEADDR);

    status = XUartLite_SelfTest(&fpga_uart);
    if (status != XST_SUCCESS)
    {
        return;
    }
}

void uart_tx(uint8_t *data, uint32_t len)
{
    XUartLite_Send(&fpga_uart, (u8 *)data, (unsigned int)len);
}

uint32_t uart_rx(uint8_t *data, uint32_t len)
{
    return (uint32_t)XUartLite_Recv(&fpga_uart, (u8 *)data, (unsigned int)len);
}
