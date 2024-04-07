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

int main(void)
{
	gpio_init();
	uart_init();
	spi_init();
	// usb_init();

	/* Simple blink to show we're alive */
	heartbeat_start();

	/* Start program tasks */
	shutter_button_start();

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for (;;)
	{
	}

	return -1;
}
