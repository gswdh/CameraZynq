#include "shutter_button.h"

#include <stdint.h>
#include <stdbool.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "log.h"

#include "spi.h"

#define LOG_TAG "S_BUTTON"

bool shutter_button_pressed = false;

static uint16_t shutter_button_value()
{
    uint8_t data[2] = {0};
    spi_0_rx(data, 2);
    return ((data[0] << 8) + data[1]) >> 2;
}

static void shutter_button_task(void)
{
    uint16_t value = shutter_button_value();
    if (value > 600)
    {
        if (!shutter_button_pressed)
        {
            log_info(LOG_TAG, "Shutter Button Pressed!\n");
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
    // Maybe some calibration...

    // Start the task
    TimerHandle_t timer = xTimerCreate((const char *)"Shutter Button Timer",
                                       pdMS_TO_TICKS(10),
                                       pdTRUE,
                                       NULL,
                                       shutter_button_task);

    xTimerStart(timer, 0);
}