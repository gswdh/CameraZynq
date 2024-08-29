#pragma once

#define LEN_BTNS(btns) (sizeof(btns) / sizeof(btns[0]))

#define SHUTTER_BTN_THRSH 600

typedef enum
{
    RELEASED,
    HALF,
    FULL
} shutter_button_state_t;

typedef enum
{
    BTN_BL = 0,
    BTN_BR,
    BTN_THMB,
    BTN_TL,
    BTN_TR,
    BTN_SHTR
} button_t;

typedef enum
{
    BTN_STATE_LO = 0,
    BTN_STATE_HI,
    BTN_STATE_RISING,
    BTN_STATE_FALLING,
} button_state_t;

void buttons_main();
shutter_button_state_t shutter_button();