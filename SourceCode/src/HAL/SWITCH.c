/*
 ============================================================================
 Name        : SWITCH.c
 Author      : Farah Mohey
 Description : Source File for the SWITCH Driver (for STM32F401xC)
 Created	 : 12-Apr-24
 ============================================================================
 */

/******************************** Includes *************************************/
#include "HAL/SWITCH.h"
#include "MCAL/GPIO.h"

/****************************** Definitions *************************************/
//#define Get_CURRENT_CONNECTION_SHIFT_MASK 3

/******************************** Variables ************************************/
extern const  SWITCH_Cfg_t SWITCHES[_Switch_Num];
//static u8 Switch_Status[_Switch_Num];


/***************************** Implementation **********************************/
/*
 * @brief    : Initializes a SWITCH pin based on the provided configuration.
 * @param	 : Void.
 * @return   : enumError_t - Error status indicating success or failure of the initialization.
 */

enumError_t SWITCH_Init (void)
{
	/*Variable to store error status to be returned at the end of the function */
	u32 Ret_ErrorStatus = Ok;

	/*Create an object from  GPIO_Config_t struct to configure the provided switches*/
	GPIO_Config_t Switch;

	/*Loop for each led to initialize it */
	u8 loc_idx=0;
	for (loc_idx=0 ; loc_idx < _Switch_Num; loc_idx++)
	{
		/*configure Switch' port, pin, mood in GPIO*/
		Switch.Port = SWITCHES[loc_idx].Port;
		Switch.Pin = SWITCHES[loc_idx].Pin;
	Switch.Mood = SWITCHES[loc_idx].Connection;

		/*Init GPIO pins And Set the init status for the required switch */
		Ret_ErrorStatus = GPIO_InitPin(&Switch);
	}

	/*Return the error status*/
	return Ret_ErrorStatus ;

}

/*
 * @brief    : Sets the value of a SWITCH pin to a specified state.
 * @param[in]: SWITCHNum
 * @param[in]: SWITCH_Status - The status of switch if it was PRESSED orRELEASED .
 * @return   : enumError_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function gets the value of a Specific SWITCH if (pressed or released).
 */

enumError_t SWITCH_Get_Status(u32 SWITCHNum , u8 *SWITCH_Status)
{
	/*Variable to store error status to be returned at the end of the function */
	u32 Ret_ErrorStatus = Nok;

	/*Validate if user entered valid input , Valid SWITCHNum & Valid SWITCH_Status Pointer */
	if( SWITCHNum >= _Switch_Num )
	{
		Ret_ErrorStatus= WrongInput ;
	}
	else if(SWITCH_Status ==  NULL_PTR)
	{
		Ret_ErrorStatus= NullPointer ;
	}
	else
	{

		/*Assign Switch value according to current value*/
	//	*SWITCH_Status = Switch_Status[SWITCHNum];



	}
	return Ret_ErrorStatus;
}



