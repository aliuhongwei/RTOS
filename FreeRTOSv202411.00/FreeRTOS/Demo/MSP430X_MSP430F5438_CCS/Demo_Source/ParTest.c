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

/*-----------------------------------------------------------
 * Simple parallel port IO routines to flash LEDs.
 *-----------------------------------------------------------*/

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Hardware includes. */
#include "msp430.h"
#include "hal_MSP-EXP430F5438.h"

/*-----------------------------------------------------------*/

void vParTestInitialise( void )
{
	/* The port used by the two LEDs is configured from halBoardInit() so
	nothing needs to be done here. */
}
/*-----------------------------------------------------------*/

void vParTestSetLED( unsigned portBASE_TYPE uxLED, signed portBASE_TYPE xValue )
{
	/* Only two LEDs are provided on the hardware. */
	taskENTER_CRITICAL();
	{
		if( xValue != pdFALSE )
		{
			switch( uxLED )
			{
				case 0: LED_PORT_OUT |= LED_1;
						break;
	
				case 1: LED_PORT_OUT |= LED_2;
						break;
						
				default: /* Nothing to do here, there are only two LEDs. */
						break;
			}
		}
		else
		{
			switch( uxLED )
			{
				case 0: LED_PORT_OUT &= ~LED_1;
						break;
	
				case 1: LED_PORT_OUT &= ~LED_2;
						break;
				default: /* Nothing to do here, there are only two LEDs. */
						break;
			}
		}
	}
	taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

void vParTestToggleLED( unsigned portBASE_TYPE uxLED )
{
	taskENTER_CRITICAL();
	{
		switch( uxLED )
		{
			case 0: if( ( LED_PORT_OUT & LED_1 ) == 0 )
					{
						LED_PORT_OUT |= LED_1;
					}
					else
					{
						LED_PORT_OUT &= ~LED_1;
					}
					break;

			case 1: if( ( LED_PORT_OUT & LED_2 ) == 0 )
					{
						LED_PORT_OUT |= LED_2;
					}
					else
					{
						LED_PORT_OUT &= ~LED_2;
					}
					break;
			default: /* Nothing to do here, there are only two LEDs. */
					break;
		}
	}
	taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

