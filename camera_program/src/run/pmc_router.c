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
static uint32_t data_ptr = 0;

static void pmc_comms_task()
{
    while (1)
    {
        uint8_t c = 0;
        uint32_t n_bytes = uart_rx(&c, 1);

        if (n_bytes)
        {
            if (c == 0)
            {
                log_info(LOG_TAG, "Message RXd = %s\n", data);
                memset(data, 0, 1024);
                data_ptr = 0;
            }

            else
            {
                data[data_ptr++] = c;
            }
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