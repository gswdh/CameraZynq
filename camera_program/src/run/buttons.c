#include "buttons.h"

#include <stdint.h>
#include <stdbool.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "xil_printf.h"

#include "gpio.h"

const gpio_pin_t buttons_to_check[] = {
    BTN_BTMLEFT,
    BTN_BTMRIGHT,
    BTN_THUMB,
    BTN_TOPLEFT,
    BTN_TOPRIGHT};

bool button_states[N_BUTTONS] = {0};

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
            xil_printf("Button %u %s edge\r\n", i, button_state ? "rising" : "falling");

            // Update the states
            button_states[i] = button_state;
        }
    }
}

void buttons_start()
{
    // Start the task
    TimerHandle_t timer = xTimerCreate((const char *)"Buttons Timer",
                                       pdMS_TO_TICKS(100),
                                       pdTRUE,
                                       NULL,
                                       buttons_tasks);

    xTimerStart(timer, 0);
}
