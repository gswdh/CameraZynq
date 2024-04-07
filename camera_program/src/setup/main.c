/* Xilinx includes. */
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Peripheral drivers */
#include "gpio.h"
#include "uart.h"
#include "usb.h"
#include "spi.h"

/* Program tasks */
#include "shutter_button.h"
#include "heartbeat.h"
#include "buttons.h"
#include "display.h"

int main(void)
{
	/* Init the peripherals */
	gpio_init();
	uart_init();
	spi_init();
	// usb_init();

	/* Start program tasks */
	heartbeat_start();
	shutter_button_start();
	buttons_start();
	display_start();

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for (;;)
	{
	}

	return -1;
}
