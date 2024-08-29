#pragma once

#include <stdint.h>

typedef enum
{
    UART_PORT_0 = 0,
    UART_PORT_1,
} uart_port_t;

void uart_init(void);
void uart_send(uart_port_t port, uint8_t *data, uint32_t len);
uint32_t uart_receive(uart_port_t port, uint8_t *data, uint32_t len);

void uart_dma_test(void);