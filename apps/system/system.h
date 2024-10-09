#pragma once

#include "buttons.h"
#include "messages.h"
#include "gmax0505.h"

#include <stdint.h>
#include <stdbool.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof(x[0]))
#define SYS_GUI_N_BASE_SCRS(x) ARRAY_LEN(x)

typedef enum
{
    SYS_GUI_HOME_SCR = 0,
    SYS_GUI_ISO_SET_SCR,
    SYS_GUI_SHTR_SET_SCR,
    SYS_GUI_POWER_INFO_SCR,
    SYS_GUI_MEMORY_INFO_SCR,
} system_gui_screen_t;

typedef struct
{
    system_gui_screen_t screen;
} system_gui_t;

typedef struct
{
    bool sync;
    uint32_t iso;
    uint32_t speed_us;
    bool take_image;
    float sensor_temp_c;
    gmax_resolution_t res;
} system_imaging_t;

typedef struct
{
    MSGSystemStats_t pmc;
    MSGBatteryStats_t battery;
    MSGChargingStats_t charging;
    MSGUSBPDStats_t usbpd;
} system_power_t;

typedef struct
{
    system_gui_t gui;
    system_imaging_t imaging;
    system_power_t power;
} system_t;

void system_main(void *params);
void actions_main(void *params);
void imaging_main(void *params);
void evf_main(void *params);

#define ACT_BTN_SCR_ISO_SET (BTN_TOPLEFT_RI)
#define ACT_BTN_SCR_ISO_RETURN (BTN_TOPLEFT_FA)
#define ACT_BTN_INC_ISO (BTN_TOPLEFT_HI | BTN_TOPRIGHT_RI)
#define ACT_BTN_DEC_ISO (BTN_TOPLEFT_HI | BTN_BTMRIGHT_RI)

#define ACT_BTN_SCR_SHTR_SET (BTN_BTMLEFT_RI)
#define ACT_BTN_SCR_SHTR_RETURN (BTN_BTMLEFT_FA)
#define ACT_BTN_INC_SHTR (BTN_BTMLEFT_HI | BTN_TOPRIGHT_RI)
#define ACT_BTN_DEC_SHTR (BTN_BTMLEFT_HI | BTN_BTMRIGHT_RI)

#define ACT_BTN_SCR_BASE_INC (BTN_TOPRIGHT_RI)
#define ACT_BTN_SCR_BASE_DEC (BTN_BTMRIGHT_RI)

#define ACT_BTN_TAKE_IMG (BTN_THUMB_RI)
