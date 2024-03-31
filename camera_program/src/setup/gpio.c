#include "gpio.h"

#include "xparameters.h"
#include "xgpio.h"
#include "xil_printf.h"

/* The Instance of the GPIO Driver */
static XGpio fpga_gpio = {0};

void gpio_init()
{
	/*
	 * Initialize the GPIO driver so that it's ready to use,
	 * specify the device ID that is generated in xparameters.h
	 */
	XGpio_Config * CfgPtr = XGpio_LookupConfig(XPAR_XGPIO_0_BASEADDR);
    if(XGpio_Initialize(&fpga_gpio, XPAR_XGPIO_0_BASEADDR) != XST_SUCCESS)
    {
        xil_printf("GPIO init fail.\r\n");
        return;
    }

	XGpio_SetDataDirection(&fpga_gpio, 1, 0x0);

	XGpio_DiscreteWrite(&fpga_gpio, 1, 0x0);
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