/*
 * FreeRTOS V202411.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* 
 * The following #error directive is to remind users that a batch file must be
 * executed prior to this project being built.  Once it has been executed 
 * remove the #error line below.
 */
#error Ensure CreateProjectDirectoryStructure.bat has been executed before building.  See comment immediately above.


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1
#define configUSE_IDLE_HOOK			  			1
#define configUSE_TICK_HOOK			  			1
#define configUSE_TRACE_FACILITY	  			0
#define configUSE_16_BIT_TICKS		  			0
#define configCPU_CLOCK_HZ			  			( ( unsigned long ) 50000000 ) /* Timer clock. */
#define configTICK_RATE_HZ			  			( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES		  			( 8 )
#define configMINIMAL_STACK_SIZE	  			( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE		  			( ( size_t ) 32768 )
#define configMAX_TASK_NAME_LEN		  			( 16 )
#define configIDLE_SHOULD_YIELD		  			1
#define configGENERATE_RUN_TIME_STATS 			0
#define configUSE_MALLOC_FAILED_HOOK  			1

#define configCHECK_FOR_STACK_OVERFLOW 			2

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 					0
#define configMAX_CO_ROUTINE_PRIORITIES 		( 2 )

/* Mutexes */
#define configUSE_MUTEXES			   			1
#define configUSE_RECURSIVE_MUTEXES	 			1

/* Semaphores */
#define configUSE_COUNTING_SEMAPHORES   		1

/* Timers */
#define configUSE_TIMERS						1
#define configTIMER_TASK_PRIORITY				( 2 )
#define configTIMER_QUEUE_LENGTH				10
#define configTIMER_TASK_STACK_DEPTH			( 128 )

/* Set the following definitions to 1 to include the API function, or zero to exclude the API function. */
#define INCLUDE_vTaskPrioritySet				1
#define INCLUDE_uxTaskPriorityGet				1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskCleanUpResources			0
#define INCLUDE_vTaskSuspend				 	1
#define INCLUDE_xTaskResumeFromISR			  	1
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_xTaskGetSchedulerState		  	1
#define INCLUDE_uxTaskGetStackHighWaterMark 	1

#define configASSERT( x ) if( ( x ) == pdFALSE ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

#endif /* FREERTOS_CONFIG_H */
