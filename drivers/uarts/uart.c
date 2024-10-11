#include "uart.h"

#include "xparameters.h"
#include "xuartlite.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"

#include "FreeRTOS.h"
#include "stream_buffer.h"

#include "log.h"

#include <stdbool.h>
#include <stdio.h>

#define LOG_TAG "UART"

static StreamBufferHandle_t uart_0_stream = NULL;

extern XScuGic xInterruptController;

static XUartLite uart_0 = {0};
static XUartLite uart_1 = {0};

static uint32_t tx_cntr = 0;
static uint32_t rx_cntr = 0;

static XUartLite *uart_get_handle(uart_port_t port)
{
    switch (port)
    {
    case UART_PORT_0:
        return &uart_0;
        break;
    // case UART_PORT_1:
    //     return &uart_1;
    //     break;
    default:
        return NULL;
        break;
    }

    return NULL;
}

static void uart_tx_handler(void *ref, unsigned int context)
{
    return;
}

static void uart_rx_handler(void *ref, unsigned int context)
{
    xStreamBufferSendFromISR(uart_0_stream, (void *)&context, 1, NULL);
}

void uart_init(void)
{
    // Make a queue for the RX uart 0 data
    uart_0_stream = xStreamBufferCreate(UART_0_BUFFER_LEN, 0);

    int status = XST_FAILURE;
    XUartLite_Config *config = NULL;

    // Use the UART IP
    status = XUartLite_Initialize(&uart_0, XPAR_PERIPHERALS_0_AXI_UARTLITE_PMC_DEVICE_ID);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "UART 0 init failed with code = %d\n", status);
    }

    status = XUartLite_SelfTest(&uart_0);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "UART 0 self test failed with code = %d\n", status);
    }

    XScuGic *gic = &xInterruptController;

    XScuGic_SetPriorityTriggerType(gic, XPAR_FABRIC_PERIPHERALS_0_AXI_UARTLITE_PMC_INTERRUPT_INTR,
                                   0xA0, 0x3);

    status = XScuGic_Connect(gic, XPAR_FABRIC_PERIPHERALS_0_AXI_UARTLITE_PMC_INTERRUPT_INTR,
                             (Xil_ExceptionHandler)XUartLite_InterruptHandler, (void *)&uart_0);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XScuGic_Connect failed with code = %d\n", status);
    }

    XScuGic_Enable(gic, XPAR_FABRIC_PERIPHERALS_0_AXI_UARTLITE_PMC_INTERRUPT_INTR);

    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, gic);
    Xil_ExceptionEnable();

    XUartLite_SetSendHandler(&uart_0, uart_tx_handler, &uart_0);
    XUartLite_SetRecvHandler(&uart_0, uart_rx_handler, &uart_0);

    XUartLite_EnableInterrupt(&uart_0);

    // // Use the UART IP
    // config = XUartLite_LookupConfig(XPAR_PERIPHERALS_0_AXI_UARTLITE_ESP_DEVICE_ID);
    // status = XUartLite_CfgInitialize(&uart_1, config, config->RegBaseAddr);
    // if (status != XST_SUCCESS)
    // {
    //     log_error(LOG_TAG, "UART 1 init failed with code = %d\n", status);
    // }

    log_info(LOG_TAG, "init done\n");
}

void uart_send(uart_port_t port, uint8_t *data, uint32_t len)
{
    XUartLite *uart = uart_get_handle(port);

    if (uart == NULL)
    {
        return;
    }

    uint32_t sent = XUartLite_Send(uart, data, len);
}

uint32_t uart_receive(uart_port_t port, uint8_t *data, uint32_t len)
{
    return xStreamBufferReceive(uart_0_stream, (void *)data, 1, pdMS_TO_TICKS(10));
}
