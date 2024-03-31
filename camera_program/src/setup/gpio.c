#include "gpio.h"

#include "xparameters.h"
#include "xgpio.h"

/* The Instance of the GPIO Driver */
XGpio fpga_gpio;

void gpio_init()
{
    XGpio_Initialize(&fpga_gpio, XPAR_XGPIO_0_BASEADDR);
    XGpio_SetDataDirection(&fpga_gpio, 1, 0x00000000);
}

void gpio_write(gpio_pin_t pin, bool level)
{
    if(level)
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
    return (bool)(XGpio_DiscreteRead(&fpga_gpio, 1) & pin);
}

void gpio_set(gpio_pin_t pin)
{
    XGpio_DiscreteSet(&fpga_gpio, 1, pin);
}

void gpio_reset(gpio_pin_t pin)
{
    XGpio_DiscreteClear(&fpga_gpio, 1, pin);
}

void gpio_toggle(gpio_pin_t pin)
{
    gpio_write(pin, !gpio_read(pin));
}