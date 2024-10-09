#pragma once

#include <stdint.h>
#include <stdbool.h>

void i2c_init(const uint32_t clk_rate_hz);
bool i2c_write(const uint16_t slave_addr, const uint8_t *const data, const uint32_t len);
bool i2c_read(const uint16_t slave_addr, uint8_t *const data, const uint32_t len);
void i2c_write_reg(const uint16_t slave_addr, const uint8_t reg_addr, const uint8_t *const data, const uint32_t len);
void i2c_read_reg(const uint16_t slave_addr, const uint8_t reg_addr, uint8_t *const data, const uint32_t len);