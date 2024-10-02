#include "display.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "spi.h"
#include "gpio.h"

#include "ssd1309z.h"

void ssd_spi_write(uint8_t *data, uint32_t len)
{
    spi_dsp_tx(data, len);
}

void ssd_set_dc(bool en)
{
    gpio_write(DSP_D_NC, en);
}

void ssd_set_cs(bool en)
{
    gpio_write(DSP_SPI_NCS, en);
}

void ssd_set_rst(bool en)
{
    gpio_write(DSP_NRESET, en);
}

void ssd_pwr_cont(bool en)
{
    gpio_write(PWR_VDISP_EN, en);
}

void ssd_delay_ms(uint32_t time_ms)
{
    vTaskDelay(pdMS_TO_TICKS(time_ms));
}