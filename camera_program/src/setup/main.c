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

// #include "xemacps.h"

// static void to_binary16(uint16_t number, char *output)
// {
// 	int j = 0; // Output array index
// 	for (int i = 15; i >= 0; i--)
// 	{
// 		uint16_t bit = (number >> i) & 1;
// 		output[j++] = bit + '0'; // Convert bit to character and store in output
// 		if (i % 4 == 0 && i != 0)
// 		{ // Add a space after every 4 bits, except at the end
// 			output[j++] = ' ';
// 		}
// 	}
// 	output[j] = '\0'; // Null terminator
// }

static void timer_heartbeat_cb(TimerHandle_t pxTimer)
{
	(void)pxTimer;

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
	spi_init();

	// usb_init();

	TimerHandle_t timer_heartbeat = xTimerCreate((const char *)"Heartbeat Timer",
												 pdMS_TO_TICKS(1000),
												 pdTRUE,
												 NULL,
												 timer_heartbeat_cb);
	xTimerStart(timer_heartbeat, 0);

	// XEmacPs_Config *emac_config = XEmacPs_LookupConfig(XPAR_XEMACPS_0_BASEADDR);
	// XEmacPs emac = {0};
	// XEmacPs_CfgInitialize(&emac, emac_config, XPAR_XEMACPS_0_BASEADDR);

	// xil_printf("\r\n\r\n");

	// char bin_num[21] = {0};
	// for (uint32_t addr = 0; addr < 32; addr++)
	// {
	// 	uint16_t data = 0;
	// 	XEmacPs_PhyRead(&emac, 0x01, addr, &data);
	// 	to_binary16(data, bin_num);
	// 	xil_printf("PHY REGS: reg = 0x%02x, reg value = 0x%04x or %s\r\n", addr, data, bin_num);
	// }

	// xil_printf("\r\n\r\n");

	/* Start program tasks */
	shutter_button_start();

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for (;;)
	{
	}

	return -1;
}
