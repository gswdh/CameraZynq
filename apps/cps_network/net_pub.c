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

static bool tick = false;

static void net_pub_timer_cb(TimerHandle_t xTimer)
{
    tick = true;
}

static void net_pub_init_rx(void)
{
    buffer_ptr = 0;
    memset(buffer, 0, NET_PUB_BUFF_LEN);
    // uart_receive(NET_PUB_UART, &buffer[buffer_ptr], NET_PUB_BUFF_LEN);
}

static uint32_t net_pub_has_terminator(void)
{
    for (uint32_t i = 0; i < NET_PUB_BUFF_LEN; i++)
    {
        if (buffer[i] == 0xFF)
        {
            return i;
        }
    }

    return 0;
}

typedef enum
{
    NET_PUB_START_STATE = 0,
    NET_PUB_PAYLOAD_STATE,
    NET_PUB_END_STATE,

} net_pub_rx_state_t;

void net_pub_task(void *params)
{
    net_pub_init_rx();

    // Start the timer
    TimerHandle_t net_pub_timer = xTimerCreate("Net Pub Timer", pdMS_TO_TICKS(NET_PUB_TICK_PERIOD_MS), true, NULL, &net_pub_timer_cb);
    xTimerStart(net_pub_timer, 0);

    uint8_t state = NET_PUB_START_STATE;

    while (true)
    {
        // Wait for the tick to set the tick flag
        if (tick == true)
        {
            // Reset for next time
            tick = false;

            uint8_t c = 0;

            while (uart_receive(NET_PUB_UART, &c, NET_PUB_BUFF_LEN) == 1)
            {
                switch (state)
                {
                case NET_PUB_START_STATE:
                    if (c == '[')
                    {
                        net_pub_init_rx();
                        state = NET_PUB_PAYLOAD_STATE;
                    }
                    break;
                case NET_PUB_PAYLOAD_STATE:
                    if (c == ']')
                    {
                        state = NET_PUB_END_STATE;
                    }
                    else
                    {
                        // Build up the buffer
                        buffer[buffer_ptr++] = c;

                        // Reset to prevent buffer overflow
                        if (buffer_ptr == NET_PUB_BUFF_LEN)
                        {
                            state = NET_PUB_START_STATE;
                        }
                    }
                    break;
                case NET_PUB_END_STATE:
                    // Found a new line, give it to the network
                    cps_network_recieve((char *)buffer, buffer_ptr - 1);

                    // Reset the state machine
                    state = NET_PUB_START_STATE;
                    break;
                default:
                    // Reset the state machine
                    state = NET_PUB_START_STATE;
                    break;
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(NULL);
}
