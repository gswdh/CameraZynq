#include "gui.h"

#include "log.h"

#include <stdio.h>

#define LOG_TAG "GUI"

static void gui_draw_line(uint8_t x_1, uint8_t y_1, uint8_t x_2, uint8_t y_2, uint8_t state)
{
    dmgui_draw_line(x_1, y_1, x_2, y_2, state);
}

static void gui_draw_rect(uint8_t x_1, uint8_t y_1, uint8_t x_2, uint8_t y_2, uint8_t filled)
{
    dmgui_draw_rect(x_1, y_1, x_2, y_2, filled);
}

static void gui_draw_image(const uint8_t *image)
{
    dmgui_add_image(image);
}

static void gui_draw_text(const char *text, uint8_t x, uint8_t y, uint8_t alignment)
{
    dmgui_add_text((char *)text, x, y, alignment);
}

static void gui_text_screen(const char const *text[8])
{
}

static void gui_welcome_screen(void)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    sprintf(text, "SOKE CAMERA 1.2.0");
    gui_draw_text(text, 0, 4, GUI_TXT_ALIGN_L);
}

static void gui_home_screen(const uint32_t iso, const uint32_t speed, const uint8_t soc, const float consumption, const float charging)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    sprintf(text, "%u ISO", iso);
    gui_draw_text(text, 0, 0, GUI_TXT_ALIGN_L);

    sprintf(text, "1/%us", (uint32_t)(10e6 / speed));
    gui_draw_text(text, 0, 1, GUI_TXT_ALIGN_L);

    sprintf(text, "SoC %u%%", soc);
    gui_draw_text(text, 0, 2, GUI_TXT_ALIGN_L);

    sprintf(text, "%2.3fW", consumption);
    gui_draw_text(text, 0, 3, GUI_TXT_ALIGN_L);

    if (charging > 0)
    {
        sprintf(text, "Charging @ %2.3fW", charging);
        gui_draw_text(text, 0, 4, GUI_TXT_ALIGN_L);
    }
}

static void gui_iso_set_screen(const uint32_t iso)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    sprintf(text, "Set to %u ISO", iso);
    gui_draw_text(text, 0, 0, GUI_TXT_ALIGN_L);
}

static void gui_shutter_set_screen(const uint32_t speed)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    sprintf(text, "Set to 1/%us", (uint32_t)(10e6 / speed));
    gui_draw_text(text, 0, 0, GUI_TXT_ALIGN_L);
}

static void gui_power_info_screen(void)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    sprintf(text, "POWER INFO");
    gui_draw_text(text, 0, 0, GUI_TXT_ALIGN_L);
}

static void gui_memory_info_screen(void)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    sprintf(text, "MEMORY INFO");
    gui_draw_text(text, 0, 0, GUI_TXT_ALIGN_L);
}

void gui_refresh(system_t *sys)
{
    switch (sys->gui.screen)
    {
    case SYS_GUI_HOME_SCR:
        gui_home_screen(sys->imaging.iso, sys->imaging.speed_us, sys->power.battery.soc, sys->power.pmc.bus_power, sys->power.battery.voltage * sys->power.battery.current);
        break;
    case SYS_GUI_ISO_SET_SCR:
        gui_iso_set_screen(sys->imaging.iso);
        break;
    case SYS_GUI_SHTR_SET_SCR:
        gui_shutter_set_screen(sys->imaging.speed_us);
        break;
    case SYS_GUI_POWER_INFO_SCR:
        gui_power_info_screen();
        break;
    case SYS_GUI_MEMORY_INFO_SCR:
        gui_memory_info_screen();
        break;
    default:
        log_warn(LOG_TAG, "Screen not supported\n");
        break;
    }
}
