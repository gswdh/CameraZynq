#include "uart.h"

#include "xparameters.h"
#include "xuartlite.h"

#include "FreeRTOS.h"
#include "task.h"

#include "log.h"

#include <stdbool.h>
#include <stdio.h>

#define LOG_TAG "UART"

static XUartLite uart_0 = {0};
static XUartLite uart_1 = {0};

static XUartLite *uart_get_handle(uart_port_t port)
{
    switch (port)
    {
    case UART_PORT_0:
        return &uart_0;
        break;
    case UART_PORT_1:
        return &uart_1;
        break;
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
    return;
}

void uart_init(void)
{
    int status = XST_FAILURE;
    XUartLite_Config *config = NULL;

    // Use the UART IP
    config = XUartLite_LookupConfig(XPAR_PERIPHERALS_0_AXI_UARTLITE_PMC_DEVICE_ID);
    status = XUartLite_CfgInitialize(&uart_0, config, config->RegBaseAddr);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "UART 0 init failed with code = %d\n", status);
    }

    // Use the UART IP
    config = XUartLite_LookupConfig(XPAR_PERIPHERALS_0_AXI_UARTLITE_ESP_DEVICE_ID);
    status = XUartLite_CfgInitialize(&uart_1, config, config->RegBaseAddr);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "UART 1 init failed with code = %d\n", status);
    }

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
    XUartLite *uart = uart_get_handle(port);

    if (uart == NULL)
    {
        return 0;
    }

    return XUartLite_Recv(uart, data, len);
}
