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


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.  See
 * https://www.FreeRTOS.org/a00110.html
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1
#define configUSE_IDLE_HOOK						1
#define configUSE_TICK_HOOK						1
#define configUSE_DAEMON_TASK_STARTUP_HOOK		1
#define configTICK_RATE_HZ						( 1000 ) /* In this non-real time simulated environment the tick frequency has to be at least a multiple of the Win32 tick frequency, and therefore very slow. */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 70 ) /* In this simulated case, the stack only has to hold one small structure as the real stack is part of the win32 thread. */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 490 * 1024 ) ) /* This demo tests heap_5 so places multiple blocks within this total heap size.  See mainREGION_1_SIZE to mainREGION_3_SIZE definitions in main.c. */
#define configMAX_TASK_NAME_LEN					( 12 )
#define configUSE_TRACE_FACILITY				1
#define configIDLE_SHOULD_YIELD					1
#define configUSE_MUTEXES						1
#define configCHECK_FOR_STACK_OVERFLOW			0
#define configUSE_RECURSIVE_MUTEXES				1
#define configQUEUE_REGISTRY_SIZE				20
#define configUSE_MALLOC_FAILED_HOOK			1
#define configUSE_APPLICATION_TASK_TAG			1
#define configUSE_COUNTING_SEMAPHORES			1
#define configUSE_ALTERNATIVE_API				0
#define configUSE_QUEUE_SETS					1
#define configUSE_TASK_NOTIFICATIONS			1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES		5
#define configSUPPORT_STATIC_ALLOCATION			1
#define configINITIAL_TICK_COUNT				( ( TickType_t ) 0 ) /* For test. */
#define configSTREAM_BUFFER_TRIGGER_LEVEL_TEST_MARGIN 1 /* As there are a lot of tasks running. */

 /* Tick type width is defined based on the target platform(32bit or 64bit). */
#ifdef _M_X64
    #define configTICK_TYPE_WIDTH_IN_BITS		TICK_TYPE_WIDTH_64_BITS
#else
    #define configTICK_TYPE_WIDTH_IN_BITS		TICK_TYPE_WIDTH_32_BITS
#endif

/* Software timer related configuration options. */
#define configUSE_TIMERS						1
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH				20
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 )

#define configMAX_PRIORITIES					( 7 )

/* Run time stats gathering configuration options. */
#define configRUN_TIME_COUNTER_TYPE				uint64_t
configRUN_TIME_COUNTER_TYPE ulGetRunTimeCounterValue( void ); /* Prototype of function that returns run time counter. */
void vConfigureTimerForRunTimeStats( void );	/* Prototype of function that initialises the run time counter. */
#define configGENERATE_RUN_TIME_STATS			1
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() ulGetRunTimeCounterValue()

/* Co-routine related configuration options. */
#define configUSE_CO_ROUTINES 					1
#define configMAX_CO_ROUTINE_PRIORITIES			( 2 )

/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS	1

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function.  In most cases the linker will remove unused
functions anyway. */
#define INCLUDE_vTaskPrioritySet				1
#define INCLUDE_uxTaskPriorityGet				1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskCleanUpResources			0
#define INCLUDE_vTaskSuspend					1
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_uxTaskGetStackHighWaterMark		1
#define INCLUDE_xTaskGetSchedulerState			1
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1
#define INCLUDE_xTaskGetIdleTaskHandle			1
#define INCLUDE_xTaskGetHandle					1
#define INCLUDE_eTaskGetState					1
#define INCLUDE_xSemaphoreGetMutexHolder		1
#define INCLUDE_xTimerPendFunctionCall			1
#define INCLUDE_xTaskAbortDelay					1

/* The Win32 target is capable of running all the tests tasks at the same
 * time. */
#define configRUN_ADDITIONAL_TESTS				1

/* It is a good idea to define configASSERT() while developing.  configASSERT()
uses the same semantics as the standard C assert() macro. */
extern void vAssertCalled( unsigned long ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#define configINCLUDE_MESSAGE_BUFFER_AMP_DEMO	0
#if ( configINCLUDE_MESSAGE_BUFFER_AMP_DEMO == 1 )
	extern void vGenerateCoreBInterrupt( void * xUpdatedMessageBuffer );
	#define sbSEND_COMPLETED( pxStreamBuffer ) vGenerateCoreBInterrupt( pxStreamBuffer )
#endif /* configINCLUDE_MESSAGE_BUFFER_AMP_DEMO */

#ifdef WIN32_LEAN_AND_MEAN
    #include "winsock2.h"
#else
    #include <winsock.h>
#endif /* WIN32_LEAN_AND_MEAN */

/* Include the FreeRTOS+Trace FreeRTOS trace macro definitions. */
#include "trcRecorder.h"

#endif /* FREERTOS_CONFIG_H */
