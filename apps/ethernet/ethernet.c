#include "ethernet.h"

// App configuration
#include "apps_config.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

// Driver includes
#include "rtl8211e_debug.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xemacps.h"

// Logging

// C Libs
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

// Logging meta
#define LOG_TAG "ETHERNET"

static TimerHandle_t ethernet_timer = NULL;
static TaskHandle_t ethernet_task_handle = NULL;

static XEmacPs emac = {0};

static bool ethernet_init(void)
{
	XEmacPs_Config *emac_config = XEmacPs_LookupConfig(XPAR_XEMACPS_0_DEVICE_ID);
	XEmacPs_CfgInitialize(&emac, emac_config, XPAR_XEMACPS_0_DEVICE_ID);

	// PHY reset
	XEmacPs_PhyWrite(&emac, 0x01, 0x00, 0x8000);

	xil_printf("Waiting for phy to come out of reset\r\n");

	vTaskDelay(pdMS_TO_TICKS(10000));

	uint16_t value = 0x8000;
	while (value & 0x8000)
	{
		XEmacPs_PhyRead(&emac, 0x01, 0x00, &value);
	}

	return true;
}

static void ethernet_task(void *params)
{
	uint16_t registers[32] = {0};
	for (uint32_t addr = 0; addr < 32; addr++)
	{
		XEmacPs_PhyRead(&emac, 0x01, addr, &registers[addr]);
		xil_printf("PHY REGS: reg = 0x%02x, reg value = 0x%04x\r\n", addr, registers[addr]);
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

static void ethernet_tick(TimerHandle_t timer)
{
	xTaskCreate(ethernet_task, "Ethernet Task", ETHERNET_STACK_DEPTH, NULL, ETHERNET_TASK_PRIORITY, &ethernet_task_handle);
}

void ethernet_start(void *params)
{
	// Perform the init routine
	if (ethernet_init() == true)
	{
		// Create and start the app tick timer
		ethernet_timer = xTimerCreate("Ethernet Tick", pdMS_TO_TICKS(ETHERNET_INTERVAL_MS), pdTRUE, NULL, ethernet_tick);
		xTimerStart(ethernet_timer, 0);
	}

	vTaskDelete(NULL);
}

void ethernet_stop(void)
{
	xTimerStop(ethernet_timer, 0);
	xTimerDelete(ethernet_timer, 0);

	vTaskDelete(ethernet_task_handle);
}
