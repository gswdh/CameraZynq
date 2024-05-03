#include "sensor.h"

/* Standard libs */
#include <stdint.h>
#include <stdbool.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Libs */
#include "log.h"
#include "cpubsub.h"
#include "messages.h"
#include "gmax0505.h"

/* Perphs */
#include "gpio.h"

#define LOG_TAG "SENSOR"

void sensor_task()
{
    while (1)
    {
        if (gpio_read(SEN_TDIG0))
        {
            log_info(LOG_TAG, "TDIG0 set\n");
        }

        if (gpio_read(SEN_TDIG1))
        {
            log_info(LOG_TAG, "TDIG1 set\n");
        }

        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void sensor_start()
{
    /* Turn on and init the sensor */
    gmax_init();

    /*  */

    xTaskCreate(sensor_task, "Sensor Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}