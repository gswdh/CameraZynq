#include "system.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "log.h"

/* Program tasks */
#include "system.h"
#include "heartbeat.h"
#include "buttons.h"
#include "display.h"
#include "sensor.h"
#include "gui.h"
#include "pmc_router.h"

#include "cpubsub.h"
#include "messages.h"

#include "dmgui.h"

#define LOG_TAG "SYSTEM"

static system_state_t system_state = {0};

/* Make a new pipe */
static pipe_t pipe = {0};
static uint8_t data[1024] = {0};

/* Message variables for long term use */
static MSGSensorSettings_t sensor_settings = {0};

static void system_action(uint32_t action)
{
    switch (action)
    {
    case GUI_ACT_INC_ISO:
        system_state.sensor_config.sensor_iso *= 2;
        break;

    case GUI_ACT_DEC_ISO:
        system_state.sensor_config.sensor_iso *= 0.5;
        break;

    case GUI_ACT_INC_SHUTTER:
        system_state.sensor_config.sensor_shutter_s *= 2;
        break;

    case GUI_ACT_DEC_SHUTTER:
        system_state.sensor_config.sensor_shutter_s *= 0.5;
        break;

    default:
        break;
    }
}

static void system_task()
{
    uint8_t data[1024] = {0};

    while (true)
    {
        /* Wait for some data to arrive */
        cps_receive(&pipe, data, PIPE_WAIT_BLOCK);

        topic_t mid = cps_get_mid(data);

        if (mid == MSGGUIActions_MID)
        {
            MSGGUIActions_t *packet = (MSGGUIActions_t *)data;

            /* Handle the action */
            system_action(packet->action);
        }

        if (mid == MSGTick_MID)
        {
            /* Let everyone know about the new value sensor values */
            sensor_settings.sensitivity_iso = system_state.sensor_config.sensor_iso;
            sensor_settings.shutter_speed = system_state.sensor_config.sensor_shutter_s;
            cps_publish(&sensor_settings);
        }
    }

    /* Should never reach */
    vTaskDelete(NULL);
}

void system_start()
{
    /* Start program tasks */
    heartbeat_start();
    buttons_start();
    display_start();
    sensor_start();
    gui_start();
    pmc_comms_start();

    /* Load the defaults */
    system_state.sensor_config.sensor_iso = SYS_ISO_DEFAULT;
    system_state.sensor_config.sensor_shutter_s = SYS_SHUTTER_DEFAULT;

    /* Subscribe to the relvant message MIDs */
    cps_subscribe(MSGTick_MID, MSGTick_LEN, &pipe);
    cps_subscribe(MSGGUIActions_MID, MSGGUIActions_LEN, &pipe);
    sensor_settings.mid = MSGSensorSettings_MID;

    /* Start the system task */
    xTaskCreate(system_task, "System Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}