/*
 ============================================================================
 Name        : RCC.h
 Author      : Farah Mohey
 Description : Header file for RCC (Reset and clock control for STM32F401xC)
 Created	 : 15-Feb-24
 ============================================================================
 */

#ifndef RCC_H_
#define RCC_H_

/********************************* Includes	*************************************/
#include  	"LIB/Std_Types.h"
#include  	"LIB/Masks.h"
#include  	"LIB/Errors_enum.h"



/********************************* Definition **********************************/

/************Clocks_Masks ************/
/*****for ON & OFF  ******/
#define CLK_HSI		BIT0_MASK
#define CLK_HSE		BIT16_MASK
#define CLK_PLL 	BIT24_MASK
#define CLK_PLL_I2S BIT26_MASK

/*****for READY  ******/
#define READY_CLK_HSI	BIT1_MASK
#define READY_CLK_HSE	BIT17_MASK
#define READY_CLK_PLL 	BIT25_MASK
#define READY_CLK_PLL_I2S	 BIT27_MASK

/*****for SYSCLK  ******/
#define SYSCLK_HSI	ALL_ZERO_MASK
#define SYSCLK_HSE	BIT0_MASK
#define SYSCLK_PLL	BIT1_MASK

/*****for PLL_SRC  ******/
#define PLL_SRC_HSI		ALL_ZERO_MASK
#define PLL_SRC_HSE 	BIT22_MASK


/************PRE-Scaler Options for buses APB1, AB2 ,AHB ************/

/*Prescaler options for APB1 --> APB Low Speed BUS*/
#define APB_L_1 	ALL_ZERO_MASK 	/*0x00000000*/
#define APB_L_2 	BIT12_MASK		/*x000010000*/
#define APB_L_4 	0x00001400
#define APB_L_8 	0x00001800
#define APB_L_16 	0x00001C00

/*Prescaler options for APB2 --> APB High Speed BUS*/
#define APB_H_1		ALL_ZERO_MASK 	/*0x00000000*/
#define APB_H_2		BIT15_MASK		/*0x00008000*/
#define APB_H_4		0x0000A000
#define APB_H_8		0x0000C000
#define APB_H_16	0x0000E000

/*Prescaler options for AHB BUS*/
#define AHB_1		ALL_ZERO_MASK 	/*0x00000000*/
#define AHB_2 		BIT7_MASK 		/*0x00000080*/
#define AHB_4		0x00000090
#define AHB_8		0x000000A0
#define AHB_16		0x000000B0
#define AHB_64		0x000000C0
#define AHB_128		0x000000D0
#define AHB_256		0x000000E0
#define AHB_512		0x000000F0


/************AHB1_BUS_Peripheral_Masks ************/
#define AHB1_GPIOA	BIT0_MASK
#define AHB1_GPIOB	BIT1_MASK
#define AHB1_GPIOC	BIT2_MASK
#define AHB1_GPIOD	BIT3_MASK
#define AHB1_GPIOE	BIT4_MASK
#define AHB1_GPIOH	BIT7_MASK
#define AHB1_CRC 	BIT12_MASK
#define AHB1_DMA1	BIT21_MASK
#define AHB1_DMA2	BIT22_MASK

/************AHB2_BUS_Peripheral_Masks ************/
#define AHB2_OTGFS	BIT7_MASK

/************APB1_BUS_Peripheral_Masks ************/
#define APB1_TIM2	BIT0_MASK
#define APB1_TIM3	BIT1_MASK
#define APB1_TIM4	BIT2_MASK
#define APB1_TIM5	BIT3_MASK
#define APB1_WWDG	BIT11_MASK
#define APB1_SPI2	BIT14_MASK
#define APB1_SPI3	BIT15_MASK
#define APB1_USART2	BIT17_MASK
#define APB1_I2C1	BIT21_MASK
#define APB1_I2C2	BIT22_MASK
#define APB1_I2C3	BIT23_MASK
#define APB1_PWR	BIT28_MASK

/************APB2_BUS_Peripheral_Masks ************/
#define APB2_TIM1	BIT0_MASK
#define APB2_USART1	BIT4_MASK
#define APB2_USART6	BIT5_MASK
#define APB2_ADC1	BIT8_MASK
#define APB2_SDIO	BIT11_MASK
#define APB2_SPI1	BIT12_MASK
#define APB2_SPI4	BIT13_MASK
#define APB2_SYSCFG	BIT14_MASK
#define APB2_TIM9	BIT16_MASK
#define APB2_TIM10	BIT17_MASK
#define APB2_TIM11	BIT18_MASK


/************************** Functions Prototypes *******************************/
/*
 * @brief    : Set Clock ON.
 * @param	 : CLK to be set on. It can be CLK_HSI, CLK_HSE, or CLK_PLL.
 * @return   : enumError_t ,Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock.
 */
enumError_t RCC_SET_Clock_ON (u32 CLK);

/*
 * @brief    : Set Clock OFF.
 * @param	 : CLK to be set off. It can be CLK_HSI, CLK_HSE, or CLK_PLL.
 * @return   : enumError_t, Error status indicating the success or failure of setting the clock off.
 * @details  : This function turns off the specified clock.
 */
enumError_t RCC_SET_Clock_OFF (u32 CLK);

/*
 * @brief    : Read if the Clock is Ready or not
 * @param	 : READY_CLK. It can be READY_CLK_HSI or READY_CLK_HSE, or READY_CLK_PLL or READY_CLK_PLL_I2S
 * @return   : enumError_t, Error status indicating the success or failure of selecting the system clock.
 */
enumError_t RCC_READ_ClockReadyState(u32 READY_CLK);

/*
 * @brief    : Select System Clock.
 * @param	 : SYSCLK The system clock source to be selected. It can be SYSCLK_HSI_MASK, SYSCLK_HSE_MASK, or SYSCLK_PLL_MASK.
 * @return   : enumError_t , Error status indicating the success or failure of selecting the system clock.
 * @details  : This function selects the system clock source among the available options: HSI, HSE, or PLL.
 */
enumError_t RCC_Select_SysClk(u32 SYSCLK);


/*
 * @brief    : Read System Clock.
 * @param	 : void
 * @return   : u32
 * @details  : This function gets the system clock activate now among the available options: HSI, HSE, or PLL.
 */
u32 RCC_Read_SysClk(void);

/*
 * @brief    : Configure PLL Source.
 * @param	 : Copy_PLLSrc The PLL source to be configured. It can be PLL_SRC_HSI or PLL_SRC_HSE.
 * @return   : enumError_t Error status indicating the success or failure of configuring PLL source.
 * @details  : This function configures the PLL source to be either HSI or HSE.
 */
enumError_t RCC_Config_PLLSrc(u32 PLL_SRC);

/*
 * @brief    : Configure PLL Parameters.
 * @param	 : PLLM, PLLN, PLLP, PLLQ The parameters to configure PLL.
 * @return   : enumError_t Error status indicating the success or failure of configuring PLL parameters.
 * @details  : This function configures the parameters (M, N, P, Q) for the PLL.
 * @note     : Ranges of Paramters 2<=PLLM<=63 ,192<=PLLN<=432 , 2<=PLLQ<=15 , PLLP = 2,4,6,8
 */
enumError_t RCC_Config_PLLParamters(u32 PLLM ,u32 PLLN , u32 PLLP ,u32 PLLQ);

/*
 * @brief    : Configure APB high-speed prescaler BUS Prescaler APB2.
 * @param	 : APBH_PreScalerValue
 * @param	 : It Can be APB_H_1 , APB_H_2 , APB_H_4 , APB_H_8 , APB_H_16
 * @return   : enumError_t, Error status indicating the success or failure of setting prescaler value.
 */
enumError_t RCC_Config_APBH_BusPrescaler (u32  APBH_PreScalerValue);
/*
 * @brief    : Configure APB Low speed prescaler BUS Prescaler APB1.
 * @param	 : APBL_PreScalerValue
 * @param	 : It Can be APB_L_1 , APB_L_2 , APB_L_4 , APB_L_8 , APB_L_16
 * @return   : enumError_t, Error status indicating the success or failure of setting prescaler value.
 */
enumError_t RCC_Config_APBL_BusPrescaler (u32  APBL_PreScalerValue);
/*
 * @brief    : Configure AHB prescalerr BUS Prescaler AHB.
 * @param	 : AHB_PreScalerValue
 * @param	 : It Can be AHB_1 ,AHB_2 ,AHB_4 , AHB_8 , AHB_16 , AHB_64 , AHB_128 , AHB_256 , AHB_512
 * @return   : enumError_t, Error status indicating the success or failure of setting prescaler value.
 */
enumError_t RCC_Config_AHB_BusPrescaler (u32  AHB_PreScalerValue);


/*
 * @brief    : Enable AHB1 Peripheral.
 * @param	 : AHB1_PeripheralName, The AHB1 peripheral to be enabled.
 * @return   : enumError_t Error status indicating the success or failure of enabling the AHB1 peripheral.
 * @details  : This function enables the specified peripheral connected to the AHB1 bus.
 * @note     : AHB1 Peripherals are AHB1_ GPIO A,B,C,D,E,H , CRC , DMA1,2
 */
enumError_t RCC_Enable_AHB1_Peripheral(u32 AHB1_PeripheralName);
/*
 * @brief    : Disable AHB1 Peripheral.
 * @param 	 : AHB1_PeripheralName The AHB1 peripheral to be disabled.
 * @return   : enumError_t Error status indicating the success or failure of disabling the AHB1 peripheral.
 * @details  : This function disables the specified peripheral connected to the AHB1 bus.
 * @note     : AHB1 Peripherals are AHB1_ GPIO A,B,C,D,E,H , CRC , DMA1,2
 */
enumError_t RCC_Disable_AHB1_Peripheral(u32 AHB1_PeripheralName);

/*
 * @brief    : Enable AHB2 Peripheral.
 * @param	 : AHB2_PeripheralName, The AHB2 peripheral to be enabled.
 * @return   : enumError_t Error status indicating the success or failure of enabling the AHB2 peripheral.
 * @details  : This function enables the specified peripheral connected to the AHB2 bus.
 * @note     : AHB2 Peripherals are AHB2_OTGFS
 */
enumError_t RCC_Enable_AHB2_Peripheral(u32 AHB2_PeripheralName);

/*
 * @brief    : Disable AHB2 Peripheral.
 * @param 	 : AHB2_PeripheralName The AHB1 peripheral to be disabled.
 * @return   : enumError_t Error status indicating the success or failure of disabling the AHB2 peripheral.
 * @details  : This function disables the specified peripheral connected to the AHB2 bus.
 * @note     : AHB2 Peripherals are AHB2_OTGFS
 */
enumError_t RCC_Disable_AHB2_Peripheral(u32 AHB2_PeripheralName);


/*
 * @brief    : Enable APB1 Peripheral.
 * @param	 : APB1_PeripheralName, The APB1 peripheral to be enabled.
 * @return   : enumError_t , Error status indicating the success or failure of enabling the APB1 peripheral.
 * @details  : This function enables the specified peripheral connected to the APB1 bus.
 * @note     : APB1 Peripherals are APB1_ TIM 2,3,4,5 , APB1_WWDG , APB1_ SPI2,3 ,APB1_USART2 , APB1_ I2C1,2,3 , APB1_PWR
 */
enumError_t RCC_Enable_APB1_Peripheral(u32 APB1_PeripheralName);

/*
 * @brief    : Disable APB1 Peripheral.
 * @param	 : APB1_PeripheralName, The APB1 peripheral to be disabled.
 * @return   : enumError_t Error status indicating the success or failure of disabling the APB1 peripheral.
 * @details  : This function disables the specified peripheral connected to the APB1 bus.
 * @note     : APB1 Peripherals are APB1_ TIM 2,3,4,5 , APB1_WWDG , APB1_ SPI2,3 ,APB1_USART2 , APB1_ I2C1,2,3 , APB1_PWR
 */
enumError_t RCC_Disable_APB1_Peripheral(u32 APB1_PeripheralName);

/*
 * @brief    : Enable APB2 Peripheral.
 * @param	 : APB2_PeripheralName. The APB2 peripheral to be enabled.
 * @return   : enumError_t, Error status indicating the success or failure of enabling the APB2 peripheral.
 * @details  : This function enables the specified peripheral connected to the APB2 bus.
 * @note     : APB2 Peripherals are APB2_TIM1 , APB2_USART1,6 , APB2_ADC1 , APB2_SDIO , APB2_SPI1,4 , APB2_SYSCFG , APB2_TIM9,10,11
 */
enumError_t RCC_Enable_APB2_Peripheral(u32 APB2_PeripheralName);

/*
 * @brief    : Disable APB2 Peripheral.
 * @param	 : APB2_PeripheralName .The APB2 peripheral to be disabled.
 * @return   : enumError_t, Error status indicating the success or failure of disabling the APB2 peripheral.
 * @details  : This function disables the specified peripheral connected to the APB2 bus.
 * @note     : APB2 Peripherals are APB2_TIM1 , APB2_USART1,6 , APB2_ADC1 , APB2_SDIO , APB2_SPI1,4 , APB2_SYSCFG , APB2_TIM9,10,11
 */
enumError_t RCC_Disable_APB2_Peripheral(u32 APB2_PeripheralName);

#endif /* RCC_H_ */
