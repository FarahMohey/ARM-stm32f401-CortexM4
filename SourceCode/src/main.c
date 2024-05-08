/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"
#include "MCAL/RCC.h"
#include "MCAL/GPIO.h"
#include "HAL/LED.h"
#include "MCAL/STK.h"


// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace-impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"








void ToggleLEd(void)
{
	/* Static variables to keep track of counter and LED status *
	static u32 COUNTER = 0 ;
	static u32 status = LED_ON ;
	/* Increment the counter */
	//COUNTER++;
	/* Check if the counter reaches 1000 milliseconds *
	if ((COUNTER % 1000) ==0)
	{
		/* Toggle the LED status *
		status ^= (LED_ON | LED_OFF);
	}
	/* Set the LED status */
//e	LED_Set_Status(Led_Red , LED_ON);
}


int main(int argc, char* argv[])
{
	/*
	RCC_SET_Clock_ON(CLK_HSE);
	RCC_Select_SysClk(SYSCLK_HSE);
	RCC_Read_SysClk();

	RCC_READ_ClockReadyState(READY_CLK_HSE);

	RCC_Config_PLLSrc(PLL_SRC_HSE);
	RCC_Config_AHB_BusPrescaler(AHB_4);
	RCC_Enable_AHB1_Peripheral(AHB1_GPIOA);
	RCC_Enable_APB1_Peripheral(APB1_USART2);
	RCC_Config_APBH_BusPrescaler(APB_H_2);
	RCC_Config_APBH_BusPrescaler(APB_H_4);

	 */


	/* LED TEST
	RCC_Select_SysClk(SYSCLK_HSI);
	RCC_Config_AHB_BusPrescaler(AHB_1);

	RCC_Enable_AHB1_Peripheral(AHB1_GPIOA);

	LED_Init();

    LED_Set_Status(Led_Yellow,LED_ON);
    LED_Set_Status(Led_Green,LED_ON);
    LED_Set_Status(Led_Red,LED_OFF);

	 */


	/*
	 * @brief   : ToggleLED function for SysTick test.
	 * @details : This function toggles the LED status every 1000 milliseconds.
	 */


	RCC_Select_SysClk(SYSCLK_HSI);
	RCC_Config_AHB_BusPrescaler(AHB_1);

	RCC_Enable_AHB1_Peripheral(AHB1_GPIOA);
	RCC_Enable_AHB1_Peripheral(AHB1_GPIOB);
	RCC_Enable_AHB1_Peripheral(AHB1_GPIOC);

	LED_Init();
/*
	STK_SetConfig(STK_AHB_8_ENB_INT);
	STK_SetCallBack(ToggleLEd);
	STK_SetTimeMs(5000);
	STK_Start();
*/
	// STK_SetCallBack(ToggleLEd);

//STK_GET_CurrentVal( ptr );

//	LED_Set_Status(Led_Red , LED_ON);
//LED_Set_Status(Led_Yellow, LED_ON);


	// Infinite loop
	while (1)
	{


	}

	return 0;

}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
