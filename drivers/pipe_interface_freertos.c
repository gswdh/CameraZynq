#include "pipe.h"

#include <stdlib.h>

#include <FreeRTOS.h>
#include <queue.h>

void pipe_init(pipe_t *pipe, uint32_t obj_size, uint32_t queue_len)
{
    // Do we already have a queue for this pipe?
    if (pipe->queue && pipe->obj_size < obj_size)
    {
        // Destory this queue to make a new one
        vQueueDelete(*(QueueHandle_t *)(pipe->queue));
        free(pipe->queue);
        pipe->queue = NULL;
    }

    // Make a queue if needed
    if (!pipe->queue)
    {
        // Create the FreeRTOS queue
        pipe->queue = malloc(sizeof(QueueHandle_t));
        *(QueueHandle_t *)pipe->queue = xQueueCreate(queue_len, obj_size);

        // Take note of the object size
        pipe->obj_size = obj_size;
    }
}

void pipe_delete(pipe_t *pipe)
{
    if (pipe->queue)
    {
        vQueueDelete(pipe->queue);
    }
}

void pipe_push(pipe_t *pipe, void *p_item)
{
    xQueueSend(*(QueueHandle_t *)pipe->queue, (void *)p_item, (TickType_t)0);
}

bool pipe_pop(pipe_t *pipe, void *p_item)
{
    if (xQueueReceive(*(QueueHandle_t *)pipe->queue, (void *)p_item, (TickType_t)10) == pdPASS)
    {
        return true;
    }

    return false;
}