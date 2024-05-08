/*
 ============================================================================
 Name        : LED.h
 Author      : Farah Mohey
 Description : Header File for the LED Driver (for STM32F401xC)
 Created	 : 18-Feb-24
 ============================================================================
 */

#ifndef HAL_LED_H_
#define HAL_LED_H_

/******************************* Includes *************************************/
#include  	"LIB/Std_Types.h"
#include  	"LIB/Errors_enum.h"
#include   	"CFG/LED_Cfg.h"

/******************************* Definitions ***********************************/
#define LED_ON 	 	  0x00000001	/*Value of GPIO Set Pin */
#define LED_OFF		  0x00010000	/*Value of GPIO Reset Pin --> Clear*/

#define LED_FORWARD	  0x00000000
#define LED_REVERSED  0x00010001

/************************* Types Declaration **********************************/
/*Struct for new LED  configuration */
typedef struct
{
	void* Port;
	u32   Pin;
	u32   Connection;
	u32   Status;
}LED_Cfg_t;

/************************** Functions Prototypes *************************/
/*
 * @brief    : Initializes a LED pin based on the provided configuration.
 * @param	 : Void.
 * @return   : enumError_t - Error status indicating success or failure of the initialization.
 */
enumError_t LED_Init (void);

/*
 * @brief    : Sets the value of a LED pin to a specified state.
 * @param	 : LEDName, LEDStatus (LED_ON or LED_OFF)
 * @return   : enumError_t - success or failure of setting the pin value.
 * @details  : This function sets the value of a Specific LED pin to the specified state (ON or OFF).
 */
enumError_t LED_Set_Status(u32 LEDName , u32 LEDStatus);


#endif /* HAL_LED_H_ */
