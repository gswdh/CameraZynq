#include "log.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"

#include "xil_printf.h"

void log_send_data(const char *msg, uint32_t msg_len)
{
    xil_printf("%s", msg);
}

uint32_t log_get_time()
{
    return (uint32_t)xTaskGetTickCount();
}