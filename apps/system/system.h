#pragma once

#include "buttons.h"

#include <stdint.h>

// Button events builder

typedef struct
{
    uint32_t iso;
    uint32_t speed_us;
} system_imaging_t;

typedef struct
{
    system_imaging_t imaging;
} system_t;

void system_main(void *params);
void actions_main(void *params);