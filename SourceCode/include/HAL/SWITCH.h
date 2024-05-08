/*
 ============================================================================
 Name        : SWITCH.h
 Author      : Farah Mohey
 Description : Header File for the SWITCH Driver (for STM32F401xC)
 Created	 : 12-Apr-24
 ============================================================================
 */

#ifndef HAL_SWITCH_H_
#define HAL_SWITCH_H_

/******************************* Includes *************************************/

#include  	"LIB/Std_Types.h"
#include  	"LIB/Errors_enum.h"
#include    "MCAL/GPIO.h"
#include   	"CFG/SWITCH_Cfg.h"

/******************************* Definitions ***********************************/
#define SWITCH_RELEASED		0x00000000
#define SWITCH_PRESSED 	 	0x00000001

/************************* Types Declaration **********************************/
/*Struct for new switch  configuration */
typedef struct
{
	void* Port;
	u32   Pin;
	u32   Connection;
}SWITCH_Cfg_t;


/************************** Functions Prototypes *************************/
/*
 * @brief    : Initializes a SWITCH pin based on the provided configuration.
 * @param	 : Void.
 * @return   : enumError_t - Error status indicating success or failure of the initialization.
 */

enumError_t SWITCH_Init (void);

/*
 * @brief    : Sets the value of a SWITCH pin to a specified state.
 * @param[in]: SWITCHNum
 * @param[in]: SWITCH_Status - The status of switch if it was PRESSED orRELEASED .
 * @return   : enumError_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function gets the value of a Specific SWITCH if (pressed or released).
 */
enumError_t SWITCH_Get_Status(u32 SWITCHNum , u8 *SWITCH_Status);


#endif /* HAL_SWITCH_H_ */
