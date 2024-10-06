#include "gmax0505.h"

#include "gpio.h"

#include "FreeRTOS.h"
#include "task.h"

#include "xil_printf.h"

#include <assert.h>

void gmax_delay(const uint32_t time_ms)
{
    vTaskDelay(pdMS_TO_TICKS(time_ms));
}

bool gmax_pin_read(const gmax_pin_t pin)
{
    switch (pin)
    {
    case SPI_MISO:
        return gpio_read(SEN_SPI_MISO);
        break;
    case SYNC_STATUS:
        assert(false && "SYNC_STATUS not implemented.");
        break;
    case FRAME_RDY:
        assert(false && "FRAME_RDY not implemented.");
        break;
    case FRAME_PROG:
        assert(false && "FRAME_PROG not implemented.");
        break;
    default:
        return 0;
        break;
    }

    return 0;
}

void gmax_pin_write(const gmax_pin_t pin, const bool value)
{
    switch (pin)
    {
    case PWR_0V7_EN:
        gpio_write(PWR_SEN_0V7_EN, value);
        break;
    case PWR_1V3_EN:
        gpio_write(PWR_SEN_1V3_EN, value);
        break;
    case PWR_3V3A_EN:
        gpio_write(PWR_SEN_3V3A_EN, value);
        break;
    case PWR_3V6_EN:
        gpio_write(PWR_SEN_3V6_EN, value);
        break;
    case PWR_4V1_EN:
        gpio_write(PWR_SEN_4V1_EN, value);
        break;
    case PWR_N1V3A_EN:
        gpio_write(PWR_SEN_N1V3A_EN, value);
        break;
    case SPI_NCS:
        gpio_write(SEN_SPI_NCS, value);
        break;
    case SPI_CLK:
        gpio_write(SEN_SPI_CLK, value);
        break;
    case SPI_MOSI:
        gpio_write(SEN_SPI_MOSI, value);
        break;
    case SYNC_EN:
        assert(false && "SYNC_EN not implemented.");
        break;
    case FRAME_REQ:
        assert(false && "FRAME_REQ not implemented.");
        break;
    case SEN_NRESET:
        gpio_write(SEN_NRESET, value);
        break;
    default:
        break;
    }
}

void gmax_sync_word_write(const uint16_t sync_word)
{
    assert(false && "gmax_sync_word_write weakly def function not implemented.");
}