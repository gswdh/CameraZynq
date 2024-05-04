#pragma once

#include <stdint.h>

void i2c_init();
void i2c_write_memory8(uint8_t device, uint8_t addr, uint8_t *data, uint32_t len);
void i2c_write_memory16(uint8_t device, uint16_t addr, uint8_t *data, uint32_t len);
void i2c_read_memory8(uint8_t device, uint8_t addr, uint8_t *data, uint32_t len);
void i2c_read_memory16(uint8_t device, uint16_t addr, uint8_t *data, uint32_t len);