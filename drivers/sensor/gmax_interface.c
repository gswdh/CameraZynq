#include "gmax0505.h"

#include "gpio.h"
#include "log.h"

#include "xparameters.h"
#include "xgpio.h"

#include "FreeRTOS.h"
#include "task.h"

#include <assert.h>

#define LOG_TAG "GMAX_INT"

static XGpio gmax_gpio = {0};

void gmax_delay_ms(const uint32_t time_ms)
{
    vTaskDelay(pdMS_TO_TICKS(time_ms));
}

bool gmax_pin_read(const gmax_pin_t pin)
{
    switch (pin)
    {
    case SPI_MISO:
        return gpio_read(SEN_SPI_MISO);
        break;
    case SYNC_STATUS:
        assert(false && "SYNC_STATUS not implemented.");
        break;
    case FRAME_RDY:
        assert(false && "FRAME_RDY not implemented.");
        break;
    case FRAME_PROG:
        assert(false && "FRAME_PROG not implemented.");
        break;
    default:
        return 0;
        break;
    }

    return 0;
}

void gmax_pin_write(const gmax_pin_t pin, const bool value)
{
    switch (pin)
    {
    case PWR_0V7_EN:
        gpio_write(PWR_SEN_0V7_EN, value);
        break;
    case PWR_1V3_EN:
        gpio_write(PWR_SEN_1V3_EN, value);
        break;
    case PWR_3V3A_EN:
        gpio_write(PWR_SEN_3V3A_EN, value);
        break;
    case PWR_3V6_EN:
        gpio_write(PWR_SEN_3V6_EN, value);
        break;
    case PWR_4V1_EN:
        gpio_write(PWR_SEN_4V1_EN, value);
        break;
    case PWR_N1V3A_EN:
        gpio_write(PWR_SEN_N1V3A_EN, value);
        break;
    case SPI_NCS:
        gpio_write(SEN_SPI_NCS, value);
        break;
    case SPI_CLK:
        gpio_write(SEN_SPI_CLK, value);
        break;
    case SPI_MOSI:
        gpio_write(SEN_SPI_MOSI, value);
        break;
    case SYNC_EN:
        assert(false && "SYNC_EN not implemented.");
        break;
    case FRAME_REQ:
        assert(false && "FRAME_REQ not implemented.");
        break;
    case SEN_NRESET:
        gpio_write(SEN_NRESET, value);
        break;
    default:
        break;
    }
}

#define REQ_BIT (1 << 13)

void gmax_initiate_frame(void)
{
    XGpio_DiscreteClear(&gmax_gpio, 1, REQ_BIT);
    XGpio_DiscreteSet(&gmax_gpio, 1, REQ_BIT);
}

void gmax_fpga_interface_init(void)
{
    /*
     * Initialize the GPIO driver so that it's ready to use,§
     * specify the device ID that is generated in xparameters.h
     */
    int status = XGpio_Initialize(&gmax_gpio, XPAR_SENSOR_0_AXI_GPIO_0_DEVICE_ID);
    if (status != XST_SUCCESS)
    {
        log_info(LOG_TAG, "XGpio_Initialize with code %d\n", status);
        return;
    }

    /* Set channel one to all outputs, set them to 0*/
    XGpio_SetDataDirection(&gmax_gpio, 1, 0x0);
    XGpio_DiscreteWrite(&gmax_gpio, 1, 0x0);
}

uint16_t gmax_get_training_word(const uint8_t *const gmax_config)
{
    /* Should return 0x086E for default config */
    return ((gmax_config[216] & 0x01) << 11) + (gmax_config[215] << 3) + ((gmax_config[214] & 0xE0) >> 5);
}

void gmax_sync_word_write(const uint16_t sync_word)
{
    uint32_t reg = XGpio_DiscreteRead(&gmax_gpio, 1) & 0xFFFFF000;
    reg |= sync_word & 0x0FFF;
    XGpio_DiscreteWrite(&gmax_gpio, 1, reg);
}

bool gmax_sync_complete(void)
{
    return (bool)(XGpio_DiscreteRead(&gmax_gpio, 2) & 0x1);
}

void gmax_sync_mode(const bool en)
{
    if (en == true)
    {
        XGpio_DiscreteSet(&gmax_gpio, 1, 0x00001000);
    }
    else
    {
        XGpio_DiscreteClear(&gmax_gpio, 1, 0x00001000);
    }
}