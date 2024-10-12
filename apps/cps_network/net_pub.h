#pragma once

#include "apps_config.h"

typedef enum
{
    NET_PUB_START_STATE = 0,
    NET_PUB_PAYLOAD_STATE,
    NET_PUB_END_STATE,
} net_pub_rx_state_t;

void net_pub_task(void *params);