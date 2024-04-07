/******************************************************************************
* Copyright (c) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
#ifndef _FREERTOSCONFIG_H
#define _FREERTOSCONFIG_H


#define	configUSE_PREEMPTION			  1
#define	configIDLE_SHOULD_YIELD			  1
#define	configUSE_TIME_SLICING			  1
#define	configUSE_PORT_OPTIMIZED_TASK_SELECTION	  1
#define	configSTREAM_BUFFER			 0
#define	configMESSAGE_BUFFER			 0
#define	configSUPPORT_STATIC_ALLOCATION		 0
#define	configUSE_FREERTOS_ASSERTS		 0
#define	configUSE_MUTEXES			  1
#define	INCLUDE_xSemaphoreGetMutexHolder	  1
#define	configUSE_RECURSIVE_MUTEXES		  1
#define	configUSE_COUNTING_SEMAPHORES		  1
#define	configUSE_TRACE_FACILITY		  1
#define	configUSE_NEWLIB_REENTRANT		 0
#define	configUSE_QUEUE_SETS			  1
#define	configUSE_TASK_NOTIFICATIONS		  1
#define	configUSE_STATS_FORMATTING_FUNCTION	  1
#define	configUSE_IDLE_HOOK			 0
#define	configUSE_TICK_HOOK			 0
#define	configUSE_MALLOC_FAILED_HOOK		  1
#define	configUSE_DAEMON_TASK_STARTUP_HOOK	 0
#define	configUSE_TIMERS			  1
#define	FREERTOS_TIMER_TICK_TRACE		 0

#define	configTICK_RATE_HZ			(100)
#define	configMAX_API_CALL_INTERRUPT_PRIORITY	18
#define	configMAX_PRIORITIES			(8)
#define	configMINIMAL_STACK_SIZE		((unsigned short) 200)
#define	configTOTAL_HEAP_SIZE			((size_t)65536)
#define	configMAX_TASK_NAME_LEN			10
#define	configQUEUE_REGISTRY_SIZE		10
#define	configCHECK_FOR_STACK_OVERFLOW		2
#define	configNUM_THREAD_LOCAL_STORAGE_POINTERS	0x0
#define	configUSE_TASK_FPU_SUPPORT		0x1
#define	configTIMER_TASK_PRIORITY		(configMAX_PRIORITIES-1)
#define	configTIMER_QUEUE_LENGTH		10
#define	configTIMER_TASK_STACK_DEPTH		((configMINIMAL_STACK_SIZE * 2))
#define	configGENERATE_RUN_TIME_STATS		0x0
#define	configMAX_CO_ROUTINE_PRIORITIES		2
#define	configTIMER_BASEADDR			0xf8001000
#define	configTIMER_SELECT_CNTR			0x0
#define	configUNIQUE_INTERRUPT_PRIORITIES	32
#define	portPOINTER_SIZE_TYPE			uint32_t
#define	configUSE_16_BIT_TICKS			0x0
#define	configUSE_APPLICATION_TASK_TAG		0x0
#define	configUSE_CO_ROUTINES			0x0
#define	configUSE_TICKLESS_IDLE			0x0
#define	INCLUDE_vTaskPrioritySet		1
#define	INCLUDE_uxTaskPriorityGet		1
#define	INCLUDE_vTaskDelete			1
#define	INCLUDE_vTaskCleanUpResources		1
#define	INCLUDE_vTaskSuspend			1
#define	INCLUDE_vTaskDelayUntil			1
#define	INCLUDE_vTaskDelay			1
#define	INCLUDE_eTaskGetState			1
#define	INCLUDE_xTimerPendFunctionCall		1
#define	INCLUDE_pcTaskGetTaskName		1
#define	portTICK_TYPE_IS_ATOMIC			0x1
#define	configTASK_RETURN_ADDRESS		NULL
#define	configMESSAGE_BUFFER_LENGTH_TYPE	uint32_t
#define	configSTACK_DEPTH_TYPE			uint32_t
#define	configINTERRUPT_CONTROLLER_BASE_ADDRESS	0xf8f01000
#define	configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET (-0xf00)

#define configASSERT( x ) if( ( x ) == 0 ) vApplicationAssert( __FILE__, __LINE__ )

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()

#define portGET_RUN_TIME_COUNTER_VALUE()

void vApplicationAssert( const char *pcFile, uint32_t ulLine );
void FreeRTOS_SetupTickInterrupt(void);
#define configSETUP_TICK_INTERRUPT() FreeRTOS_SetupTickInterrupt()




#define portSET_INTERRUPT_MASK_FROM_ISR() ulPortSetInterruptMask()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x) vPortClearInterruptMask(x)


#endif /* _FREERTOSCONFIG_H */
