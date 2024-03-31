#pragma once

#include <stdbool.h>

typedef enum {  FPGA_LED_0 = 0x00000001, 
                FPGA_LED_1 = 0x00000002, 
                FPGA_LED_2 = 0x00000004
} gpio_pin_t;

void gpio_init();
void gpio_write(gpio_pin_t pin, bool level);
bool gpio_read(gpio_pin_t pin);
void gpio_set(gpio_pin_t pin);
void gpio_reset(gpio_pin_t pin);
void gpio_toggle(gpio_pin_t pin);