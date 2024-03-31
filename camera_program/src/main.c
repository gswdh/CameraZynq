/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/* Xilinx includes. */
#include "xil_printf.h"
#include "xparameters.h"

static void timer_heartbeat_cb(TimerHandle_t pxTimer)
{
	(void)pxTimer;
	xil_printf("Camera heartbeat. Tick = %ums.\r\n", xTaskGetTickCount());
}

int main(void)
{
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
