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

static const system_gui_screen_t base_screens[] = {SYS_GUI_HOME_SCR, SYS_GUI_POWER_INFO_SCR, SYS_GUI_MEMORY_INFO_SCR};
static uint32_t base_screen_cntr = 0;

static void actions_timer_cb(TimerHandle_t timer)
{
    tick = true;
}

static void actions_rotate_base_scr(const bool dir)
{
    if (dir == true)
    {
        base_screen_cntr += 1;

        if (base_screen_cntr == SYS_GUI_N_BASE_SCRS(base_screens))
        {
            base_screen_cntr = 0;
        }
    }

    else
    {
        if (base_screen_cntr == 0)
        {
            base_screen_cntr = (SYS_GUI_N_BASE_SCRS(base_screens) - 1);
        }

        else
        {
            base_screen_cntr -= 1;
        }
    }
}

static void actions_button_handler(uint32_t state, system_t *sys)
{
    switch (state)
    {
    // Adjust the ISO
    case ACT_BTN_SCR_ISO_SET:
        sys->gui.screen = SYS_GUI_ISO_SET_SCR;
        break;
    case ACT_BTN_SCR_ISO_RETURN:
        sys->gui.screen = SYS_GUI_HOME_SCR;
        break;
    case ACT_BTN_INC_ISO:
        if (sys->imaging.iso < 3200)
        {
            sys->imaging.iso *= 2;
        }
        else
        {
            sys->imaging.iso = 3200;
        }
        break;
    case ACT_BTN_DEC_ISO:
        if (sys->imaging.iso > 100)
        {
            sys->imaging.iso *= 0.5;
        }
        else
        {
            sys->imaging.iso = 100;
        }
        break;

    // Adjust the shutter speed
    case ACT_BTN_SCR_SHTR_SET:
        sys->gui.screen = SYS_GUI_SHTR_SET_SCR;
        break;
    case ACT_BTN_SCR_SHTR_RETURN:
        sys->gui.screen = SYS_GUI_HOME_SCR;
        break;
    case ACT_BTN_INC_SHTR:

        if (sys->imaging.speed_us > 1000)
        {
            sys->imaging.speed_us *= 0.5;
        }
        else
        {
            sys->imaging.speed_us = 1000;
        }
        break;
    case ACT_BTN_DEC_SHTR:
        if (sys->imaging.speed_us < 1e6)
        {
            sys->imaging.speed_us *= 2;
        }
        else
        {
            sys->imaging.speed_us = 1e6;
        }
        break;

    // Screen movement
    case ACT_BTN_SCR_BASE_INC:
        actions_rotate_base_scr(true);
        sys->gui.screen = base_screens[base_screen_cntr];
        break;

    case ACT_BTN_SCR_BASE_DEC:
        actions_rotate_base_scr(false);
        sys->gui.screen = base_screens[base_screen_cntr];
        break;

    case ACT_BTN_TAKE_IMG:
        sys->imaging.take_image = true;
        break;

    // Default action (nothing to do for invalid actions)
    default:
        break;
    }
}

void actions_main(void *params)
{
    pipe_t pipe = {0};
    uint8_t *buffer = NULL;

    system_t *sys = (system_t *)params;
    if (sys == NULL)
    {
        log_error(LOG_TAG, "sys == NULL.\n");
        run = false;
    }

    pipe_set_length(&pipe, SYS_ACTION_PIPE_LEN);
    cps_subscribe(MSGButtonPress_MID, MSGButtonPress_LEN, &pipe);
    cps_subscribe(MSGSystemStats_MID, MSGSystemStats_LEN, &pipe);
    cps_subscribe(MSGBatteryStats_MID, MSGBatteryStats_LEN, &pipe);
    cps_subscribe(MSGChargingStats_MID, MSGChargingStats_LEN, &pipe);
    cps_subscribe(MSGUSBPDStats_MID, MSGUSBPDStats_LEN, &pipe);

    /* Assign some space for the display buffer */
    buffer = (uint8_t *)malloc((size_t)pipe_item_size(&pipe));
    if (buffer == NULL)
    {
        log_error(LOG_TAG, "malloc failed.\n");

        // Do not continue
        run = false;
    }

    // Default screen
    sys->gui.screen = SYS_GUI_HOME_SCR;

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

            // Flag on whether to update the UI
            bool update = false;

            // Check for messages
            while (cps_receive(&pipe, (void *)buffer, PIPE_WAIT_POLL) == CPS_OK)
            {
                topic_t mid = cps_get_mid((void *)buffer);

                switch (mid)
                {
                case MSGButtonPress_MID:
                    actions_button_handler((uint32_t)((MSGButtonPress_t *)buffer)->button_state, sys);
                    update = true;
                    break;
                case MSGSystemStats_MID:
                    sys->power.pmc = *((MSGSystemStats_t *)buffer);
                    update = true;
                    break;
                case MSGBatteryStats_MID:
                    sys->power.battery = *((MSGBatteryStats_t *)buffer);
                    update = true;
                    break;
                case MSGChargingStats_MID:
                    sys->power.charging = *((MSGChargingStats_t *)buffer);
                    update = true;
                    break;
                case MSGUSBPDStats_MID:
                    sys->power.usbpd = *((MSGUSBPDStats_t *)buffer);
                    update = true;
                    break;
                default:
                    log_warn(LOG_TAG, "Unhandled MID 0x%04X\n", mid);
                    break;
                }
            }

            if (update == true)
            {
                gui_refresh(sys);
            }
        }
    }

    // Should never reach here if all is okay
    vTaskDelete(NULL);
}