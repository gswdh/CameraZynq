// Matching header
#include "apps.h"

#include "log.h"

// App headers
#include "system.h"
#include "buttons.h"
#include "cpubsub_network.h"
#include "net_pub.h"
#include "display.h"
#include "debugging.h"

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
} app_config_t;

static const app_config_t app_configs[] = {
    {
        .function = &system_main,
        .name = "System",
        .stack_size = 128,
    },
    {
        .function = &buttons_main,
        .name = "Buttons",
        .stack_size = 128,
    },
    {
        .function = &net_pub_task,
        .name = "Network publisher from UART",
        .stack_size = 4096,
    },
    {
        .function = &display_start,
        .name = "Display Writer",
        .stack_size = 4096,
    },
    {
        .function = &dbg_start,
        .name = "Debugging",
        .stack_size = 512,
    },
    {
        .function = &cps_network_task,
        .name = "CPS Network",
        .stack_size = 1024,
    },
};

void apps_launcher(void)
{
    for (uint32_t i = 0; i < (sizeof(app_configs) / sizeof(app_configs[0])); i++)
    {
        BaseType_t result = xTaskCreate(app_configs[i].function, app_configs[i].name, app_configs[i].stack_size, NULL, SYS_APP_PRIORITY, NULL);
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
