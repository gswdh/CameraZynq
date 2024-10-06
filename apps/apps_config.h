#pragma once

// CPS Network
#define NET_PUB_BUFF_LEN (1024)

// Debugging
#define DBG_APP_STACK_SIZE_B (256)
#define DBG_PIPE_LEN (64)
#define DBG_TICK_PERIOD_MS (100)

// Display
#define DSP_APP_STACK_SIZE_B (4096)
#define DSP_TICK_PERIOD_MS (20)

// Network Publisher
#define NET_PUB_APP_STACK_SIZE_B (256)
#define NET_PUB_TICK_PERIOD_MS (100)
#define NET_PUB_BUFF_LEN (1024)
#define NET_PUB_UART UART_PORT_0

// Buttons
#define BTN_APP_STACK_SIZE_B (128)
#define BTN_TICK_PERIOD_MS (50)

// System
#define SYS_APP_STACK_SIZE_B (512)
#define SYS_TICK_BLINK_PERIOD_MS (50)
#define SYS_TICK_ACTION_PERIOD_MS (20)
#define SYS_ACTION_PIPE_LEN (64)
#define SYS_APP_ACTIONS_PRIORITY (3)

#define SYS_ACT_APP_STACK_SIZE_B (512)