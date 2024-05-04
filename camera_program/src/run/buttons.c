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
#include "spi.h"

#define LOG_TAG "BUTTONS"

#define SHUTTER_BTN_THRSH 600

static const gpio_pin_t buttons_to_check[] = {
    BTN_BTMLEFT,
    BTN_BTMRIGHT,
    BTN_THUMB,
    BTN_TOPLEFT,
    BTN_TOPRIGHT};

static bool button_states[N_BUTTONS] = {0};

static MSGButtonPress_t packet = {0};

static shutter_button_state_t shutter_button_state = RELEASED;

static badc_spi_read(uint8_t *data, uint32_t len)
{
    gpio_write(BADC_SPI_NCS, false);
    spi_0_rx(data, len);
    gpio_write(BADC_SPI_NCS, true);
}

static shutter_button_state_t shutter_button_state()
{
    uint8_t data[2] = {0};
    badc_spi_read(data, 2);
    uint16_t value = ((data[0] << 8) + data[1]) >> 2;

    return value > SHUTTER_BTN_THRSH ? FULL : RELEASED;
}

static void buttons_tasks()
{
    /* Check the regular push buttons */
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

    /* Check the shutter button */
    shutter_button_state_t button_state = shutter_button_value();
    if (button_state != shutter_button_state)
    {
        /* Update the state */
        shutter_button_state = state;

        /* Tell the system about this button press */
        packet.button = 6;
        packet.type = shutter_button_state;
        cps_publish(&packet);

        log_info(LOG_TAG, "Shutter button %s.\n", button_state ? "pressed" : "released");
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
