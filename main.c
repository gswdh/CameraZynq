// App headers
#include "apps.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"

// A demo task
void startup_thread(void *params)
{
	// Start all the child threads
	apps_launcher();

	// Finish up with this thread
	vTaskDelete(NULL);
}

int main()
{
	// Create a startup task to keep all execution in tasks
	xTaskCreate(startup_thread, "Startup Thread", 128, NULL, tskIDLE_PRIORITY, NULL);

	// Start and enter the scheduler
	vTaskStartScheduler();

	// This loop should never be reached
	while (1)
	{
	}

	// We should never return
	return 0;
}
