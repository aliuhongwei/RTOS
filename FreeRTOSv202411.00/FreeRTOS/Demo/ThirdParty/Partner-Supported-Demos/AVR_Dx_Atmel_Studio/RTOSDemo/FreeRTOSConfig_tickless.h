/*
 * FreeRTOS Kernel V10.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_TICKLESS_H
#define FREERTOS_CONFIG_TICKLESS_H


/* The configUSE_TICKLESS_IDLE setting is used to enable low power support in FreeRTOS */
#ifdef configUSE_TICKLESS_IDLE
#undef configUSE_TICKLESS_IDLE
#endif
#define configUSE_TICKLESS_IDLE 1

#ifdef configEXPECTED_IDLE_TIME_BEFORE_SLEEP
#undef configEXPECTED_IDLE_TIME_BEFORE_SLEEP
#endif
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP 40

#ifdef configMINIMAL_STACK_SIZE
#undef configMINIMAL_STACK_SIZE
#endif
#define configMINIMAL_STACK_SIZE 100

#ifdef configTOTAL_HEAP_SIZE
#undef configTOTAL_HEAP_SIZE
#endif
#define configTOTAL_HEAP_SIZE 0x0800

#ifdef INCLUDE_vTaskDelay
#undef INCLUDE_vTaskDelay
#endif
#define INCLUDE_vTaskDelay 1

#ifdef INCLUDE_vTaskSuspend
#undef INCLUDE_vTaskSuspend
#endif
#define INCLUDE_vTaskSuspend 1

#endif /* FREERTOS_CONFIG_TICKLESS_H */