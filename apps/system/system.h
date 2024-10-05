#pragma once

#include "buttons.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint32_t iso;
    uint32_t speed_us;
} system_imaging_t;

typedef struct
{
    float consumption_w;
    uint8_t soc_p;
    float charging_w;
} system_power_t;

typedef struct
{
    system_imaging_t imaging;
    system_power_t power;
} system_t;

void system_main(void *params);
void actions_main(void *params);