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

/* Device specific includes. */
#include "mb96348hs.h"

/* 
 * The below define should be same as the option selected by the Memory 
 * Model (Project->Setup Project->C Compiler->Category->Target Depend ) 
 *
 * Valid settings here include:
 * ------- Memory models ---------      Data	  Code
 * portSMALL							16 Bit    16 Bit
 * portMEDIUM							16 Bit    24 Bit
 * portCOMPACT							24 Bit    16 Bit
 * portLARGE							24 Bit    24 Bit
 */
#define configMEMMODEL portMEDIUM

/* Demo specific definition - set this to 1 if you want to include the task
that writes trace and debug information to the UART.  If it is set to 0 then
the ComTest tasks will be included in place of the trace task. */
#define INCLUDE_TraceListTasks		0

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *----------------------------------------------------------*/
#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			1
#define configUSE_TICK_HOOK			0
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 180 ) /* This can be greatly reduced when using the small or medium memory model. */
#define configCPU_CLOCK_HZ			( ( unsigned long ) 56000000 )	/* Clock setup from start.asm in the demo application. */
#define configCLKP1_CLOCK_HZ		( ( unsigned long ) 56000000 )	/* Clock setup from start.asm in the demo application. */
#define configTICK_RATE_HZ			( (TickType_t) 1000 )
#define configMAX_PRIORITIES		( 6 )
#define configTOTAL_HEAP_SIZE		( (size_t) (20000) )
#define configMAX_TASK_NAME_LEN		( 20 )
#define configUSE_16_BIT_TICKS		1
#define configIDLE_SHOULD_YIELD		1
#define configUSE_MUTEXES			1
#define configUSE_TRACE_FACILITY	1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES			1
#define configMAX_CO_ROUTINE_PRIORITIES ( 4 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet			1
#define INCLUDE_uxTaskPriorityGet			1
#define INCLUDE_vTaskDelete					1
#define INCLUDE_vTaskCleanUpResources		1
#define INCLUDE_vTaskSuspend				1
#define INCLUDE_vResumeFromISR				1
#define INCLUDE_vTaskDelayUntil				1
#define INCLUDE_vTaskDelay					1
#define INCLUDE_xTaskGetSchedulerState		1
#define INCLUDE_xTaskGetCurrentTaskHandle	1

/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within 
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS	1

#define configKERNEL_INTERRUPT_PRIORITY 6

#endif /* FREERTOS_CONFIG_H */
