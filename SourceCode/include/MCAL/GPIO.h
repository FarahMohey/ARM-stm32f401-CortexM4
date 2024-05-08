/*
 ============================================================================
 Name        : GPIO.h
 Author      : Farah Mohey
 Description : Header file for GPIO (General-purpose I/Os for STM32F401xC)
 Created	 : 18-Feb-24
 ============================================================================
 */

#ifndef GPIO_H_
#define GPIO_H_

/******************************* Includes *************************************/
#include  	"LIB/Std_Types.h"
#include  	"LIB/Masks.h"
#include  	"LIB/Errors_enum.h"

/******************************* Definitions ***********************************/
#define GPIO_PORTA  (void *)(0x40020000)
#define GPIO_PORTB	(void *)(0x40020400)
#define GPIO_PORTC  (void *)(0x40020800)
#define GPIO_PORTD 	(void *)(0x40020C00)
#define GPIO_PORTE 	(void *)(0x40021000)
#define GPIO_PORTH	(void *)(0x40021C00)

/********************Macros for the GPIO pins********************/
#define GPIO_PIN0 	0x00000000
#define GPIO_PIN1 	0x00000001
#define GPIO_PIN2 	0x00000002
#define GPIO_PIN3 	0x00000003
#define GPIO_PIN4 	0x00000004
#define GPIO_PIN5 	0x00000005
#define GPIO_PIN6 	0x00000006
#define GPIO_PIN7 	0x00000007
#define GPIO_PIN8 	0x00000008
#define GPIO_PIN9	0x00000009
#define GPIO_PIN10 	0x0000000A
#define GPIO_PIN11 	0x0000000B
#define GPIO_PIN12 	0x0000000C
#define GPIO_PIN13 	0x0000000D
#define GPIO_PIN14 	0x0000000E
#define GPIO_PIN15 	0x0000000F


/********************Macros for the GPIO SPEEDS********************/
#define GPIO_LOW_SPEED			ALL_ZERO_MASK /*0x00000000*/
#define GPIO_MEDIUM_SPEED		BIT0_MASK	  /*0x00000001*/
#define GPIO_HIGH_SPEED			BIT1_MASK 	  /*0x00000002*/
#define GPIO_VERY_HIGH_SPEED	0x00000003

/********************Macros for the GPIO MOODS********************/
#define GPIO_INPUT_FL		ALL_ZERO_MASK	/*0x00000000*/
#define GPIO_INPUT_PU		BIT3_MASK		/*0x00000008*/
#define GPIO_INPUT_PD		BIT4_MASK		/*0x00000010*/

#define GPIO_OUTPUT_PP 		0x00000001
#define GPIO_OUTPUT_PP_PU	0x00000009
#define GPIO_OUTPUT_PP_PD	0x00000011
#define GPIO_OUTPUT_OD		0x00000005
#define GPIO_OUTPUT_OD_PU	0x0000000D
#define GPIO_OUTPUT_OD_PD	0x00000015

#define GPIO_ANALOG 		0x00000003

#define GPIO_AF_PP 			0x00000002
#define GPIO_AF_PP_PU		0x0000000A
#define GPIO_AF_PP_PD		0x00000012
#define GPIO_AF_OD			0x00000006
#define GPIO_AF_OD_PU		0x0000000E
#define GPIO_AF_OD_PD		0x00000016

#define GPIO_SET_PIN 		BIT0_MASK	/*first 16 pin set*/
#define GPIO_RESET_PIN 		BIT16_MASK	/*last 16 pin reset*/

/************************* Types Declaration ********************************/

/*Struct for new GPIO pin configuration */
typedef struct
{

	void* Port;
	u32  Pin;
	u32  Speed;
	u32  Mood;

}GPIO_Config_t;

/************************** Functions Prototypes ******************************/

/*
 * @brief    : Initializes a GPIO pin based on the provided configuration.
 * @param[in]: Loc_GPIOElement - Pointer to a structure containing the GPIO pin configuration.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a GPIO pin according to the provided configuration.
 */
enumError_t GPIO_InitPin (GPIO_Config_t *Loc_GPIOElement);

/*
 * @brief    : Sets the value of a GPIO pin to a specified state.
 * @param[in]: Port - Pointer to the GPIO port (GPIO_PORTA B C D E H).
 * @param[in]: PinNum - The number of the pin to be set (FROM GPIO_PIN0-->16) .
 * @param[in]: PinState - The state to set the pin to (GPIO_SET_PIN or GPIO_RESET_PIN).
 * @return   : enumError_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function sets the value of a GPIO pin to the specified state (high or low).
 */
enumError_t GPIO_Set_PinValue(void *Port , u32 PinNum , u32 PinState );

/*
 * @brief     : Gets the current value of a GPIO pin.
 * @param[in] : Port - Pointer to the GPIO port (GPIO_PORTA B C D E H).
 * @param[in] : PinNum - The number of the pin to be set (FROM GPIO_PIN0-->16) .
 * @param[out]: PinStatus - Pointer to a variable to store the pin status (1 for high, 0 for low).
 * @return    : enumError_t - Error status indicating success or failure of reading the pin value.
 * @details   : This function reads the current value of a GPIO pin and stores it in PinStatus.
 */
enumError_t GPIO_Get_PinValue(void *Port , u32 PinNum,  u32 *PinStatus) ;



#endif /* GPIO_H_ */
