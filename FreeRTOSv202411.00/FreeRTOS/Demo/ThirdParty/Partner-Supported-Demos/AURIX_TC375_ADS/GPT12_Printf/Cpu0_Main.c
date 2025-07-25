/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2023
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 * 
 * SPDX-License-Identifier: BSL-1.0
 *********************************************************************************************************************/
 /*\title TC375 Basic FreeRTOS interrupt usage example
 * \abstract This example shows how to get started with using the AURIX(TM) FreeRTOS port
 * \description This code example creates a timer interrupt (GPT12) which in turn notifies a task every 500ms, the
 *              notified task then prints a message to the serial port when it gets notified. Another task toggles LED1
 *              every 250ms; it also polls the BUTTON1 and toggles LED2 every times BUTTON1 is pressed.
 *
 * \name iLLD_TC375_ADS_Timer_Interrupt
 * \version V1.0.0
 * \board AURIX TC375 lite Kit, KIT_A2G_TC375_LITE, TC37xTP_A-Step
 * \keywords AURIX, TC3XX, TC375, FreeRTOS, Blinky, Task, LED, Button, GPT12, Timer, Interrupt
 * \documents See README.md
 * \lastUpdated 2023-11-07
 *********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "serialio.h"

/* Scheduler includes */
#include "FreeRTOS.h"
#include "task.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
/* ASCLIN0 module and UART TX/RX pin selection */
SERIALIO_t SERIALIO =
{
  .asclin = &MODULE_ASCLIN0,
  .tx_pin = &IfxAsclin0_TX_P14_0_OUT,
  .rx_pin = &IfxAsclin0_RXA_P14_1_IN
};

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void task_print(void *arg);
void task_blinky(void *arg);

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
void core0_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    /* Setup serial port to allow printf(...) usage */
    SERIALIO_Init(115200);

    /* Create the print task */
    xTaskCreate(task_print, "PRINT", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

    /* Create the blinky task */
    xTaskCreate(task_blinky, "BLINKY", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

    /* Start the scheduler (this function will never return) */
    vTaskStartScheduler();
}

/* Required FreeRTOS callback, called in case of a stack overflow.
 * For the sake of simplicity, this function will loop indefinitely
 * and the root cause can be confirmed by using a debugger
 */
void vApplicationStackOverflowHook (TaskHandle_t xTask, char *pcTaskName)
{
}
