#include "pmc_router.h"

#include <stdint.h>
#include <stdbool.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "log.h"

#include "cpubsub.h"
#include "messages.h"

#include "uart.h"

#define LOG_TAG "PMC"

/* Make a new pipe */
static pipe_t pipe = {0};
static uint8_t data[1024] = {0};

static void pmc_comms_task()
{
    while (1)
    {
        uint32_t n_bytes = uart_rx(data, 1024);

        if (n_bytes)
        {
            memset(data, 0, 1024);
        }
    }

    vTaskDelete(NULL);
}

void pmc_comms_start()
{
    /* Subscribe to the relvant message MIDs */
    // cps_subscribe(MSGButtonPress_MID, MSGButtonPress_LEN, &pipe);

    /* Start the task */
    xTaskCreate(pmc_comms_task, "GUI Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}