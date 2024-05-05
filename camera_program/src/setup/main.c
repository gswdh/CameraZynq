/* Xilinx includes. */
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
#include "i2c.h"

/* External libs */
#include "log.h"

static void main_init(void)
{
	/* Init the peripherals */
	gpio_init();
	uart_init();
	spi_init();
	usb_init();
	i2c_init();

	/* The main event */
	system_start();

	vTaskDelete(NULL);
}

int main(void)
{
	xTaskCreate(main_init, "Init task", 1024, NULL, tskIDLE_PRIORITY, NULL);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for (;;)
	{
	}

	return -1;
}
