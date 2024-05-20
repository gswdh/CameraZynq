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

#include "cpubsub.h"
#include "messages.h"

#include "dmgui.h"

#define LOG_TAG "SYSTEM"

const float sensor_valid_isos[] = {100, 200, 400, 800, 1600};
const float sensor_valid_shutters[] = {1, 0.5, 0.25, 0.1, 0.05, 0.025};
static uint8_t sensor_iso_ptr = 0;
static uint8_t sensor_shutter_ptr = 0;

static system_state_t system_state = {0};

/* Make a new pipe */
static pipe_t pipe = {0};
static uint8_t data[1024] = {0};

static void system_gui_action(uint32_t action)
{
    switch (action)
    {
    case GUI_ACT_INC_ISO:
        if (sensor_iso_ptr < 4)
        {
            sensor_iso_ptr++;
        }
        break;

    case GUI_ACT_DEC_ISO:
        if (sensor_iso_ptr > 0)
        {
            sensor_iso_ptr--;
        }
        break;

    case GUI_ACT_INC_SHUTTER:
        if (sensor_shutter_ptr < 4)
        {
            sensor_shutter_ptr++;
        }
        break;

    case GUI_ACT_DEC_SHUTTER:
        if (sensor_shutter_ptr > 0)
        {
            sensor_shutter_ptr--;
        }
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

            /* Handle the GUI action */
            system_gui_action(packet->action);

            /* Let everyone know about the new value sensor values */
            MSGSensorSettings_t sensor_settings = {0};
            sensor_settings.mid = MSGSensorSettings_MID;
            sensor_settings.sensitivity_iso = sensor_valid_isos[sensor_iso_ptr];
            sensor_settings.shutter_speed = sensor_valid_shutters[sensor_shutter_ptr];
            cps_publish(&sensor_settings);

            log_info(LOG_TAG, "system_task sensitivity_iso = %f, shutter_speed = %f\n",
                     sensor_settings.sensitivity_iso, sensor_settings.shutter_speed);
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

    // /* Subscribe to the relvant message MIDs */
    cps_subscribe(MSGGUIActions_MID, MSGGUIActions_LEN, &pipe);

    /* Start the system task */
    xTaskCreate(system_task, "System Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}