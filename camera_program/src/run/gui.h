#pragma once

#include <stdint.h>

typedef enum
{
    GUI_ACT_UNKNOWN,
    GUI_ACT_INC_ISO,
    GUI_ACT_DEC_ISO,
    GUI_ACT_INC_SHUTTER,
    GUI_ACT_DEC_SHUTTER,
    GUI_ACT_GOTO_HOME,
    GUI_ACT_GOTO_ISO_ADJ,
    GUI_ACT_GOTO_SHTR_ADJ,
} gui_action_t;

typedef enum
{
    GUI_SCRN_HOME,
    GUI_SCRN_ISO_ADJ,
    GUI_SCRN_SHTR_ADJ,
} gui_screen_t;

typedef struct
{
    gui_screen_t gui_screen;

    float sensitivity_iso;
    float shutter_speed;

    uint32_t tick;
} gui_state_t;

void gui_start();