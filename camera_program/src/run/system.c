#include "system.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "log.h"
#include "cpubsub.h"
#include "messages.h"

#include "gmax0505.h"

#define LOG_TAG "SYSTEM"

/* Make a new pipe */
static pipe_t pipe = {0};

static void system_task()
{
    uint8_t data[1024] = {0};

    while (true)
    {
        /* Wait for some data to arrive */
        cps_receive(&pipe, data, PIPE_WAIT_BLOCK);

        topic_t mid = cps_get_mid(data);

        if (mid == MSGButtonPress_MID)
        {
            MSGButtonPress_t *packet = (MSGButtonPress_t *)data;

            log_info(LOG_TAG, "Message with id = 0x%X rxd at %u.\n", packet->mid, xTaskGetTickCount());
            log_info(LOG_TAG, "button = %u, type = %u\n", packet->button, packet->type);

            volatile uint8_t data[256] = {0};
            gmax_spi_read(0x00, data, 256);

            for (uint32_t i = 0; i < 256; i++)
            {
                log_info(LOG_TAG, "%u,%u\n", i, data[i]);
            }
        }
    }

    /* Should never reach */
    vTaskDelete(NULL);
}

void system_start()
{
    cps_subscribe(MSGButtonPress_MID, MSGButtonPress_LEN, &pipe);

    xTaskCreate(system_task, "System Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}