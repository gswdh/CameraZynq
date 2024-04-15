#pragma once

#include <stdint.h>
#include <stdbool.h>

void gmax_power_on();
void gmax_power_off();

void gmax_spi_write(uint8_t reg, uint8_t *data, uint32_t len);
void gmax_spi_read(uint8_t reg, uint8_t *data, uint32_t len);

void gmax_init();