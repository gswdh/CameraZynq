#include "shutter_button.h"

#include <stdint.h>
#include <stdbool.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* System tools */
#include "log.h"
#include "cpubsub.h"
#include "messages.h"

/* Perphs */
#include "spi.h"
#include "gpio.h"

#define LOG_TAG "S_BUTTON"

static bool shutter_button_pressed = false;
static MSGButtonPress_t packet = {0};

static uint16_t shutter_button_value()
{
    uint8_t data[2] = {0};
    gpio_write(BADC_SPI_NCS, false);
    spi_0_rx(data, 2);
    gpio_write(BADC_SPI_NCS, true);
    return ((data[0] << 8) + data[1]) >> 2;
}

static void shutter_button_task(void)
{
    uint16_t value = shutter_button_value();
    if (value > 600)
    {
        if (!shutter_button_pressed)
        {
            /* Tell the system about this button press */
            packet.button = 6;
            packet.type = 1;
            cps_publish(&packet);
        }

        shutter_button_pressed = true;
    }

    else
    {
        shutter_button_pressed = false;
    }
}

void shutter_button_start()
{
    /* Init */
    packet.mid = MSGButtonPress_MID;

    // Maybe some calibration...

    // Start the task
    TimerHandle_t timer = xTimerCreate((const char *)"Shutter Button Timer",
                                       pdMS_TO_TICKS(10),
                                       pdTRUE,
                                       NULL,
                                       shutter_button_task);

    xTimerStart(timer, 0);
}