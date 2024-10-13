#include "system.h"

#include "apps_config.h"

#include "pipe.h"
#include "cpubsub.h"
#include "messages.h"
#include "log.h"
#include "gmax0505.h"

#include "xaxidma.h"
#include "xscugic.h"
#include "xil_exception.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include <string.h>
#include <stdlib.h>

#define LOG_TAG "IMG"

#define XPAR_FABRIC_SENSOR_FRAME_RDY_INTERRUPT_INTR (66)
#define XPAR_FABRIC_SENSOR_FRAME_DONE_INTERRUPT_INTR (67)

#define IMG_SIZE_B ((uint32_t)60e6)

extern XScuGic xInterruptController;

static bool tick = false;
static bool run = false;

static uint32_t *image_buffer = NULL;

static XAxiDma dma = {0};

static void imaging_frame_rdy_handler(void *ctx)
{
    log_warn(LOG_TAG, "Frame ready\n");
}

static void imaging_frame_done_handler(void *ctx)
{
    log_warn(LOG_TAG, "Frame done\n");
}

static void imaging_timer_cb(TimerHandle_t timer)
{
    tick = true;
}

static void imaging_init_intr(void)
{
    XScuGic *gic = &xInterruptController;

    XScuGic_SetPriorityTriggerType(gic, XPAR_FABRIC_SENSOR_FRAME_RDY_INTERRUPT_INTR, 0xA0, 0x3);
    int status = XScuGic_Connect(gic, XPAR_FABRIC_SENSOR_FRAME_RDY_INTERRUPT_INTR, (Xil_ExceptionHandler)imaging_frame_rdy_handler, NULL);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XScuGic_Connect failed with code = %d\n", status);
    }
    XScuGic_Enable(gic, XPAR_FABRIC_SENSOR_FRAME_RDY_INTERRUPT_INTR);

    XScuGic_SetPriorityTriggerType(gic, XPAR_FABRIC_SENSOR_FRAME_DONE_INTERRUPT_INTR, 0xA0, 0x3);
    status = XScuGic_Connect(gic, XPAR_FABRIC_SENSOR_FRAME_DONE_INTERRUPT_INTR,
                             (Xil_ExceptionHandler)imaging_frame_done_handler, NULL);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XScuGic_Connect failed with code = %d\n", status);
    }

    XScuGic_Enable(gic, XPAR_FABRIC_SENSOR_FRAME_DONE_INTERRUPT_INTR);
}

static void imaging_init_dma(void)
{
    // Attempt to get some data
    image_buffer = (uint32_t *)malloc(IMG_SIZE_B);
    if (image_buffer == NULL)
    {
        log_error(LOG_TAG, "image_buffer == NULL\n");
        return;
    }

    XAxiDma_Config *config = XAxiDma_LookupConfig(XPAR_SENSOR_0_AXI_DMA_0_DEVICE_ID);
    if (config == NULL)
    {
        log_error(LOG_TAG, "XAxiDma_LookupConfig failed\n");
        return;
    }

    int status = XAxiDma_CfgInitialize(&dma, config);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiDma_CfgInitialize failed with code = %d\n", status);
        return;
    }

    XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
    XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);
}

static void imaging_start_dma(void)
{
    Xil_DCacheFlushRange((UINTPTR)image_buffer, IMG_SIZE_B);
    int status = XAxiDma_SimpleTransfer(&dma, (UINTPTR)image_buffer, IMG_SIZE_B, XAXIDMA_DEVICE_TO_DMA);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiDma_SimpleTransfer failed with code = %d\n", status);
        return;
    }
}

void imaging_main(void *params)
{
    run = true;
    pipe_t pipe = {0};
    uint8_t *buffer = NULL;

    system_t *sys = (system_t *)params;
    if (sys == NULL)
    {
        log_error(LOG_TAG, "sys == NULL.\n");
        run = false;
    }

    pipe_set_length(&pipe, SYS_ACTION_PIPE_LEN);
    cps_subscribe(MSGButtonPress_MID, MSGButtonPress_LEN, &pipe);

    /* Assign some space for the display buffer */
    buffer = (uint8_t *)malloc((size_t)pipe_item_size(&pipe));
    if (buffer == NULL)
    {
        log_error(LOG_TAG, "malloc failed.\n");

        // Do not continue
        run = false;
    }

    // Init the sensor
    gmax_error_t error = gmax_init();
    if (error == GMAX_OK)
    {
        log_info(LOG_TAG, "GMAX init success\n");
        sys->imaging.sync = true;
    }

    else
    {
        log_error(LOG_TAG, "GMAX init fail with %s\n", gmax_error_string(error));
        run = false;
        sys->imaging.sync = false;
    }

    imaging_init_intr();
    imaging_init_dma();

    // Default screen
    TimerHandle_t timer = xTimerCreate("Imaging Tick", pdMS_TO_TICKS(SYS_IMG_TICK_PERIOD_MS), true, NULL, imaging_timer_cb);
    xTimerStart(timer, 0);

    // Go forever
    while (run == true)
    {
        // Wait for the tick to arrive
        if (tick == true)
        {
            // Reset the flag
            tick = false;

            if (sys->imaging.take_image == true)
            {
                sys->imaging.take_image = false;

                imaging_start_dma();

                gmax_frame_request(sys->imaging.speed_us, sys->imaging.iso, sys->imaging.res);

                log_info(LOG_TAG, "Taking image\n");
            }

            gmax_sensor_temperature(&sys->imaging.sensor_temp_c);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    // Should never reach here if all is okay
    vTaskDelete(NULL);
}