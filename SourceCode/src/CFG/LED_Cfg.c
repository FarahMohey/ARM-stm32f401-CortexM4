/*
 ============================================================================
 Name        : LED_Cfg.c
 Author      : Farah Mohey
 Description : Source File for Configuring the LED Driver (for STM32F401xC)
 Created	 : 18-Feb-24
 ============================================================================
 */

/******************************** Includes	*************************************/

#include "MCAL/GPIO.h"
#include "CFG/LED_Cfg.h"
#include "HAL/LED.h"
/***************************** Implementation ********************************/

/*Global array to set LEDs configuration */

/*I make an extra extern here beacuse of linker issue when declare and constant global array
 It implicitly make it static fri this file so the other files can't see it */

const  LED_Cfg_t LEDS[_Led_Num] = {

		/*	[Led_Green] = {
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN0,
				.Connection = LED_FORWARD,
				.Status = LED_OFF
		},

		[Led_Yellow] = {
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN12,
				.Connection = LED_FORWARD,
				.Status = LED_OFF
		},

		[Led_Red] = {
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN0,
				.Connection = LED_FORWARD,
				.Status = LED_OFF
		},
		*/
		[LED1]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN0,
				.Connection = LED_FORWARD,
				.Status = LED_ON
		},

		[LED2]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN1,
				.Connection = LED_FORWARD,
				.Status = LED_ON
		},
		[LED3]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN2,
				.Connection = LED_FORWARD,
				.Status = LED_ON
		},


};
