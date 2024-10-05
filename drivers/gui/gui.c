#include "gui.h"

#include "log.h"

#include "FreeRTOS.h"
#include "task.h"

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

static void gui_power_info_screen(system_t *sys)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    // PMC
    gui_draw_text("PMC", 0, 0, GUI_TXT_ALIGN_L);
    sprintf(text, "%2.1fV %2.1fA %2.1fW %uC",
            sys->power.pmc.bus_voltage,
            sys->power.pmc.bus_current,
            sys->power.pmc.bus_power,
            (uint8_t)sys->power.pmc.pmc_temp);
    gui_draw_text(text, 0, 1, GUI_TXT_ALIGN_L);

    // Charger
    gui_draw_text("Charger", 0, 2, GUI_TXT_ALIGN_L);

    if (sys->power.charging.charging == 1)
    {
        sprintf(text, "%2.1fV %2.1fA %uC",
                sys->power.charging.output_voltage,
                sys->power.charging.output_current,
                (uint8_t)sys->power.charging.chrgr_temp);
    }
    else
    {
        sprintf(text, "Not Charging");
    }
    gui_draw_text(text, 0, 3, GUI_TXT_ALIGN_L);

    // BMS
    gui_draw_text("BMS", 0, 4, GUI_TXT_ALIGN_L);
    sprintf(text, "%2.1fV %2.1fA %u%% %1.1fAh",
            sys->power.battery.voltage,
            sys->power.battery.current,
            (uint8_t)sys->power.battery.soc,
            sys->power.battery.capacity);
    gui_draw_text(text, 0, 5, GUI_TXT_ALIGN_L);

    // USBPD
    gui_draw_text("USBPD", 0, 6, GUI_TXT_ALIGN_L);

    if (sys->power.usbpd.attached == 1)
    {
        sprintf(text, "%2.1fV %2.1fA",
                sys->power.usbpd.bus_voltage,
                sys->power.usbpd.bus_current);
    }
    else
    {
        sprintf(text, "Disconnected");
    }
    gui_draw_text(text, 0, 7, GUI_TXT_ALIGN_L);
}

static void gui_memory_info_screen(void)
{
    char text[64] = {0};

    dmgui_fill_screen(GUI_CLR_BLACK);

    sprintf(text, "MEMORY INFO");
    gui_draw_text(text, 0, 0, GUI_TXT_ALIGN_L);

    // TaskStatus_t *taskStatusArray;
    // UBaseType_t totalTasks;
    // UBaseType_t i;
    // uint32_t totalStackUsed = 0;

    // // Get the number of tasks
    // totalTasks = uxTaskGetNumberOfTasks();

    // // Allocate memory for task status array
    // taskStatusArray = pvPortMalloc(totalTasks * sizeof(TaskStatus_t));

    // if (taskStatusArray != NULL)
    // {
    //     // Get system state
    //     uxTaskGetSystemState(taskStatusArray, totalTasks, NULL);

    //     for (i = 0; i < totalTasks; i++)
    //     {
    //         xil_printf("%s - %uB\n", taskStatusArray[i].pcTaskName, taskStatusArray[i].usStackHighWaterMark);
    //     }

    //     vPortFree(taskStatusArray);
    // }

    size_t totalHeapSize = configTOTAL_HEAP_SIZE;
    size_t freeHeapSize = xPortGetFreeHeapSize();
    size_t usedHeapSize = totalHeapSize - freeHeapSize;

    sprintf(text, "%u/%ukiB", (uint32_t)(usedHeapSize / 1024), (uint32_t)(totalHeapSize / 1024));
    gui_draw_text(text, 0, 1, GUI_TXT_ALIGN_L);
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
        gui_power_info_screen(sys);
        break;
    case SYS_GUI_MEMORY_INFO_SCR:
        gui_memory_info_screen();
        break;
    default:
        log_warn(LOG_TAG, "Screen not supported\n");
        break;
    }
}
