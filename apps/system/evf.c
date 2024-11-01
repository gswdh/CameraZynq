#include "system.h"

#include "sy103.h"
#include "log.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdlib.h>
#include <string.h>

#define LOG_TAG "EVF"

#define EVF_FRAME_BUFF_ADDR (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x400000)

static uint32_t *evf_frame_buffer = (uint32_t *)EVF_FRAME_BUFF_ADDR;

void evf_main(void *params)
{
    // Get some memory for the frame buffer
    if (evf_frame_buffer != NULL)
    {
        sy103_init((uint8_t *)evf_frame_buffer);
    }

    else
    {
        log_error(LOG_TAG, "evf_frame_buffer == NULL\n");
    }

    // All done
    vTaskDelete(NULL);
}