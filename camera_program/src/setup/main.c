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

static void timer_heartbeat_cb(TimerHandle_t pxTimer)
{
	(void)pxTimer;
	xil_printf("Camera heartbeat. Tick = %ums.\r\n", xTaskGetTickCount());

	// Flash the LED
	gpio_toggle(FPGA_LED_0);

	// Send some dummy data to the PMC
	char *msg = "somedata\n";
	uart_tx((uint8_t *)msg, (uint32_t)strlen(msg));
}

int main(void)
{
	gpio_init();
	uart_init();

	usb_init();

	TimerHandle_t timer_heartbeat = xTimerCreate((const char *)"Heartbeat Timer",
												 pdMS_TO_TICKS(1000),
												 pdTRUE,
												 NULL,
												 timer_heartbeat_cb);

	xTimerStart(timer_heartbeat, 0);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for (;;)
	{
	}

	return -1;
}
