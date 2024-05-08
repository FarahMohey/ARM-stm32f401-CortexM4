/*
 ============================================================================
 Name        : LED.c
 Author      : Farah Mohey
 Description : Source File for the LED Driver (for STM32F401xC)
 Created	 : 18-Feb-24
 ============================================================================
 */

/******************************** Includes	*************************************/
#include "HAL/LED.h"
#include "MCAL/GPIO.h"

/******************************		Variables    ************************************/
extern  const LED_Cfg_t LEDS[_Led_Num];

/****************************  Implementation *********************************/
/*
 * @brief    : Initializes a LED pin based on the provided configuration.
 * @param	 : Void.
 * @return   : enumError_t - Error status indicating success or failure of the initialization.
 */
enumError_t LED_Init (void)
{
	/*Variable to store error status to be returned at the end of the function */
	u32 Ret_ErrorStatus = Ok;

	/*Create an object from  GPIO_Config_t struct to configure the provided leds*/
	GPIO_Config_t led;
	led.Mood= GPIO_OUTPUT_PP;		/*Configure all LEDs Mood as Push PUll */
	led.Speed=GPIO_HIGH_SPEED;

	/*Loop for each led to initialize it */
	u8 loc_idx=0;
	for (loc_idx=0 ; loc_idx < _Led_Num; loc_idx++)
	{
		/*configure leds' port and pin in GPIO*/
		led.Port = LEDS[loc_idx].Port;
		led.Pin = LEDS[loc_idx].Pin;

		/*Init GPIO pins And Set the init status for the required LED */
		Ret_ErrorStatus = GPIO_InitPin(&led);
		Ret_ErrorStatus = GPIO_Set_PinValue( LEDS[loc_idx].Port , LEDS[loc_idx].Pin , ( (LEDS[loc_idx].Connection) ^ (LEDS[loc_idx].Status) ) );
	}

	/*Return the error status*/
	return Ret_ErrorStatus ;
}


/*
 * @brief    : Sets the value of a LED pin to a specified state.
 * @param	 : LEDName, LEDStatus (LED_ON or LED_OFF)
 * @return   : enumError_t - success or failure of setting the pin value.
 * @details  : This function sets the value of a Specific LED pin to the specified state (ON or OFF).
 */
enumError_t LED_Set_Status(u32 LEDName , u32 LEDStatus)
{
	/*Variable to store error status to be returned at the end of the function */
	u32 Ret_ErrorStatus = Nok;

	/*Validate if user entered valid input , Valid LEDName & Valid LEDStatus */
	if( (LEDName > _Led_Num ) || ( (LEDStatus != LED_ON) && (LEDStatus != LED_OFF) ) )
	{
		Ret_ErrorStatus= WrongInput ;
	}

	else
	{    /*Set the required pin with the required status whether it was on or off */
		GPIO_Set_PinValue( LEDS[LEDName].Port , LEDS[LEDName].Pin , ( (LEDS[LEDName].Connection) ^ LEDStatus ) );

		Ret_ErrorStatus = Ok;

		/* Toggle the LEDStatus with the LED Connection, So The value refers to the pin status
		 *
		 *            XOR                       LED_STATE_OFF(0)				  LED_STATE_ON(1)
		 *
		 *                                      (pin status)
		 *  LED_CONNECTION_FORWARD (0) 	            (0)                                (1)
		 *
		 *  LED_CONNECTION_REVERSED (1)	            (1)                                (0)
		 */

	}

	return Ret_ErrorStatus;
}

