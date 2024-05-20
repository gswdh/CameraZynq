#pragma once

#define N_BUTTONS (sizeof(buttons_to_check) / sizeof(buttons_to_check[0]))

typedef enum
{
    RELEASED,
    HALF,
    FULL
} shutter_button_state_t;

typedef enum
{
    BTN_BL,
    BTN_BR,
    BTN_THMB,
    BTN_TL,
    BTN_TR,
    BTN_SHTR
} button_t;

typedef enum
{
    BTN_RISING,
    BTN_FALLING,
} button_edge_t;

void buttons_start();