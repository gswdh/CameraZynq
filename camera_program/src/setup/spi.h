#pragma once

#include <stdint.h>

void spi_init();
void spi_0_transfer(uint8_t *tx_data, uint8_t *rx_data, uint32_t len);
void spi_0_rx(uint8_t *data, uint32_t len);
void spi_0_tx(uint8_t *data, uint32_t len);
void spi_1_transfer(uint8_t *tx_data, uint8_t *rx_data, uint32_t len);
void spi_1_rx(uint8_t *data, uint32_t len);
void spi_1_tx(uint8_t *data, uint32_t len);