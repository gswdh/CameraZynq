#include "sy103.h"

#include "i2c.h"
#include "gpio.h"
#include "log.h"

#include "xparameters.h"
#include "xdsitxss.h"
#include "xaxivdma.h"
#include "xil_cache.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdbool.h>
#include <stdint.h>

#define LOG_TAG "EVF_INT"

static XDsiTxSs dsi_tx = {0};
static XAxiVdma vdma = {0};

void sy103_delay_ms(const uint32_t time_ms)
{
    vTaskDelay(pdMS_TO_TICKS(time_ms));
}

void sy103_i2c_write(const uint8_t reg, const uint8_t *const data, const uint32_t len)
{
    i2c_write_reg(SY103_I2C_ADDR, reg, data, len);
}

void sy103_i2c_read(const uint8_t reg, uint8_t *const data, const uint32_t len)
{
    i2c_read_reg(SY103_I2C_ADDR, reg, data, len);
}

void sy103_enable_avdd(const bool enable)
{
    gpio_write(PWR_EVF_AVDD_EN, enable);
}

void sy103_enable_avee(const bool enable)
{
    gpio_write(PWR_EVF_AVEE_EN, enable);
}

void sy103_reset(const bool reset)
{
    gpio_write(EVF_NRESET, !reset);
}

sy103_error_t sy103_init_mipi(const uint8_t *const buffer)
{
    // Do the initial DSI TX setup
    XDsiTxSs_Config *config = XDsiTxSs_LookupConfig(XPAR_MIPI_DSI_TX_SUBSYSTEM_0_DEVICE_ID);

    int status = XDsiTxSs_CfgInitialize(&dsi_tx, config, config->BaseAddr);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XDsiTxSs_CfgInitialize error with code = %d\n", status);
        return SY103_MIPI_INIT_ERROR;
    }

    status = XDsiTxSs_SelfTest(&dsi_tx);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XDsiTxSs_SelfTest error with code = %d\n", status);
        return SY103_MIPI_INIT_ERROR;
    }

    XDsiTxSs_Reset(&dsi_tx);

    // Set the Video Peripheral timing parameters
    XDsi_VideoTiming timing = {
        .HActive = 1280,
        .HBackPorch = 32,
        .HFrontPorch = 64,
        .HSyncWidth = 2, // This is a guess to be the same as the VSyncWidth
        .VActive = 1280,
        .VBackPorch = 14,
        .VSyncWidth = 2,
        .BLLPBurst = 0, // As in the Xilinx example (https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/dsitxss/examples/xdsitxss_video_test_example.c#L365)
    };

    XDsiTxSs_SetCustomVideoInterfaceTiming(&dsi_tx, XDSI_VM_NON_BURST_SYNC_EVENT, &timing);

    // Init and start the VDMA
    XAxiVdma_Config *vmda_conf = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);

    status = XAxiVdma_CfgInitialize(&vdma, vmda_conf, vmda_conf->BaseAddress);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiVdma_CfgInitialize error with code = %d\n", status);
        return SY103_MIPI_INIT_ERROR;
    }

    status = XAxiVdma_Selftest(&vdma);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiVdma_Selftest error with code = %d\n", status);
        return SY103_MIPI_INIT_ERROR;
    }

    XAxiVdma_DmaSetup vdma_setup = {
        .EnableVFlip = 0,
        .FixedFrameStoreAddr = 0,
        .GenLockRepeat = 0,

        .FrameStoreStartAddr = 0,
        .EnableSync = 0,
        .FrameDelay = 0,
        .PointNum = 0,
        .EnableCircularBuf = 1,
        .EnableFrameCounter = 0,
        .Stride = 1376,
        .HoriSizeInput = 1280,
        .VertSizeInput = 1280,
    };

    status = XAxiVdma_DmaConfig(&vdma, XAXIVDMA_READ, &vdma_setup);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiVdma_DmaConfig error with code = %d\n", status);
        return SY103_MIPI_INIT_ERROR;
    }

    Xil_DCacheFlushRange((INTPTR)buffer, vdma_setup.VertSizeInput * vdma_setup.HoriSizeInput);

    status = XAxiVdma_DmaSetBufferAddr(&vdma, XAXIVDMA_READ, (UINTPTR *)buffer);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiVdma_DmaSetBufferAddr error with code = %d\n", status);
        return SY103_MIPI_INIT_ERROR;
    }

    status = XAxiVdma_DmaStart(&vdma, XAXIVDMA_READ);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XAxiVdma_DmaStart error with code = %d\n", status);
        return SY103_MIPI_INIT_ERROR;
    }

    // Start the DSI TX
    status = XDsiTxSs_Activate(&dsi_tx, XDSITXSS_DSI, XDSITXSS_ENABLE);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XDsiTxSs_Activate XDSITXSS_DSI error with code = %d\n", status);
        return SY103_MIPI_INIT_ERROR;
    }

    status = XDsiTxSs_Activate(&dsi_tx, XDSITXSS_PHY, XDSITXSS_ENABLE);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XDsiTxSs_Activate XDSITXSS_PHY error with code = %d\n", status);
        return SY103_MIPI_INIT_ERROR;
    }

    // All done
    log_info(LOG_TAG, "init success\n");
    return SY103_OK;
}