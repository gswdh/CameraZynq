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

/* External libs */
#include "log.h"

/* Program tasks */
#include "system.h"
#include "shutter_button.h"
#include "heartbeat.h"
#include "buttons.h"
#include "display.h"
#include "sensor.h"

static void init(void)
{
	/* Init the peripherals */
	gpio_init();
	uart_init();
	spi_init();
	usb_init();

	/* Start program tasks */
	heartbeat_start();
	shutter_button_start();
	buttons_start();
	display_start();
	sensor_start();

	/* The main event */
	system_start();

	vTaskDelete(NULL);
}

int main(void)
{
	xTaskCreate(init, "Init task", 1024, NULL, tskIDLE_PRIORITY, NULL);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for (;;)
	{
	}

	return -1;
}
