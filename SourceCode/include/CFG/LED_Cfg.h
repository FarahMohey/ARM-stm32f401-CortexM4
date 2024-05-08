/*
 ============================================================================
 Name        : LED_CFG.h
 Author      : Farah Mohey
 Description : Header File for Configuring the LED Driver (for STM32F401xC)
 Created	 : 18-Feb-24
 ============================================================================
 */

#ifndef CFG_LED_CFG_H_
#define CFG_LED_CFG_H_

/**************************		Types Declaration	 ******************************/
/* Configure The Leds Name in this Enum */
typedef enum
{ /*
	Led_Green,
	Led_Yellow,
	*/
//	Led_Red,

	LED1,
	LED2,
	LED3,

	/*Indicate number of Max num of Leds*/
	_Led_Num
}LEDS_t;


#endif /* CFG_LED_CFG_H_ */
