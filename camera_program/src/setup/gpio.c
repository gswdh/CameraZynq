#include "gpio.h"

#include "xparameters.h"
#include "xgpio.h"

#include "log.h"

#define LOG_TAG "GPIO"

/* The Instance of the GPIO Driver */
static XGpio fpga_gpio = {0};

void gpio_init()
{
    /*
     * Initialize the GPIO driver so that it's ready to use,
     * specify the device ID that is generated in xparameters.h
     */
    XGpio_Config *CfgPtr = XGpio_LookupConfig(XPAR_XGPIO_0_BASEADDR);
    if (XGpio_Initialize(&fpga_gpio, XPAR_XGPIO_0_BASEADDR) != XST_SUCCESS)
    {
        log_info(LOG_TAG, "Init fail.\n");
        return;
    }

    XGpio_SetDataDirection(&fpga_gpio, 1, 0x0);

    XGpio_DiscreteWrite(&fpga_gpio, 1, 0x0);
}

void gpio_write(gpio_pin_t pin, bool level)
{
    if (level)
    {
        gpio_set(pin);
    }
    else
    {
        gpio_reset(pin);
    }
}

bool gpio_read(gpio_pin_t pin)
{
    uint32_t channel = (pin / 32) + 1;
    uint32_t mask = 1 << (pin % 32);
    return (bool)(XGpio_DiscreteRead(&fpga_gpio, channel) & mask);
}

void gpio_set(gpio_pin_t pin)
{
    uint32_t channel = (pin / 32) + 1;
    uint32_t mask = 1 << (pin % 32);
    XGpio_DiscreteSet(&fpga_gpio, channel, mask);
}

void gpio_reset(gpio_pin_t pin)
{
    uint32_t channel = (pin / 32) + 1;
    uint32_t mask = 1 << (pin % 32);
    XGpio_DiscreteClear(&fpga_gpio, channel, mask);
}

void gpio_toggle(gpio_pin_t pin)
{
    gpio_write(pin, !gpio_read(pin));
}