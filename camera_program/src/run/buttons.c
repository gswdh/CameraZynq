#include "buttons.h"

#include <stdint.h>
#include <stdbool.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "log.h"
#include "cpubsub.h"
#include "messages.h"

#include "gpio.h"

#define LOG_TAG "BUTTONS"

static const gpio_pin_t buttons_to_check[] = {
    BTN_BTMLEFT,
    BTN_BTMRIGHT,
    BTN_THUMB,
    BTN_TOPLEFT,
    BTN_TOPRIGHT};

static bool button_states[N_BUTTONS] = {0};

static MSGButtonPress_t packet = {0};

static void buttons_tasks()
{
    for (uint8_t i = 0; i < N_BUTTONS; i++)
    {
        // Read the button state
        bool button_state = gpio_read(buttons_to_check[i]);

        // If there's a difference
        if (button_state != button_states[i])
        {
            // Do something with this information
            log_info(LOG_TAG, "Button %u %s edge\n", i, button_state ? "rising" : "falling");

            /* Tell the system about this button press */
            packet.button = i;
            packet.type = button_state;
            cps_publish(&packet);

            // Update the states
            button_states[i] = button_state;
        }
    }
}

void buttons_start()
{
    /* Init */
    packet.mid = MSGButtonPress_MID;

    /* Timer... */
    TimerHandle_t timer = xTimerCreate((const char *)"Buttons Timer",
                                       pdMS_TO_TICKS(100),
                                       pdTRUE,
                                       NULL,
                                       buttons_tasks);

    xTimerStart(timer, 0);
}
