#pragma once

#include <stdbool.h>

typedef enum
{ /* Outputs */
  DSP_D_NC = 0,
  DSP_NRESET = 1,
  EVF_NRESET = 2,
  FPGA_LED_0 = 3,
  FPGA_LED_1 = 4,
  FPGA_LED_2 = 5,
  PSS_PMC_FLAG = 6,
  PWR_EVF_AVDD_EN = 7,
  PWR_EVF_AVEE_EN = 8,
  PWR_SEN_0V7_EN = 9,
  PWR_SEN_1V3_EN = 10,
  PWR_SEN_3V3A_EN = 11,
  PWR_SEN_3V6_EN = 12,
  PWR_SEN_4V1_EN = 13,
  PWR_SEN_N1V3A_EN = 14,
  PWR_VDISP_EN = 15,
  SEN_SYS_NRESET = 16,
  TMP_THERM = 17,
  DSP_SPI_NCS = 18,
  BADC_SPI_NCS = 19,
  SEN_SPI_NCS = 20,
  SEN_SPI_CLK = 21,
  SEN_SPI_MOSI = 22,

  /* Inputs */
  BTN_BTMLEFT = 32,
  BTN_BTMRIGHT = 33,
  BTN_THUMB = 34,
  BTN_TOPLEFT = 35,
  BTN_TOPRIGHT = 36,
  PMC_PSS_FLAG = 37,
  TMP_ALERT = 38,
  SEN_SPI_MISO = 39
} gpio_pin_t;

void gpio_init();
void gpio_write(gpio_pin_t pin, bool level);
bool gpio_read(gpio_pin_t pin);
void gpio_set(gpio_pin_t pin);
void gpio_reset(gpio_pin_t pin);
void gpio_toggle(gpio_pin_t pin);