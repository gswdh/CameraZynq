#include "system.h"

#include "apps_config.h"

#include "pipe.h"
#include "cpubsub.h"
#include "messages.h"
#include "log.h"
#include "gui.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include <string.h>
#include <stdlib.h>

#define LOG_TAG "ACT"

static bool tick = false;
static bool run = true;

static system_t *sys = NULL;
static pipe_t pipe = {0};
static uint8_t *buffer = NULL;

static void actions_timer_cb(TimerHandle_t timer)
{
    tick = true;
}

void actions_main(void *params)
{
    sys = (system_t *)params;
    if (sys == NULL)
    {
        log_error(LOG_TAG, "sys == NULL.\n");
        run = false;
    }

    pipe_set_length(&pipe, SYS_ACTION_PIPE_LEN);
    cps_subscribe(MSGButtonPress_MID, MSGButtonPress_LEN, &pipe);

    /* Assign some space for the display buffer */
    buffer = (uint8_t *)malloc((size_t)pipe_item_size(&pipe));
    if (buffer == NULL)
    {
        log_error(LOG_TAG, "malloc failed.\n");

        // Do not continue
        run = false;
    }

    vTaskDelay(pdMS_TO_TICKS(1000));

    gui_welcome_screen();

    vTaskDelay(pdMS_TO_TICKS(500));

    // Draw the first home screem
    gui_home_screen(sys->imaging.iso, sys->imaging.speed_us, 10);

    TimerHandle_t timer = xTimerCreate("Actions Tick", pdMS_TO_TICKS(SYS_TICK_ACTION_PERIOD_MS), true, NULL, actions_timer_cb);
    xTimerStart(timer, 0);

    // Go forever
    while (run == true)
    {
        // Wait for the tick to arrive
        if (tick == true)
        {
            // Reset the flag
            tick = false;

            // Check for messages
            while (cps_receive(&pipe, (void *)buffer, PIPE_WAIT_POLL) == CPS_OK)
            {
                topic_t mid = cps_get_mid((void *)buffer);

                switch (mid)
                {
                case MSGButtonPress_MID:
                    break;
                default:
                    log_warn(LOG_TAG, "Unhandled MID 0x%04X\n", mid);
                    break;
                }
            }
        }
    }

    // Should never reach here if all is okay
    vTaskDelete(NULL);
}