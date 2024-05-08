/*
 ============================================================================
 Name        : GPIO.c
 Author      : Farah Mohey
 Description : Source file for GPIO (General-purpose I/Os for STM32F401xC)
 Created	 : 18-Feb-24
 ============================================================================
 */

/****************************** Includes	***************************************/
#include "MCAL/GPIO.h"

/****************************Definitions ***********************************/

#define GPIO_MODE_MASK      0x00000003  /*-->11*/
#define GPIO_OUT_TYPE_MASK  0x00000004	/*-->100*/
#define GPIO_PULL_TYPE_MASK 0x00000018	/*-->1 1000*/


#define GPIO_SET_1_BIT      BIT0_MASK	/*0x00000001*/
#define GPIO_SET_2_BITS     0x00000003
#define GPIO_SET_3_BITS     0x00000007


#define GPIO_OUT_TYPE_SHIFT         2
#define GPIO_PULL_TYPE_SHIFT        3

#define GPIO_GROUP_OF_2_BITS        2
#define GPIO_GROUP_OF_3_BITS        3


/************************* Types Declaration ********************************/
typedef struct
{
	u32	MODER     ;
	u32 OTYPER    ;
	u32 OSPEEDR   ;
	u32 PUPDR     ;
	u32 IDR       ;
	u32 ODR       ;
	u32 BSRR      ;
	u32 LCKR      ;
	u32 AFRL      ;
	u32 AFRH      ;
}GPIO_PORT_t;


/***************************** Implementation  ********************************/

/*
 * @brief    : Initializes a GPIO pin based on the provided configuration.
 * @param[in]: Loc_GPIOElement - Pointer to a structure containing the GPIO pin configuration.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a GPIO pin according to the provided configuration.
 */
enumError_t GPIO_InitPin (GPIO_Config_t *Loc_GPIOElement)
{
	u32 Ret_ErrorStatus = Nok;

	/*Validate the input parameters*/
	if(Loc_GPIOElement == NULL_PTR)
	{
		Ret_ErrorStatus= NullPointer;
	}

	else if(Loc_GPIOElement->Mood >GPIO_AF_OD_PD || Loc_GPIOElement->Speed >GPIO_VERY_HIGH_SPEED)
	{
		Ret_ErrorStatus= WrongInput;
	}

	else if ( (Loc_GPIOElement->Port < GPIO_PORTA || Loc_GPIOElement->Port > GPIO_PORTE ) && Loc_GPIOElement->Port != GPIO_PORTH )
	{
		Ret_ErrorStatus= WrongInput;
	}

	else if(Loc_GPIOElement->Pin > GPIO_PIN15)
	{
		Ret_ErrorStatus= WrongInput;
	}
	else
	{
		Ret_ErrorStatus = Ok;

		/* Getting the Mode value , Output Type , the value of pull-up/pull-down from the mask
		 * By Anding with the Clear Mask And Shifting with this bits.
		 * The first 2 bits --> Mode
		 * The second 1 bit --> Output Type
		 * The Third 2 bits --> PullUp Or PullDown
		 */
		u32 Loc_Mode_Value = (Loc_GPIOElement->Mood) & GPIO_MODE_MASK;
		u32 Loc_OutType_Value = ( (Loc_GPIOElement->Mood) & GPIO_OUT_TYPE_MASK ) >> GPIO_OUT_TYPE_SHIFT ;
		u32 Loc_Pull_Value = (Loc_GPIOElement->Mood) & GPIO_PULL_TYPE_MASK >> GPIO_PULL_TYPE_SHIFT;


		/*Assign the addresses in local vars */
		u32 loc_MODER_Temp	=((GPIO_PORT_t *)Loc_GPIOElement->Port)-> MODER ;
		u32 loc_OTYPER_Temp	=((GPIO_PORT_t *)Loc_GPIOElement->Port )->OTYPER;
		u32 loc_OSPEEDR_Temp=((GPIO_PORT_t *)Loc_GPIOElement->Port)->OSPEEDR ;
		u32 loc_PUPDR_Temp	=((GPIO_PORT_t *)Loc_GPIOElement->Port)->PUPDR ;


		/*Clear bits which will be configured according to the provided configuration from the user*/

		/*Each Pin is represented by 2 bits , so we need to shift according to the pin number after multiplying it by 2 */
		loc_MODER_Temp   &= ~ (GPIO_SET_2_BITS << ( (Loc_GPIOElement ->Pin) * GPIO_GROUP_OF_2_BITS) );
		loc_OSPEEDR_Temp &= ~ (GPIO_SET_2_BITS << ( (Loc_GPIOElement ->Pin) * GPIO_GROUP_OF_2_BITS) );
		loc_PUPDR_Temp	 &= ~ (GPIO_SET_2_BITS << ( (Loc_GPIOElement ->Pin) * GPIO_GROUP_OF_2_BITS) );
		loc_OTYPER_Temp  &= ~ (GPIO_SET_1_BIT) << (Loc_GPIOElement->Pin); /*OTYPER is represented by 1 bit only */


		/*Set bits which will be configured according to the provided configuration from the user in the temp vars */
		loc_MODER_Temp   |=  (Loc_Mode_Value << ( (Loc_GPIOElement ->Pin) * GPIO_GROUP_OF_2_BITS) );
		loc_PUPDR_Temp	 |=  (Loc_Pull_Value << ( (Loc_GPIOElement ->Pin) * GPIO_GROUP_OF_2_BITS) );
		loc_OTYPER_Temp  |=  Loc_OutType_Value << (Loc_GPIOElement->Pin); /*OTYPER is represented by 1 bit only */
		loc_OSPEEDR_Temp |=  (Loc_GPIOElement->Speed << ( (Loc_GPIOElement ->Pin) * GPIO_GROUP_OF_2_BITS) ); /*Speed is not injected in the Mood */


		/*ReAllocate the new configuration of temp back to the registers to init the pin with the new configuration*/
		((GPIO_PORT_t *)Loc_GPIOElement->Port)-> MODER   = loc_MODER_Temp;
		((GPIO_PORT_t *)Loc_GPIOElement->Port)-> OTYPER  = loc_OTYPER_Temp;
		((GPIO_PORT_t *)Loc_GPIOElement->Port)-> OSPEEDR = loc_OSPEEDR_Temp;
		((GPIO_PORT_t *)Loc_GPIOElement->Port)-> PUPDR   = loc_PUPDR_Temp;
	}

	return Ret_ErrorStatus;
}


/*
 * @brief    : Sets the value of a GPIO pin to a specified state.
 * @param[in]: Port - Pointer to the GPIO port (GPIO_PORTA B C D E H).
 * @param[in]: PinNum - The number of the pin to be set (FROM GPIO_PIN0-->16) .
 * @param[in]: PinState - The state to set the pin to (GPIO_SET_PIN or GPIO_RESET_PIN).
 * @return   : enumError_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function sets the value of a GPIO pin to the specified state (high or low).
 */
enumError_t GPIO_Set_PinValue(void *Port , u32 PinNum , u32 PinState )
{
	u32 Ret_ErrorStatus = Nok;

	/*Validate the input parameters*/

	if(Port == NULL_PTR)
	{
		Ret_ErrorStatus= NullPointer;
	}

	else if ( (Port < GPIO_PORTA || Port > GPIO_PORTE ) && Port != GPIO_PORTH )
	{
		Ret_ErrorStatus= WrongInput;
	}

	else if(PinNum > GPIO_PIN15)
	{
		Ret_ErrorStatus= WrongInput;
	}
	else if(PinState != GPIO_SET_PIN && PinState != GPIO_RESET_PIN)
	{
		Ret_ErrorStatus= WrongInput;
	}

	else
	{
		Ret_ErrorStatus = Ok;

		/*Assign the desired value of the pin & using feature of first 16 bit set and second 16 bit is reset*/
		((GPIO_PORT_t *)Port)->BSRR=  PinState << PinNum;
	}
	return Ret_ErrorStatus;
}

/*
 * @brief     : Gets the current value of a GPIO pin.
 * @param[in] : Port - Pointer to the GPIO port (GPIO_PORTA B C D E H).
 * @param[in] : PinNum - The number of the pin to be set (FROM GPIO_PIN0-->16) .
 * @param[out]: PinStatus - Pointer to a variable to store the pin status (1 for high, 0 for low).
 * @return    : enumError_t - Error status indicating success or failure of reading the pin value.
 * @details   : This function reads the current value of a GPIO pin and stores it in PinStatus.
 */
enumError_t GPIO_Get_PinValue(void *Port , u32 PinNum,  u32 *PinStatus)
{
	u32 Ret_ErrorStatus = Nok;

	/*Validate the input parameters*/

	if(Port == NULL_PTR)
	{
		Ret_ErrorStatus= NullPointer;
	}

	else if ( (Port < GPIO_PORTA || Port > GPIO_PORTE ) && Port != GPIO_PORTH )
	{
		Ret_ErrorStatus= WrongInput;
	}

	else if(PinNum > GPIO_PIN15)
	{
		Ret_ErrorStatus= WrongInput;
	}
	else
	{
		Ret_ErrorStatus = Ok;

		*PinStatus = (( ( ((GPIO_PORT_t *) Port)->IDR) & (1 << PinNum) ) >> PinNum);

	}
	return Ret_ErrorStatus;
}


