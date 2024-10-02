#include "uart.h"

#include "xparameters.h"
#include "xaxidma.h"

#include "FreeRTOS.h"
#include "task.h"

#include "log.h"

#include <stdbool.h>
#include <stdio.h>

#define LOG_TAG "UART"

static XAxiDma dma = {0};

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

    // Test the DMA UART
    XAxiDma_Config *dma_config = XAxiDma_LookupConfig(XPAR_AXI_DMA_PMC_UART_DEVICE_ID);
    status = XAxiDma_CfgInitialize(&dma, dma_config);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiDma_CfgInitialize failed with %d\r\n", status);
        return;
    }
    XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
    XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

    log_info(LOG_TAG, "init done\n");
}

void uart_send(uart_port_t port, uint8_t *data, uint32_t len)
{
    // XUartLite *uart = uart_get_handle(port);

    // if (uart == NULL)
    // {
    //     return;
    // }

    // uint32_t sent = XUartLite_Send(uart, data, len);
}

uint32_t uart_receive(uart_port_t port, uint8_t *data, uint32_t len)
{
    // XUartLite *uart = uart_get_handle(port);

    // if (uart == NULL)
    // {
    //     return 0;
    // }

    // return XUartLite_Recv(uart, data, len);

    return 0;
}

#define DMA_DATA_LEN (32)

void uart_dma_test(void)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
    log_info(LOG_TAG, "starting uart_dma_test\n");

    uint8_t some_data[32] = "hello world";
    log_info(LOG_TAG, "some_data = %p\n", some_data);

    uint8_t *tx_data = (uint8_t *)malloc(DMA_DATA_LEN);
    uint8_t *rx_data = (uint8_t *)malloc(DMA_DATA_LEN);
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

    while (XAxiDma_Busy(&dma, XAXIDMA_DMA_TO_DEVICE))
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    log_info(LOG_TAG, "TX done\n");

    while (XAxiDma_Busy(&dma, XAXIDMA_DEVICE_TO_DMA))
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    log_info(LOG_TAG, "RX done\n");

    log_info(LOG_TAG, "TXd message = %s\n", (const char *)tx_data);
    log_info(LOG_TAG, "RXd message = %s\n", (const char *)rx_data);

    free(tx_data);
    free(rx_data);
}
