#include "cpubsub_network.h"

#include "net_pub.h"

#include "uart.h"

void cps_network_transmit(uint8_t *data, uint32_t len)
{
    uart_send(NET_PUB_UART, data, len);
}