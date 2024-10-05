#include "debugging.h"

#include "apps_config.h"

#include "system.h"
#include "gpio.h"
#include "log.h"

#include "cpubsub.h"
#include "messages.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include <stdlib.h>

#define LOG_TAG "DBG"

#ifdef DEBUG
const topic_t dbg_subs[] = {MSGButtonPress_MID, MSGPowerButton_MID};

static uint8_t *buffer = NULL;
static pipe_t pipe = {0};

static bool run = false;

static void dbg_tick(TimerHandle_t timer)
{
    run = true;
}
#endif

void dbg_start(void *params)
{
#ifdef DEBUG
    pipe_set_length(&pipe, DBG_PIPE_LEN);
    for (uint32_t i = 0; i < (sizeof(dbg_subs) / sizeof(dbg_subs[0])); i++)
    {
        cps_subscribe(dbg_subs[i], messages_msg_len(dbg_subs[i]), &pipe);
    }

    buffer = (uint8_t *)malloc(pipe_item_size(&pipe));

    if (buffer == NULL)
    {
        log_error(LOG_TAG, "Was unable to malloc for cps.\n");
    }

    else
    {
        TimerHandle_t dbg_timer = xTimerCreate("Debugging Tick", pdMS_TO_TICKS(DBG_TICK_PERIOD_MS), true, NULL, dbg_tick);
        xTimerStart(dbg_timer, 0);
    }

    while (true)
    {
        if (run == true)
        {
            run = false;

            // If there are no messages, finish up
            while (cps_receive(&pipe, (void *)buffer, PIPE_WAIT_POLL) == CPS_OK)
            {
                topic_t mid = cps_get_mid((void *)buffer);

                switch (mid)
                {
                case MSGButtonPress_MID:
                    log_info(LOG_TAG, "BTN event %08X\n", ((MSGButtonPress_t *)buffer)->button_state);
                    break;
                // case MSGSensorSettings_MID:
                // 	log_info(LOG_TAG, "\n");
                // 	break;
                // case MSGGUIActions_MID:
                // 	log_info(LOG_TAG, "\n");
                // 	break;
                // case MSGTick_MID:
                // 	log_info(LOG_TAG, "\n");
                // 	break;
                case MSGBatteryStats_MID:
                    log_info(LOG_TAG, "BMS %2.3fV %2.3fA SoC=%u%% cap=%2.3fAh STATUS=0x%04X FAULTS=0x%04X\n",
                             ((MSGBatteryStats_t *)buffer)->voltage,
                             ((MSGBatteryStats_t *)buffer)->current,
                             (uint32_t)((MSGBatteryStats_t *)buffer)->soc,
                             ((MSGBatteryStats_t *)buffer)->capacity,
                             ((MSGBatteryStats_t *)buffer)->status,
                             ((MSGBatteryStats_t *)buffer)->faults);
                    break;
                case MSGChargingStats_MID:
                    log_info(LOG_TAG, "CHRGR %2.3fVin %2.3fAin %2.3fVout %2.3fAout %2.3fC Charging = %5s\n",
                             ((MSGChargingStats_t *)buffer)->input_voltage,
                             ((MSGChargingStats_t *)buffer)->input_current,
                             ((MSGChargingStats_t *)buffer)->output_voltage,
                             ((MSGChargingStats_t *)buffer)->output_current,
                             ((MSGChargingStats_t *)buffer)->chrgr_temp,
                             (((MSGChargingStats_t *)buffer)->charging == 0) ? "false" : "true ");
                    break;
                case MSGSystemStats_MID:
                    log_info(LOG_TAG, "SYS %2.3fV %2.3fA %2.3fW %2.3fC\n",
                             ((MSGSystemStats_t *)buffer)->bus_voltage,
                             ((MSGSystemStats_t *)buffer)->bus_current,
                             ((MSGSystemStats_t *)buffer)->bus_power,
                             ((MSGSystemStats_t *)buffer)->pmc_temp);
                    break;
                case MSGUSBPDStats_MID:
                    log_info(LOG_TAG, "USBPD %2.3fV %2.3fA Attached = %5s\n",
                             ((MSGUSBPDStats_t *)buffer)->bus_voltage,
                             ((MSGUSBPDStats_t *)buffer)->bus_current,
                             (((MSGUSBPDStats_t *)buffer)->attached == 0) ? "false" : "true ");
                    break;
                default:
                    log_warn(LOG_TAG, "MID %04X not supported in the debugging.\n", mid);
                    break;
                }
            }
        }
    }

#endif
    vTaskDelete(NULL);
}
