#pragma once

#define N_BUTTONS (sizeof(buttons_to_check) / sizeof(buttons_to_check[0]))

typedef enum
{
    RELEASED,
    HALF,
    FULL
} shutter_button_state_t;

void buttons_start();