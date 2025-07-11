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

#define configUSE_PREEMPTION                       1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    0
#define configUSE_IDLE_HOOK                        1
#define configUSE_TICK_HOOK                        1
#define configUSE_DAEMON_TASK_STARTUP_HOOK         1
#define configTICK_RATE_HZ                         ( 1000 )                  /* In this non-real time simulated environment the tick frequency has to be at least a multiple of the Win32 tick frequency, and therefore very slow. */
#define configMINIMAL_STACK_SIZE                   ( PTHREAD_STACK_MIN ) /* The stack size being passed is equal to the minimum stack size needed by pthread_create(). */
#define configTOTAL_HEAP_SIZE                      ( ( size_t ) ( 65 * 1024 ) )
#define configMAX_TASK_NAME_LEN                    ( 12 )
#define configUSE_TRACE_FACILITY                   1
#define configUSE_16_BIT_TICKS                     0
#define configIDLE_SHOULD_YIELD                    1
#define configUSE_MUTEXES                          1
#define configCHECK_FOR_STACK_OVERFLOW             0
#define configUSE_RECURSIVE_MUTEXES                1
#define configQUEUE_REGISTRY_SIZE                  20
#define configUSE_APPLICATION_TASK_TAG             1
#define configUSE_COUNTING_SEMAPHORES              1
#define configUSE_ALTERNATIVE_API                  0
#define configUSE_QUEUE_SETS                       1
#define configUSE_TASK_NOTIFICATIONS               1

/* The following 2  memory allocation schemes are possible for this demo:
 *
 * 1. Dynamic Only.
 *    #define configSUPPORT_STATIC_ALLOCATION  0
 *    #define configSUPPORT_DYNAMIC_ALLOCATION 1
 *
 * 2. Static and Dynamic.
 *    #define configSUPPORT_STATIC_ALLOCATION  1
 *    #define configSUPPORT_DYNAMIC_ALLOCATION 1
 *
 * Static only configuration is not possible for this demo as it utilizes
 * dynamic allocation.
 */
#define configSUPPORT_STATIC_ALLOCATION            1
#define configSUPPORT_DYNAMIC_ALLOCATION           1

#define configRECORD_STACK_HIGH_ADDRESS            1

/* Software timer related configuration options.  The maximum possible task
 * priority is configMAX_PRIORITIES - 1.  The priority of the timer task is
 * deliberately set higher to ensure it is correctly capped back to
 * configMAX_PRIORITIES - 1. */
#define configUSE_TIMERS                           1
#define configTIMER_TASK_PRIORITY                  ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH                   20
#define configTIMER_TASK_STACK_DEPTH               ( configMINIMAL_STACK_SIZE * 2 )

#define configMAX_PRIORITIES                       ( 7 )

/* Run time stats gathering configuration options. */
unsigned long ulGetRunTimeCounterValue( void ); /* Prototype of function that returns run time counter. */
void vConfigureTimerForRunTimeStats( void );    /* Prototype of function that initialises the run time counter. */
#define configGENERATE_RUN_TIME_STATS             1

/* Co-routine related configuration options. */
#define configUSE_CO_ROUTINES                     0
#define configMAX_CO_ROUTINE_PRIORITIES           ( 2 )

/* This demo can use of one or more example stats formatting functions.  These
 * format the raw data provided by the uxTaskGetSystemState() function in to human
 * readable ASCII form.  See the notes in the implementation of vTaskList() within
 * FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS      0

/* Enables the test whereby a stack larger than the total heap size is
 * requested. */
#define configSTACK_DEPTH_TYPE                    uint32_t

/* Set the following definitions to 1 to include the API function, or zero
 * to exclude the API function.  In most cases the linker will remove unused
 * functions anyway. */
#define INCLUDE_vTaskPrioritySet                  1
#define INCLUDE_uxTaskPriorityGet                 1
#define INCLUDE_vTaskDelete                       1
#define INCLUDE_vTaskCleanUpResources             0
#define INCLUDE_vTaskSuspend                      1
#define INCLUDE_vTaskDelayUntil                   1
#define INCLUDE_vTaskDelay                        1
#define INCLUDE_uxTaskGetStackHighWaterMark       1
#define INCLUDE_uxTaskGetStackHighWaterMark2      1
#define INCLUDE_xTaskGetSchedulerState            1
#define INCLUDE_xTimerGetTimerDaemonTaskHandle    1
#define INCLUDE_xTaskGetIdleTaskHandle            1
#define INCLUDE_xTaskGetHandle                    1
#define INCLUDE_eTaskGetState                     1
#define INCLUDE_xSemaphoreGetMutexHolder          1
#define INCLUDE_xTimerPendFunctionCall            1
#define INCLUDE_xTaskAbortDelay                   1

#define configINCLUDE_MESSAGE_BUFFER_AMP_DEMO     0
#if ( configINCLUDE_MESSAGE_BUFFER_AMP_DEMO == 1 )
    extern void vGenerateCoreBInterrupt( void * xUpdatedMessageBuffer );
    #define sbSEND_COMPLETED( pxStreamBuffer )    vGenerateCoreBInterrupt( pxStreamBuffer )
#endif /* configINCLUDE_MESSAGE_BUFFER_AMP_DEMO */

extern void vAssertCalled( const char * const pcFileName,
                           unsigned long ulLine );

/* projCOVERAGE_TEST should be defined on the command line so this file can be
 * used with multiple project configurations.  If it is
 */
#ifndef projCOVERAGE_TEST
    #error projCOVERAGE_TEST should be defined to 1 or 0 on the command line.
#endif

#ifndef projENABLE_TRACING
    #error projENABLE_TRACING should be defined to 1 or 0 on the command line.
#endif

#if ( projCOVERAGE_TEST == 1 )

/* Insert NOPs in empty decision paths to ensure both true and false paths
 * are being tested. */
    #define mtCOVERAGE_TEST_MARKER()    __asm volatile ( "NOP" )

/* Ensure the tick count overflows during the coverage test. */
    #define configINITIAL_TICK_COUNT        0xffffd800UL

/* Allows tests of trying to allocate more than the heap has free. */
    #define configUSE_MALLOC_FAILED_HOOK    0

/* To test builds that remove the static qualifier for debug builds. */
    #define portREMOVE_STATIC_QUALIFIER
#else /* if ( projCOVERAGE_TEST == 1 ) */

/* It is a good idea to define configASSERT() while developing.  configASSERT()
 * uses the same semantics as the standard C assert() macro.  Don't define
 * configASSERT() when performing code coverage tests though, as it is not
 * intended to asserts() to fail, some some code is intended not to run if no
 * errors are present. */
    #define configASSERT( x )    if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )

    #define configUSE_MALLOC_FAILED_HOOK    1

/* Include the FreeRTOS+Trace FreeRTOS trace macro definitions. */
    #if( projENABLE_TRACING == 1 )
        #include "trcRecorder.h"
    #endif /* if ( projENABLE_TRACING == 1 ) */
#endif /* if ( projCOVERAGE_TEST == 1 ) */

/* networking definitions */
#define configMAC_ISR_SIMULATOR_PRIORITY    ( configMAX_PRIORITIES - 1 )

/* Prototype for the function used to print out.  In this case it prints to the
 * console before the network is connected then a UDP port after the network has
 * connected. */
extern void vLoggingPrintf( const char * pcFormatString,
                            ... );

/* Set to 1 to print out debug messages.  If ipconfigHAS_DEBUG_PRINTF is set to
 * 1 then FreeRTOS_debug_printf should be defined to the function used to print
 * out the debugging messages. */
#define ipconfigHAS_DEBUG_PRINTF    1
#if ( ipconfigHAS_DEBUG_PRINTF == 1 )
    #define FreeRTOS_debug_printf( X )    vLoggingPrintf X
#endif

/* Set to 1 to print out non debugging messages, for example the output of the
 * FreeRTOS_netstat() command, and ping replies.  If ipconfigHAS_PRINTF is set to 1
 * then FreeRTOS_printf should be set to the function used to print out the
 * messages. */
#define ipconfigHAS_PRINTF    0
#if ( ipconfigHAS_PRINTF == 1 )
    #define FreeRTOS_printf( X )    vLoggingPrintf X
#endif
#endif /* FREERTOS_CONFIG_H */
