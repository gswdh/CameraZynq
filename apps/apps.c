// Matching header
#include "apps.h"
#include "apps_config.h"

// App headers
#include "system.h"
#include "buttons.h"
#include "cpubsub_network.h"
#include "net_pub.h"
#include "display.h"
#include "debugging.h"
#include "log.h"

// Xilinx

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

// System headers
#include <stdint.h>

#define LOG_TAG "APPS"

typedef struct
{
    TaskFunction_t function;
    const char name[32];
    const uint32_t stack_size;
    uint32_t priority;
} app_config_t;

static const app_config_t app_configs[] = {
    {
        .function = &display_start,
        .name = "Display Writer",
        .stack_size = DSP_APP_STACK_SIZE_B,
        .priority = DSP_APP_PRIORITY,
    },
    {
        .function = &buttons_main,
        .name = "Buttons",
        .stack_size = BTN_APP_STACK_SIZE_B,
        .priority = BTN_APP_PRIORITY,
    },
    {
        .function = &net_pub_task,
        .name = "Network publisher from UART",
        .stack_size = NET_PUB_APP_STACK_SIZE_B,
        .priority = NET_PUB_APP_PRIORITY,
    },
    {
        .function = &system_main,
        .name = "System",
        .stack_size = SYS_APP_STACK_SIZE_B,
        .priority = SYS_APP_PRIORITY,
    },
    // {
    //     .function = &dbg_start,
    //     .name = "Debugging",
    //     .stack_size = DBG_APP_STACK_SIZE_B,
    //.priority = DBG_APP_PRIORITY,
    // },
    // {
    //     .function = &cps_network_task,
    //     .name = "CPS Network",
    //     .stack_size = 1024,
    //.priority = DBG_APP_PRIORITY,
    // },
};

void apps_launcher(void)
{
    for (uint32_t i = 0; i < (sizeof(app_configs) / sizeof(app_configs[0])); i++)
    {
        BaseType_t result = xTaskCreate(app_configs[i].function, app_configs[i].name, app_configs[i].stack_size, NULL, app_configs[i].priority, NULL);
        if (result == pdPASS)
        {
            log_info(LOG_TAG, "%s started.\n", app_configs[i].name);
        }

        else
        {
            log_error(LOG_TAG, "%s start failed with %d\n", app_configs[i].name, result);
        }
    }
}
