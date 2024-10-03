#include "gui.h"

#include <stdio.h>

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

void gui_text_screen(const char const *text[8])
{
}

void gui_welcome_screen(void)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    sprintf(text, "SOKE CAMERA 1.2.0");
    gui_draw_text(text, 0, 4, GUI_TXT_ALIGN_L);
}

void gui_home_screen(const uint32_t iso, const uint32_t speed, const uint8_t soc)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    sprintf(text, "%u ISO", iso);
    gui_draw_text(text, 0, 0, GUI_TXT_ALIGN_L);

    sprintf(text, "1/%us", (uint32_t)(10e6 / speed));
    gui_draw_text(text, 0, 1, GUI_TXT_ALIGN_L);

    sprintf(text, "SoC %u%%", soc);
    gui_draw_text(text, 0, 2, GUI_TXT_ALIGN_L);
}