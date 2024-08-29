#pragma once

#define NET_PUB_BUFF_LEN (1024)
#define NET_PUB_UART UART_PORT_0

void net_pub_task(void *params);