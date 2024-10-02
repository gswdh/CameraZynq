#pragma once

#include <stdint.h>

typedef enum
{
    SPI_PORT_0 = 0,
    SPI_PORT_1,
} spi_port_t;

void spi_init();
void spi_transfer(spi_port_t port, uint8_t *tx_data, uint8_t *rx_data, uint32_t len);
void spi_rx(spi_port_t port, uint8_t *data, uint32_t len);
void spi_tx(spi_port_t port, uint8_t *data, uint32_t len);
void spi_dsp_tx(uint8_t *data, uint32_t len);