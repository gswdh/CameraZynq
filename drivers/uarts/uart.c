#include "uart.h"

#include "xparameters.h"
#include "xuartlite.h"
#include "xaxidma.h"

#include "FreeRTOS.h"
#include "task.h"

#include "log.h"

#include <stdbool.h>
#include <stdio.h>

#define LOG_TAG "UART"

static XUartLite uart_0 = {0};
static XUartLite uart_1 = {0};

static XAxiDma dma = {0};

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

    // Test the DMA UART
    XAxiDma_Config *dma_config = XAxiDma_LookupConfig(XPAR_PERIPHERALS_0_AXI_DMA_0_DEVICE_ID);
    status = XAxiDma_CfgInitialize(&dma, dma_config);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiDma_CfgInitialize failed with %d\r\n", status);
        return;
    }
    XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
    XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

    // Use the UART IP
    config = XUartLite_LookupConfig(XPAR_UARTLITE_0_DEVICE_ID);
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

#define DMA_DATA_LEN (32)

void uart_dma_test(void)
{

    vTaskDelay(pdMS_TO_TICKS(1000));
    log_info(LOG_TAG, "starting uart_dma_test\n");

    uint8_t *tx_data[DMA_DATA_LEN] = {0};
    uint8_t *rx_data[DMA_DATA_LEN] = {0};
    sprintf((char *)tx_data, "Hello world");
    Xil_DCacheFlushRange((UINTPTR)tx_data, DMA_DATA_LEN);
    Xil_DCacheFlushRange((UINTPTR)rx_data, DMA_DATA_LEN);
    int status = XST_FAILURE;

    status = XAxiDma_SimpleTransfer(&dma, (UINTPTR)rx_data, DMA_DATA_LEN, XAXIDMA_DEVICE_TO_DMA);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiDma_SimpleTransfer RX fail = %d\n", status);
        return;
    }

    status = XAxiDma_SimpleTransfer(&dma, (UINTPTR)tx_data, DMA_DATA_LEN, XAXIDMA_DMA_TO_DEVICE);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiDma_SimpleTransfer TX fail = %d\n", status);
        return;
    }

    while (true)
    {
        if (!(XAxiDma_Busy(&dma, XAXIDMA_DEVICE_TO_DMA)) && !(XAxiDma_Busy(&dma, XAXIDMA_DMA_TO_DEVICE)))
        {
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    log_info(LOG_TAG, "TXd message = %s\n", (const char *)tx_data);
    log_info(LOG_TAG, "RXd message = %s\n", (const char *)rx_data);
}
