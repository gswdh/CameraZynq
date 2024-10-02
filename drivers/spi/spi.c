#include "spi.h"

#include "xparameters.h"
#include "xspi.h"
#include "xaxidma.h"

#include "log.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>

#define LOG_TAG "SPI"

static XAxiDma dma = {0};
static XSpi spi_0 = {0};
static XSpi spi_1 = {0};

static XSpi *spi_get_handle(spi_port_t port)
{
    switch (port)
    {
    case SPI_PORT_0:
        return &spi_0;
        break;
    case SPI_PORT_1:
        return &spi_1;
        break;
    default:
        return NULL;
        break;
    }

    return NULL;
}

void spi_init()
{

    int status = XST_FAILURE;

    // Test the DMA UART
    XAxiDma_Config *dma_config = XAxiDma_LookupConfig(XPAR_AXI_DMA_DSP_SPI_DEVICE_ID);
    status = XAxiDma_CfgInitialize(&dma, dma_config);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiDma_CfgInitialize failed with %d\r\n", status);
        return;
    }
    XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
    XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

    log_info(LOG_TAG, "init done\n");
    /*






    */

    XSpi_Config *spi_conf_0 = XSpi_LookupConfig(XPAR_SPI_0_DEVICE_ID);
    XSpi_CfgInitialize(&spi_0, spi_conf_0, spi_conf_0->BaseAddress);
    XSpi_SetOptions(&spi_0, XSP_MASTER_OPTION);
    XSpi_Start(&spi_0);
    XSpi_IntrGlobalDisable(&spi_0);
    XSpi_SetSlaveSelect(&spi_0, 0x01);

    XSpi_Config *spi_conf_1 = XSpi_LookupConfig(XPAR_SPI_1_DEVICE_ID);
    XSpi_CfgInitialize(&spi_1, spi_conf_1, spi_conf_1->BaseAddress);
    XSpi_SetOptions(&spi_1, XSP_MASTER_OPTION);
    XSpi_Start(&spi_1);
    XSpi_IntrGlobalDisable(&spi_1);
    XSpi_SetSlaveSelect(&spi_1, 0x01);
}

void spi_transfer(spi_port_t port, uint8_t *tx_data, uint8_t *rx_data, uint32_t len)
{
    XSpi *spi_port = spi_get_handle(port);

    if (spi_port == NULL)
    {
        return;
    }

    XSpi_Transfer(spi_port, tx_data, rx_data, len);
}

void spi_rx(spi_port_t port, uint8_t *data, uint32_t len)
{
    spi_transfer(port, data, data, len);
}

void spi_tx(spi_port_t port, uint8_t *data, uint32_t len)
{
    spi_transfer(port, data, NULL, len);
}

void spi_dsp_tx(uint8_t *data, uint32_t len)
{
    Xil_DCacheFlushRange((UINTPTR)data, len);

    int status = XST_FAILURE;

    status = XAxiDma_SimpleTransfer(&dma, (UINTPTR)data, len, XAXIDMA_DMA_TO_DEVICE);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiDma_SimpleTransfer TX fail = %d\n", status);
        return;
    }

    while (XAxiDma_Busy(&dma, XAXIDMA_DMA_TO_DEVICE))
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}