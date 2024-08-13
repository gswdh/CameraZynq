#include "log.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"

// Xilinx includes
#include "xil_printf.h"

void log_transmit(const char *log)
{
    xil_printf("%s", log);
}

uint32_t log_get_time()
{
    return (uint32_t)xTaskGetTickCount();
}