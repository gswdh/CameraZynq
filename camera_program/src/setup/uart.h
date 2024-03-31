#pragma once

#include <stdint.h>

void uart_init();
void uart_tx(uint8_t *data, uint32_t len);
void uart_rx(uint8_t *data, uint32_t len);