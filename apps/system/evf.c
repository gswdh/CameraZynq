#include "system.h"

#include "sy103.h"
#include "log.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdlib.h>
#include <string.h>

#define LOG_TAG "EVF"

static uint8_t *evf_frame_buffer = NULL;

void evf_main(void *params)
{
    // Get some memory for the frame buffer
    evf_frame_buffer = (uint8_t *)malloc(1280 * 1280 * 3);
    if (evf_frame_buffer != NULL)
    {
        sy103_init(evf_frame_buffer);

        memset(evf_frame_buffer, 0x55, 1280 * 1280 * 3);
    }

    else
    {
        log_error(LOG_TAG, "evf_frame_buffer == NULL\n");
    }

    // All done
    vTaskDelete(NULL);
}