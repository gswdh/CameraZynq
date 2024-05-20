#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct sensor_config_struct
{
    /* Sensor meta data */
    float sensor_shutter_s;
    bool sensor_shutter_man;
    float sensor_iso;
    bool sensor_iso_man;
} sensor_config_t;

typedef struct system_state_struct
{
    sensor_config_t sensor_config;
} system_state_t;

void system_start();