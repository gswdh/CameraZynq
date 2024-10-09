// App headers
#include "apps.h"

#include "git_details.h"

// Drivers
#include "gpio.h"
#include "spi.h"
#include "uart.h"
#include "i2c.h"
#include "log.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"

#define I2C_CLK_FREQ_HZ (100000)

#define LOG_TAG "MAIN"

// A demo task
void startup_thread(void *params)
{
	vTaskDelay(pdMS_TO_TICKS(100));

	// Init the HW
	gpio_init();
	spi_init();
	uart_init();
	i2c_init(I2C_CLK_FREQ_HZ);

	log_info(LOG_TAG, "git commit on %s %s %s\n", GIT_COMMIT_TIME, GIT_BRANCH, GIT_TAG);
	log_info(LOG_TAG, "Built by %s on %s at %s\n", USER, HOSTNAME, BUILD_TIME);

	// Start all the child threads
	apps_launcher();

	// Finish up with this thread
	vTaskDelete(NULL);
}

int main()
{
	// Create a startup task to keep all execution in tasks
	xTaskCreate(startup_thread, "Startup Thread", 4096, NULL, tskIDLE_PRIORITY, NULL);

	// Start and enter the scheduler
	vTaskStartScheduler();

	// This loop should never be reached
	while (1)
	{
	}

	// We should never return
	return 0;
}
