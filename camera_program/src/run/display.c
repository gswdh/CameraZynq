#include "display.h"

#include <stdint.h>
#include <stdbool.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "log.h"

#include "spi.h"
#include "gpio.h"

#include "ssd1309z.h"

#define LOG_TAG "DISP"

void ssd_spi_write(uint8_t *data, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        spi_1_tx(data + i, 1);
    }
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

volatile bool disp_update = false;

static uint8_t display_data[SSD_DISP_BUFFER_LEN] = {100};

static void display_task(void *params)
{
    (void *)params;

    while (true)
    {
        if (disp_update)
        {
            disp_update = false;

            log_info(LOG_TAG, "Updating display\n");

            ssd_update_display(display_data);

            ssd_delay_ms(100);
        }
    }

    vTaskDelete(NULL);
}

void display_start()
{
    /* Init the display HW */
    ssd_init();

    memset(display_data, 0, SSD_DISP_BUFFER_LEN);

    /* Update the display once, to blank */
    disp_update = true;

    /* Start the task */
    xTaskCreate(display_task, "Display Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}