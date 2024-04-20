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

void sensor_task()
{
    vTaskDelete(NULL);
}

void sensor_start()
{
    /* Turn on and init the sensor */
    gmax_init();

    /*  */

    xTaskCreate(sensor_task, "Sensor Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}