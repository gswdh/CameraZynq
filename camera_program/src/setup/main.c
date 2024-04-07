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

#include "xemacps.h"
#include "rtl8211e_debug.h"

static void to_binary16(uint16_t number, char *output)
{
	int j = 0; // Output array index
	for (int i = 15; i >= 0; i--)
	{
		uint16_t bit = (number >> i) & 1;
		output[j++] = bit + '0'; // Convert bit to character and store in output
		if (i % 4 == 0 && i != 0)
		{ // Add a space after every 4 bits, except at the end
			output[j++] = ' ';
		}
	}
	output[j] = '\0'; // Null terminator
}

static void timer_heartbeat_cb(TimerHandle_t pxTimer)
{
	(void)pxTimer;

	// Flash the LED
	gpio_toggle(FPGA_LED_0);

	// Send some dummy data to the PMC
	char *msg = "somedata\n";
	uart_tx((uint8_t *)msg, (uint32_t)strlen(msg));
}

static void eth_task(void *params)
{

	XEmacPs_Config *emac_config = XEmacPs_LookupConfig(XPAR_XEMACPS_0_BASEADDR);
	XEmacPs emac = {0};
	XEmacPs_CfgInitialize(&emac, emac_config, XPAR_XEMACPS_0_BASEADDR);

	// PHY reset
	XEmacPs_PhyWrite(&emac, 0x01, 0x00, 0x8000);

	xil_printf("Waiting for phy to come out of reset\r\n");

	vTaskDelay(pdMS_TO_TICKS(10000));

	uint16_t value = 0x8000;
	while (value & 0x8000)
	{
		XEmacPs_PhyRead(&emac, 0x01, 0x00, &value);
	}

	xil_printf("Waiting for auto negotiation\r\n");

	value = 0x0000;
	uint32_t attempts = 0;
	while (true)
	{
		XEmacPs_PhyRead(&emac, 0x01, 0x13, &value);

		if (value & (1 << 11))
		{
			xil_printf("Auto negotiation complete! Register = 0x%04x. attempts = %u\r\n", value, attempts);
			break;
		}

		attempts++;
		if (attempts == 10)
		{
			xil_printf("Auto negotiation failed\r\n");
			break;
		}
		vTaskDelay(pdMS_TO_TICKS(3000));
	}

	xil_printf("\r\n\r\n");

	char bin_num[21] = {0};
	uint16_t registers[32] = {0};
	for (uint32_t addr = 0; addr < 32; addr++)
	{
		XEmacPs_PhyRead(&emac, 0x01, addr, &registers[addr]);
		to_binary16(registers[addr], bin_num);
		xil_printf("PHY REGS: reg = 0x%02x, reg value = 0x%04x or %s\r\n", addr, registers[addr], bin_num);
	}

	xil_printf("\r\n\r\n");

	printBMCR(registers[0]);   // Register 0x00
	printBMSR(registers[1]);   // Register 0x01
	printPHYID1(registers[2]); // Register 0x02
	printPHYID2(registers[3]); // Register 0x03
	printANAR(registers[4]);   // Register 0x04
	printANLPAR(registers[5]); // Register 0x05
	printANER(registers[6]);   // Skipping to 0x06 as per request
	printANNPTR(registers[7]); // 0x07
	printANNPRR(registers[8]); // 0x08
	printINSR(registers[19]);

	xil_printf("\r\n\r\n");
	vTaskDelete(NULL);
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

	xTaskCreate(eth_task, "eth_task", 4096, NULL, tskIDLE_PRIORITY, NULL);

	/* Start program tasks */
	shutter_button_start();

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for (;;)
	{
	}

	return -1;
}
