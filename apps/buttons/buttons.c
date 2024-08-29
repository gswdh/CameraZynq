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
    BTN_TOPRIGHT,
};

static button_state_t button_state[LEN_BTNS(buttons_to_check)] = {0};
static shutter_button_state_t shutter_button_state = RELEASED;

static MSGButtonPress_t packet = {0};

static button_state_t button_get_state(gpio_pin_t button)
{
    bool pin_value = gpio_read(button);

    switch (button)
    {
    case BTN_BTMLEFT:
        return pin_value ? BTN_STATE_LO : BTN_STATE_HI;
        break;

    case BTN_BTMRIGHT:
        return pin_value ? BTN_STATE_LO : BTN_STATE_HI;
        break;

    case BTN_THUMB:
        return pin_value ? BTN_STATE_HI : BTN_STATE_LO;
        break;

    case BTN_TOPLEFT:
        return pin_value ? BTN_STATE_LO : BTN_STATE_HI;
        break;

    case BTN_TOPRIGHT:
        return pin_value ? BTN_STATE_LO : BTN_STATE_HI;
        break;
    }

    return BTN_STATE_LO;
}

static uint32_t button_state_packer(button_state_t *states, uint8_t len)
{
    uint32_t state = 0;

    for (uint8_t i = 0; i < len; i++)
    {
        state |= (((uint32_t)states[i]) & 0x3) << (i * 2);
    }

    return state;
}

static void button_state_resolver()
{
    /* Check the regular push buttons */
    for (uint8_t i = 0; i < LEN_BTNS(buttons_to_check); i++)
    {
        // Read the button state
        button_state_t state = button_get_state(buttons_to_check[i]);

        // If there's a difference
        if (state != button_state[i])
        {
            // Resolve the edges. If the previous state was an edge, the state will automatically set to a level
            switch (button_state[i])
            {
            case BTN_STATE_HI:
                state = (state == BTN_STATE_LO) ? BTN_STATE_FALLING : state;
                break;

            case BTN_STATE_LO:
                state = (state == BTN_STATE_HI) ? BTN_STATE_RISING : state;
                break;
            }

            // Update the states
            button_state[i] = state;

            // Do something with this information
            // log_info(LOG_TAG, "Button %u %s edge\n", i, state ? "rising" : "falling");

            /* Tell the system about this button press */
            packet.button_state = button_state_packer(button_state, LEN_BTNS(buttons_to_check));
            cps_publish(&packet, MSGButtonPress_MID);
        }
    }

    // /* Check the shutter button */
    // shutter_button_state_t button_state = shutter_button();
    // if (button_state != shutter_button_state)
    // {
    //     /* Update the state */
    //     shutter_button_state = button_state;

    //     /* Tell the system about this button press */
    //     packet.button = BTN_SHTR;
    //     packet.edge = shutter_button_state;
    //     cps_publish(&packet);

    //     log_info(LOG_TAG, "Shutter button %s.\n", button_state ? "pressed" : "released");
    // }
}

void buttons_main()
{
    // Set the starting values for the buttons
    for (uint8_t i = 0; i < LEN_BTNS(buttons_to_check); i++)
    {
        button_state[i] = button_get_state(buttons_to_check[i]);
    }

    // Start the task
    TimerHandle_t timer = xTimerCreate((const char *)"Buttons Timer", pdMS_TO_TICKS(100), pdTRUE, NULL, button_state_resolver);
    xTimerStart(timer, 0);

    // Run off the end of our rope
    vTaskDelete(NULL);
}