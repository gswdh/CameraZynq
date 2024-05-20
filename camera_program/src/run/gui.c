#include "gui.h"

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

#include "dmgui.h"
#include "ssd1309z.h"
#include "buttons.h"

#define LOG_TAG "GUI"

/* Make a new pipe */
static pipe_t pipe = {0};
static uint8_t data[1024] = {0};

/* GUI state */
static gui_state_t gui_state = {0};

/* Make some space for messages */
static MSGGUIActions_t action_msg = {0};

static void gui_handle_action(gui_action_t action)
{
    switch (action)
    {
    case GUI_ACT_UNKNOWN:
        break;
    case GUI_ACT_INC_ISO:
    case GUI_ACT_DEC_ISO:
    case GUI_ACT_INC_SHUTTER:
    case GUI_ACT_DEC_SHUTTER:
        action_msg.mid = MSGGUIActions_MID;
        action_msg.action = action;
        cps_publish(&action_msg);
        break;
    case GUI_ACT_GOTO_HOME:
        gui_state.gui_screen = GUI_SCRN_HOME;
        break;
    case GUI_ACT_GOTO_ISO_ADJ:
        gui_state.gui_screen = GUI_SCRN_ISO_ADJ;
        break;
    case GUI_ACT_GOTO_SHTR_ADJ:
        gui_state.gui_screen = GUI_SCRN_SHTR_ADJ;
        break;
    default:
        break;
    }
}

static gui_action_t gui_button_action(uint8_t button, uint8_t edge)
{
    switch (gui_state.gui_screen)
    {
    case GUI_SCRN_HOME:
        /* Rising edge on the top left adjusts ISO */
        if (button == BTN_TL && edge == BTN_RISING)
        {
            return GUI_ACT_GOTO_ISO_ADJ;
        }

        /* Rising edge on the bottom left adjusts shutter speed */
        if (button == BTN_BL && edge == BTN_RISING)
        {
            return GUI_ACT_GOTO_SHTR_ADJ;
        }
        break;
    case GUI_SCRN_ISO_ADJ:
        /* Rising edge on the top right increments ISO */
        if (button == BTN_TR && edge == BTN_RISING)
        {
            return GUI_ACT_INC_ISO;
        }
        /* Rising edge on the bottom right decrements ISO */
        if (button == BTN_BR && edge == BTN_RISING)
        {
            return GUI_ACT_DEC_ISO;
        }
        /* Falling edge on the top left goes back to home */
        if (button == BTN_TL && edge == BTN_FALLING)
        {
            return GUI_ACT_GOTO_HOME;
        }
        break;
    case GUI_SCRN_SHTR_ADJ:
        /* Rising edge on the top right increments shutter */
        if (button == BTN_TR && edge == BTN_RISING)
        {
            return GUI_ACT_INC_SHUTTER;
        }
        /* Rising edge on the bottom right decrements shutter */
        if (button == BTN_BR && edge == BTN_RISING)
        {
            return GUI_ACT_DEC_SHUTTER;
        }
        /* Falling edge on the top left goes back to home */
        if (button == BTN_BL && edge == BTN_FALLING)
        {
            return GUI_ACT_GOTO_HOME;
        }
        break;
    default:
        break;
    }

    return GUI_ACT_UNKNOWN;
}

static void gui_buttons_handler(uint8_t button, uint8_t edge)
{
    log_info(LOG_TAG, "gui_buttons_handler button = %u, edge = %u\n", button, edge);
    gui_action_t action = gui_button_action(button, edge);
    gui_handle_action(action);
}

static void gui_screen_home()
{
    dmgui_fill_screen(GUI_CLR_BLACK);
    char display_text[100] = {0};
    sprintf(display_text, "HOME");
    dmgui_add_text(display_text, 0, 0, GUI_TXT_ALIGN_L);

    sprintf(display_text, "ISO %f", gui_state.sensitivity_iso);
    dmgui_add_text(display_text, 0, 1, GUI_TXT_ALIGN_L);

    sprintf(display_text, "SHUTTER %f", gui_state.shutter_speed);
    dmgui_add_text(display_text, 0, 2, GUI_TXT_ALIGN_L);

    sprintf(display_text, "TICK %ums", xTaskGetTickCount());
    dmgui_add_text(display_text, 0, 3, GUI_TXT_ALIGN_L);
}

static void gui_screen_iso_adj()
{
    dmgui_fill_screen(GUI_CLR_BLACK);
    char display_text[100] = {0};
    sprintf(display_text, "ISO %f", gui_state.sensitivity_iso);
    dmgui_add_text(display_text, 0, 0, GUI_TXT_ALIGN_L);
}

static void gui_screen_shtr_adj()
{
    dmgui_fill_screen(GUI_CLR_BLACK);
    char display_text[100] = {0};
    sprintf(display_text, "SHUTTER %f", gui_state.shutter_speed);
    dmgui_add_text(display_text, 0, 0, GUI_TXT_ALIGN_L);
}

static void gui_draw_screen()
{
    switch (gui_state.gui_screen)
    {
    case GUI_SCRN_HOME:
        gui_screen_home();
        break;
    case GUI_SCRN_ISO_ADJ:
        gui_screen_iso_adj();
        break;
    case GUI_SCRN_SHTR_ADJ:
        gui_screen_shtr_adj();
        break;
    default:
        break;
    }
}

static void gui_task(void *params)
{
    gui_draw_screen();

    while (true)
    {
        /* Wait for some data to arrive */
        cps_receive(&pipe, data, PIPE_WAIT_BLOCK);

        topic_t mid = cps_get_mid(data);

        if (mid == MSGButtonPress_MID)
        {
            MSGButtonPress_t *button_press = (MSGButtonPress_t *)data;
            gui_buttons_handler(button_press->button, button_press->edge);
        }

        if (mid == MSGSensorSettings_MID)
        {
            MSGSensorSettings_t *sensor_settings = (MSGSensorSettings_t *)data;

            gui_state.sensitivity_iso = sensor_settings->sensitivity_iso;
            gui_state.shutter_speed = sensor_settings->shutter_speed;

            log_info(LOG_TAG, "gui_task %f, %f\n", gui_state.sensitivity_iso, gui_state.shutter_speed);
        }

        gui_draw_screen();
    }

    vTaskDelete(NULL);
}

void gui_start()
{
    /* Setup the initial GUI state */
    gui_state.gui_screen = GUI_SCRN_HOME;

    /* Subscribe to the relvant message MIDs */
    cps_subscribe(MSGButtonPress_MID, MSGButtonPress_LEN, &pipe);
    cps_subscribe(MSGSensorSettings_MID, MSGSensorSettings_LEN, &pipe);

    /* Start the task */
    xTaskCreate(gui_task, "GUI Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}