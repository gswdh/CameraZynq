#include "spi.h"

#include "xparameters.h"
#include "xspi.h"

#include "xil_printf.h"

static XSpi spi_0 = {0};
static XSpi spi_1 = {0};

void spi_init()
{
    XSpi_Config *spi_conf = XSpi_LookupConfig(XPAR_XSPI_0_BASEADDR);
    XSpi_CfgInitialize(&spi_0, spi_conf, spi_conf->BaseAddress);
    XSpi_SetOptions(&spi_0, XSP_MASTER_OPTION);
    XSpi_Start(&spi_0);
    XSpi_IntrGlobalDisable(&spi_0);
    XSpi_SetSlaveSelect(&spi_0, 0x01);
}

void spi_0_transfer(uint8_t *tx_data, uint8_t *rx_data, uint32_t len)
{
    XSpi_Transfer(&spi_0, tx_data, rx_data, len);
}

void spi_0_rx(uint8_t *data, uint32_t len)
{
    spi_0_transfer(data, data, len);
}

void spi_0_tx(uint8_t *data, uint32_t len)
{
    spi_0_transfer(data, NULL, len);
}
