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
    /* Turn on and init the sensor */
    gmax_init();

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    vTaskDelete(NULL);
}

void sensor_start()
{
    /*  */

    xTaskCreate(sensor_task, "Sensor Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}