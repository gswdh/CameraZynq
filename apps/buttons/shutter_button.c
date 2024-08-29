#include "buttons.h"

#include "gpio.h"
#include "spi.h"
#include "log.h"

static void badc_spi_read(uint8_t *data, uint32_t len)
{
    gpio_write(BADC_SPI_NCS, false);
    spi_rx(SPI_PORT_0, data, len);
    gpio_write(BADC_SPI_NCS, true);
}

shutter_button_state_t shutter_button()
{
    uint8_t data[2] = {0};
    badc_spi_read(data, 2);
    uint16_t value = ((data[0] << 8) + data[1]) >> 2;
    return value > SHUTTER_BTN_THRSH ? FULL : RELEASED;
}