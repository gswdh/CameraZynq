#include "xil_printf.h"

#include "log.h"

void log_send_data(const char *msg, uint32_t msg_len)
{
    xil_printf("%s", msg);
}

uint32_t log_get_time()
{
    return 0;
}