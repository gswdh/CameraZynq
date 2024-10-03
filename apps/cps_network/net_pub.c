#include "net_pub.h"

#include "cpubsub_network.h"

#include "log.h"
#include "uart.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

// Standard headers
#include <stdbool.h>
#include <string.h>

#define LOG_TAG "NET_PUB"

static uint8_t buffer[NET_PUB_BUFF_LEN] = {0};
static uint32_t buffer_ptr = 0;

static bool run = false;

static void net_pub_timer_cb(TimerHandle_t xTimer)
{
    run = true;
}

static void net_pub_init_rx(void)
{
    buffer_ptr = 0;
    memset(buffer, 0, NET_PUB_BUFF_LEN);
}

void net_pub_task(void *params)
{
    net_pub_init_rx();

    // Start the timer
    TimerHandle_t net_pub_timer = xTimerCreate("Net Pub Timer", pdMS_TO_TICKS(NET_PUB_TICK_PERIOD_MS), true, NULL, &net_pub_timer_cb);
    xTimerStart(net_pub_timer, 0);

    while (true)
    {
        // Wait for the tick to set the run flag
        if (run == true)
        {
            // Reset for next time
            run = false;

            // Get some data
            buffer_ptr += uart_receive(NET_PUB_UART, (buffer + buffer_ptr), 100);

            // log_info(LOG_TAG, "buffer_ptr = %u\n", buffer_ptr);

            // Look for a newline in the buffer
            char *needle = strstr((char *)buffer, "\n");
            if (needle != NULL)
            {
                uint32_t len = (uint32_t)needle - (uint32_t)buffer;

                log_info(LOG_TAG, "message with length = %u\n", len);

                // Found a new line, give it to the network
                cps_network_recieve((char *)buffer, len);

                // Start a new RX
                net_pub_init_rx();
            }

            // Make sure the buffer pointer is safe
            if (buffer_ptr >= (NET_PUB_BUFF_LEN - 1))
            {
                // Start a new RX
                net_pub_init_rx();
            }
        }
    }

    vTaskDelete(NULL);
}
