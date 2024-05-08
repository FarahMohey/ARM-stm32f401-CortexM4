/*
 ============================================================================
 Name        : SWITCH_Cfg.c
 Author      : Farah Mohey
 Description : Source File for Configuring the Switch Driver (for STM32F401xC)
 Created	 : 12-Apr-24
 ============================================================================

/******************************** Includes*************************************/

#include "MCAL/GPIO.h"
#include "CFG/SWITCH_Cfg.h"
#include "HAL/SWITCH.h"

/**************************** Implementation ***********************************/
/*Global array to set Switches configuration */
const  SWITCH_Cfg_t SWITCHES[_Switch_Num] =
{
		/*Ex : Set Switch1 Configuration*/
		[Switch1] = {
				.Port = GPIO_PORTB,
				.Pin = GPIO_PIN4,
				.Connection = GPIO_INPUT_PU
		},
		[Switch2] = {
				.Port = GPIO_PORTB,
				.Pin = GPIO_PIN5,
				.Connection = GPIO_INPUT_PU
		},
		[Switch3] = {
				.Port = GPIO_PORTB,
				.Pin = GPIO_PIN6,
				.Connection = GPIO_INPUT_PU
		}
};
