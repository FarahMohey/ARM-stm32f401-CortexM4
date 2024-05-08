/*
 ============================================================================
 Name        : RCC.C
 Author      : Farah Mohey
 Description : Source file for RCC (Reset and clock control for STM32F401xC)
 Created	 : 15-Feb-24
 ============================================================================
 */

/********************************* Includes	*************************************/
#include  	"MCAL/RCC.h"

/**************************** Definitions **************************************/
#define RCC_Base_ADDRESS 	0x40023800

#define STATUS_SYSCLK_MASK	0x0000000C	/*read sysclk */
#define	SYSCLK_CLR_MASK		0xFFFFFFFC 	/*Clear bit 0,1*/

#define APBH_PRE_CLR_MASK   0XFFFF1FFF	 /* clearing bit 13,14,15 */
#define APBL_PRE_CLR_MASK   0XFFFFE3FF	 /* clearing bit 10,11,12 */

#define AHB_PRE_CLR_MASK    0XFFFFFF0F	/* clearing bit 4,5,6,7 */

/**************** PLL Config ******************/
#define PLL_SRC_CLR_MASK 	0xFFBFFFFF /*Clear bit 22 */

#define PLL_CONFIG_CLR_MASK BIT22_MASK	/*clear register with keeping PLLSRC*/

#define PLL_Q_SHIFTING		24		/*PLLN starts from bit24-->bit27 */
#define PLL_P_SHIFTING		16		/*PLLP starts from bit16 & bit 17 */
#define PLL_N_SHIFTING		6		/*PLLN starts from bit6-->bit14 */


#define PLLM_BOUNDARY1		2		/* 2 ≤ PLLM ≤ 63 */
#define PLLM_BOUNDARY2		63

#define PLLQ_BOUNDARY1		2		/*  2 ≤PLLQ ≤15 */
#define PLLQ_BOUNDARY2		15

#define PLLN_BOUNDARY1		192
#define PLLN_BOUNDARY2		432		/*192 ≤ PLLN ≤ 432 */

/**** PLLP = 2, 4, 6, or 8 ****/
#define PLLP_2		2
#define PLLP_4		4
#define PLLP_6		6
#define PLLP_8		8

/**************************   Types Declaration   *****************************/
typedef struct
{
	u32 RCC_CR 	;
	u32 RCC_PLLCFGR ;
	u32 RCC_CFGR ;
	u32 RCC_CIR  ;
	u32 RCC_AHB1RSTR  ;
	u32 RCC_AHB2RSTR  ;
	u32 Reserved  ;
	u32 Reserved2 ;
	u32 RCC_APB1RSTR  ;
	u32 RCC_APB2RSTR  ;
	u32 Reserved3  	;
	u32 Reserved4 	;
	u32 RCC_AHB1ENR  ;
	u32 RCC_AHB2ENR  ;
	u32 Reserved5 	 ;
	u32 Reserved6    ;
	u32 RCC_APB1ENR  ;
	u32 RCC_APB2ENR  ;
	u32 Reserved7  	;
	u32 Reserved8  	;
	u32 RCC_AHB1LPENR  ;
	u32 RCC_AHB2LPENR  ;
	u32 Reserved9  	;
	u32 Reserved10  ;
	u32 RCC_APB1LPENR  ;
	u32 RCC_APB2LPENR  ;
	u32 Reserved11   ;
	u32 Reserved12   ;
	u32 RCC_BDCR  ;
	u32 RCC_CSR   ;
	u32 Reserved13  ;
	u32 Reserved14  ;
	u32 RCC_SSCGR  	;
	u32 RCC_PLLI2SCFGR ;
}RCC_PERI_t;


/**************************** Variables	***************************************/
volatile RCC_PERI_t * const RCC = (volatile RCC_PERI_t *) RCC_Base_ADDRESS;


/************************** Functions Implementation *******************************/

/*
 * @brief    : Set Clock ON.
 * @param	 : CLK to be set on. It can be CLK_HSI, CLK_HSE, or CLK_PLL, or CLK_PLL_I2S
 * @return   : enumError_t, Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock.
 */
enumError_t RCC_SET_Clock_ON (u32 CLK)
{
	enumError_t Ret_ErrorStatus = Nok;

	/* Check if the provided clock source is valid */
	if (CLK != CLK_HSI && CLK != CLK_HSE && CLK != CLK_PLL && CLK != CLK_PLL_I2S )
	{
		Ret_ErrorStatus = WrongInput;
	}

	/* Clear the previous clock configuration and set the new clock source After setting error status OK */
	else
	{
		 Ret_ErrorStatus = Ok;
		u32 loc_CR_Temp = RCC->RCC_CR ;

		loc_CR_Temp &= ~CLK;	/*clear */
		loc_CR_Temp |= CLK; 	/*set */
		RCC -> RCC_CR = loc_CR_Temp ; /*Reallocte temp back to the register */
	}

	return Ret_ErrorStatus;
}
/*
 * @brief    : Set Clock OFF.
 * @param	 : CLK to be set off. It can be CLK_HSI, CLK_HSE, or CLK_PLL, or CLK_PLL_I2S
 * @return   : enumError_t ,Error status indicating the success or failure of setting the clock off.
 * @details  : This function turns off the specified clock.
 */
enumError_t RCC_SET_Clock_OFF (u32 CLK)
{
	enumError_t Ret_ErrorStatus = Nok;

	/* Check if the provided clock source is valid */
	if (CLK != CLK_HSI && CLK != CLK_HSE && CLK != CLK_PLL && CLK != CLK_PLL_I2S )
	{
		Ret_ErrorStatus = WrongInput;
	}

	/* Clear the previous clock configuration To turn off CLK After setting error status OK */
	else
	{
		 Ret_ErrorStatus = Ok;
		u32 loc_CR_Temp = RCC->RCC_CR ;

		loc_CR_Temp &= ~CLK;	/*clear */
		RCC -> RCC_CR = loc_CR_Temp ; /*Reallocte temp back to the register */
	}

	return Ret_ErrorStatus;
}

/*
 * @brief    : Read if the Clock is Ready or not
 * @param	 : READY_CLK. It can be READY_CLK_HSI or READY_CLK_HSE, or READY_CLK_PLL or READY_CLK_PLL_I2S
 * @return   : enumError_t, Error status indicating the success or failure of selecting the system clock.
 */
enumError_t RCC_READ_ClockReadyState(u32 READY_CLK)
{
	enumError_t Ret_ErrorStatus = Nok;

	/* Check if the provided clock source is valid */
	if (READY_CLK != READY_CLK_HSI && READY_CLK != READY_CLK_HSE && READY_CLK != READY_CLK_PLL && READY_CLK != READY_CLK_PLL_I2S )
	{
		Ret_ErrorStatus = WrongInput;
	}

	else
	{
		/* Set a timeout value for the clock readiness check. More than 6 Clk Cycles */
		u16 loc_TimeOut = 1000;

		/* Wait for the clock to become ready within timeout */
		/*while (still within time && flag still not set to desired ready state)*/
		while (loc_TimeOut && !(RCC->RCC_CR & READY_CLK))
		{
			loc_TimeOut--;
		}

		/* Check if the clock is still not ready after the timeout */
		if (!(RCC->RCC_CR & READY_CLK))
		{
			Ret_ErrorStatus = RCC_ClkNotReady ; /*Setting CLK to Not Ready */
		}

		else
		{
			Ret_ErrorStatus = RCC_ClkReady ; /*Setting CLK to Ready */
		}
	}
	return Ret_ErrorStatus;
}

/*
 * @brief    : Select System Clock.
 * @param	 : SYSCLK The system clock source to be selected. It can be SYSCLK_HSI_MASK, SYSCLK_HSE_MASK, or SYSCLK_PLL_MASK.
 * @return   : enumError_t , Error status indicating the success or failure of selecting the system clock.
 * @details  : This function selects the system clock source among the available options: HSI, HSE, or PLL.
 */
enumError_t RCC_Select_SysClk(u32 SYSCLK)
{
	enumError_t Ret_ErrorStatus = Nok;

	/* Check if the provided clock source is valid */
	if (SYSCLK != SYSCLK_HSI && SYSCLK != SYSCLK_HSE && SYSCLK != SYSCLK_PLL )
	{
		Ret_ErrorStatus = WrongInput;
	}

	/* Clear the previous clock configuration To ReAssign the new SysCLK value After setting error status OK */
	else
	{
		 Ret_ErrorStatus = Ok;

		u32 loc_CFGR_Temp = RCC->RCC_CFGR ;
		loc_CFGR_Temp &= SYSCLK_CLR_MASK; 	/* Clear the bits related to system clock configuration. */
		loc_CFGR_Temp |= SYSCLK; 			/* Set the bits for the selected system clock source. */
		RCC->RCC_CFGR = loc_CFGR_Temp; 		/* ReAllocate Temp to CFGR register with the new SysCLK value */
	}

	return Ret_ErrorStatus;
}

/*
 * @brief    : Read System Clock.
 * @param	 : void
 * @return   : u32
 * @details  : This function gets the system clock activate now among the available options: HSI, HSE, or PLL.
 */
u32 RCC_Read_SysClk(void)
{
	u32 loc_CFGR_Temp = RCC->RCC_CFGR & STATUS_SYSCLK_MASK;
	return loc_CFGR_Temp ;
}

/*
 * @brief    : Configure PLL Source.
 * @param	 : Copy_PLLSrc The PLL source to be configured. It can be PLL_SRC_HSI or PLL_SRC_HSE.
 * @return   : enumError_t Error status indicating the success or failure of configuring PLL source.
 * @details  : This function configures the PLL source to be either HSI or HSE.
 */
enumError_t RCC_Config_PLLSrc(u32 PLL_SRC)
{
	enumError_t Ret_ErrorStatus = Nok;

	/* Check if the provided clock source is valid */
	if(PLL_SRC != PLL_SRC_HSI && PLL_SRC != PLL_SRC_HSE)
	{
		Ret_ErrorStatus = WrongInput;
	}

	/*Setting the PLL configuration */
	else
	{
		 Ret_ErrorStatus = Ok;
		u32 loc_PLLCFGR_Temp = RCC->RCC_PLLCFGR ;

		loc_PLLCFGR_Temp &= PLL_SRC_CLR_MASK;	/*clear */
		loc_PLLCFGR_Temp |= PLL_SRC;
		RCC -> RCC_PLLCFGR = loc_PLLCFGR_Temp ; /*ReAllocte temp back to the register */
	}

	return Ret_ErrorStatus;
}

/*
 * @brief    : Configure PLL Parameters.
 * @param	 : PLLM, PLLN, PLLP, PLLQ The parameters to configure PLL.
 * @return   : enumError_t Error status indicating the success or failure of configuring PLL parameters.
 * @details  : This function configures the parameters (M, N, P, Q) for the PLL.
 * @note     : Ranges of Paramters 2<=PLLM<=63 ,192<=PLLN<=432 , 2<=PLLQ<=15 , PLLP = 2,4,6,8
 */
enumError_t RCC_Config_PLLParamters(u32 PLLM ,u32 PLLN , u32 PLLP ,u32 PLLQ)
{
	enumError_t Ret_ErrorStatus = Nok;

	/* Validate the PLL parameters */

	/* check on the value of M --> 2 ≤ PLLM ≤ 63*/
	if(PLLM < PLLM_BOUNDARY1 || PLLM > PLLM_BOUNDARY2)
	{
		Ret_ErrorStatus = WrongInput;
	}

	/* check on the value of N --> 192 ≤ PLLN ≤ 432 */
	else if(PLLN < PLLN_BOUNDARY1 || PLLN > PLLN_BOUNDARY2)
	{
		Ret_ErrorStatus = WrongInput;
	}

	/* check on the value of P --> PLLP = 2, 4, 6, or 8  */
	else if(PLLP != PLLP_2 && PLLP != PLLP_4 && PLLP != PLLP_6 && PLLP != PLLP_8)
	{
		Ret_ErrorStatus = WrongInput;
	}

	/* check on the value of Q -->  2 ≤PLLQ ≤15 */
	else if(PLLQ < PLLQ_BOUNDARY1 || PLLQ > PLLQ_BOUNDARY2)
	{
		Ret_ErrorStatus = WrongInput;
	}

	else
	{
		 Ret_ErrorStatus = Ok;
		u32 loc_PLLCFGR_Temp = RCC->RCC_PLLCFGR ;

		loc_PLLCFGR_Temp &= PLL_CONFIG_CLR_MASK; /*clearing the Register with keeping the value of PLL SRC */

		PLLP = (PLLP / 2) - 1 ; /*To get the values as needed */

		/*Setting the values in temp */
		loc_PLLCFGR_Temp |= PLLM;
		loc_PLLCFGR_Temp |= PLLN << PLL_N_SHIFTING;
		loc_PLLCFGR_Temp |= PLLP << PLL_P_SHIFTING;
		loc_PLLCFGR_Temp |= PLLQ << PLL_Q_SHIFTING;

		RCC->RCC_PLLCFGR = loc_PLLCFGR_Temp; /*ReAssign the value back in the register */
	}

	return Ret_ErrorStatus;
}


/*
 * @brief    : Configure APB high-speed prescaler BUS Prescaler APB2.
 * @param	 : APBH_PreScalerValue
 * @param	 : It Can be APB_H_1 , APB_H_2 , APB_H_4 , APB_H_8 , APB_H_16
 * @return   : enumError_t, Error status indicating the success or failure of setting prescaler value.
 */
enumError_t RCC_Config_APBH_BusPrescaler (u32  APBH_PreScalerValue)
{
	enumError_t Ret_ErrorStatus = Nok;

	/* Check if the provided PreScaler Value is valid */
	if(APBH_PreScalerValue!=APB_H_1 && APBH_PreScalerValue!= APB_H_2 && APBH_PreScalerValue != APB_H_4 && APBH_PreScalerValue!=APB_H_8 && APBH_PreScalerValue!=APB_H_16 )
	{
		Ret_ErrorStatus = WrongInput;
	}
	else
	{
		 Ret_ErrorStatus = Ok;

		u32 loc_CFGR_Temp = RCC->RCC_CFGR ;
		loc_CFGR_Temp &= APBH_PRE_CLR_MASK; 		/* Clear the bits*/
		loc_CFGR_Temp |= APBH_PreScalerValue;	/* Set the bits for the APB HighBus PreScaler Value*/
		RCC->RCC_CFGR = loc_CFGR_Temp;		/* ReAllocate Temp to CFGR register with the new PreScaler Value*/
	}

	return Ret_ErrorStatus;

}

/*
 * @brief    : Configure APB Low speed prescaler BUS Prescaler APB1.
 * @param	 : APBL_PreScalerValue
 * @param	 : It Can be APB_L_1 , APB_L_2 , APB_L_4 , APB_L_8 , APB_L_16
 * @return   : enumError_t, Error status indicating the success or failure of setting prescaler value.
 */
enumError_t RCC_Config_APBL_BusPrescaler (u32  APBL_PreScalerValue)
{
	enumError_t Ret_ErrorStatus = Nok;

	/* Check if the provided PreScaler Value is valid */
	if(APBL_PreScalerValue!=APB_L_1 && APBL_PreScalerValue!= APB_L_2 && APBL_PreScalerValue != APB_L_4 && APBL_PreScalerValue!=APB_L_8 && APBL_PreScalerValue!=APB_L_16 )
	{
		Ret_ErrorStatus = WrongInput;
	}
	else
	{
		 Ret_ErrorStatus = Ok;

		u32 loc_CFGR_Temp = RCC->RCC_CFGR ;
		loc_CFGR_Temp &= APBL_PRE_CLR_MASK; 		/* Clear the bits*/
		loc_CFGR_Temp |= APBL_PreScalerValue;		/* Set the bits for the APB HighBus PreScaler Value*/
		RCC->RCC_CFGR = loc_CFGR_Temp;		/* ReAllocate Temp to CFGR register with the new PreScaler Value*/
	}

	return Ret_ErrorStatus;
}

/*
 * @brief    : Configure AHB prescalerr BUS Prescaler AHB.
 * @param	 : AHB_PreScalerValue
 * @param	 : It Can be AHB_1 ,AHB_2 ,AHB_4 , AHB_8 , AHB_16 , AHB_64 , AHB_128 , AHB_256 , AHB_512
 * @return   : enumError_t, Error status indicating the success or failure of setting prescaler value.
 */
enumError_t RCC_Config_AHB_BusPrescaler (u32  AHB_PreScalerValue)
{
	enumError_t Ret_ErrorStatus = Nok;

	/* Check if the provided PreScaler Value is valid */
	if(AHB_PreScalerValue != AHB_1 && AHB_PreScalerValue != AHB_2 && AHB_PreScalerValue != AHB_4 && AHB_PreScalerValue != AHB_8 && AHB_PreScalerValue != AHB_16 && AHB_PreScalerValue != AHB_64 && AHB_PreScalerValue != AHB_128 && AHB_PreScalerValue != AHB_256 && AHB_PreScalerValue != AHB_512)
	{
		Ret_ErrorStatus = WrongInput;
	}
	else
	{
		 Ret_ErrorStatus = Ok;

		u32 loc_CFGR_Temp = RCC->RCC_CFGR ;
		loc_CFGR_Temp &= AHB_PRE_CLR_MASK; 		/* Clear the bits*/
		loc_CFGR_Temp |= AHB_PreScalerValue;	/* Set the bits for the AHB PreScaler Value*/
		RCC->RCC_CFGR = loc_CFGR_Temp;		/* ReAllocate Temp to CFGR register with the new PreScaler Value*/
	}
	return Ret_ErrorStatus;
}


/*
 * @brief    : Enable AHB1 Peripheral.
 * @param	 : AHB1_PeripheralName, The AHB1 peripheral to be enabled.
 * @return   : enumError_t Error status indicating the success or failure of enabling the AHB1 peripheral.
 * @details  : This function enables the specified peripheral connected to the AHB1 bus.
 * @note     : AHB1 Peripherals are AHB1_ GPIO A,B,C,D,E,H , CRC , DMA1,2
 */
enumError_t RCC_Enable_AHB1_Peripheral(u32 AHB1_PeripheralName)
{
	enumError_t Ret_ErrorStatus = Ok;

	u32 loc_AHB1ENR_Temp = RCC->RCC_AHB1ENR ;

	loc_AHB1ENR_Temp &= ~(AHB1_PeripheralName); /* Clear the bits*/
	loc_AHB1ENR_Temp |= AHB1_PeripheralName;	/* Set the bits for the AHB1  selected Peripheral*/
	RCC->RCC_AHB1ENR = loc_AHB1ENR_Temp;		/* ReAllocate Temp Back to AHB1ENR register with the new Value*/

	return Ret_ErrorStatus;
}

/*
 * @brief    : Disable AHB1 Peripheral.
 * @param 	 : AHB1_PeripheralName The AHB1 peripheral to be disabled.
 * @return   : enumError_t Error status indicating the success or failure of disabling the AHB1 peripheral.
 * @details  : This function disables the specified peripheral connected to the AHB1 bus.
 * @note     : AHB1 Peripherals are AHB1_ GPIO A,B,C,D,E,H , CRC , DMA1,2
 */
enumError_t RCC_Disable_AHB1_Peripheral(u32 AHB1_PeripheralName)
{
	enumError_t Ret_ErrorStatus = Ok;

	u32 loc_AHB1ENR_Temp = RCC->RCC_AHB1ENR ;

	loc_AHB1ENR_Temp &= ~(AHB1_PeripheralName); /* Clear the bits*/
	RCC->RCC_AHB1ENR = loc_AHB1ENR_Temp;		/* ReAllocate Temp Back to AHB1ENR register with the new Value*/

	return Ret_ErrorStatus;
}

/*
 * @brief    : Enable AHB2 Peripheral.
 * @param	 : AHB2_PeripheralName, The AHB2 peripheral to be enabled.
 * @return   : enumError_t Error status indicating the success or failure of enabling the AHB2 peripheral.
 * @details  : This function enables the specified peripheral connected to the AHB2 bus.
 * @note     : AHB2 Peripherals are AHB2_OTGFS
 */
enumError_t RCC_Enable_AHB2_Peripheral(u32 AHB2_PeripheralName)
{
	enumError_t Ret_ErrorStatus = Nok;
	if(AHB2_PeripheralName != AHB2_OTGFS)
	{
		Ret_ErrorStatus= WrongInput;
	}

	else
	{
		 Ret_ErrorStatus = Ok;

		u32 loc_AHB2ENR_Temp = RCC->RCC_AHB2ENR ;

		loc_AHB2ENR_Temp &= ~(AHB2_PeripheralName); /* Clear the bits*/
		loc_AHB2ENR_Temp |= AHB2_PeripheralName; 	/* Setting the bits*/
		RCC->RCC_AHB2ENR = loc_AHB2ENR_Temp;		/* ReAllocate Temp Back to AHB2ENR register with the new Value*/
	}
	return Ret_ErrorStatus;
}

/*
 * @brief    : Disable AHB2 Peripheral.
 * @param 	 : AHB2_PeripheralName The AHB1 peripheral to be disabled.
 * @return   : enumError_t Error status indicating the success or failure of disabling the AHB2 peripheral.
 * @details  : This function disables the specified peripheral connected to the AHB2 bus.
 * @note     : AHB2 Peripherals are AHB2_OTGFS
 */
enumError_t RCC_Disable_AHB2_Peripheral(u32 AHB2_PeripheralName)
{
	enumError_t Ret_ErrorStatus = Nok;

	if(AHB2_PeripheralName != AHB2_OTGFS)
	{
		Ret_ErrorStatus= WrongInput;
	}

	else
	{
		 Ret_ErrorStatus = Ok;

		u32 loc_AHB2ENR_Temp = RCC->RCC_AHB2ENR ;

		loc_AHB2ENR_Temp &= ~(AHB2_PeripheralName); /* Clear the bits*/
		RCC->RCC_AHB2ENR = loc_AHB2ENR_Temp;		/* ReAllocate Temp Back to AHB2ENR register with the new Value*/
	}
	return Ret_ErrorStatus;
}


/*
 * @brief    : Enable APB1 Peripheral.
 * @param	 : APB1_PeripheralName, The APB1 peripheral to be enabled.
 * @return   : enumError_t , Error status indicating the success or failure of enabling the APB1 peripheral.
 * @details  : This function enables the specified peripheral connected to the APB1 bus.
 * @note     : APB1 Peripherals are APB1_ TIM 2,3,4,5 , APB1_WWDG , APB1_ SPI2,3 ,APB1_USART2 , APB1_ I2C1,2,3 , APB1_PWR
 */
enumError_t RCC_Enable_APB1_Peripheral(u32 APB1_PeripheralName)
{
	enumError_t Ret_ErrorStatus = Ok;

	u32 loc_APB1ENR_Temp = RCC->RCC_APB1ENR ;

	loc_APB1ENR_Temp &= ~(APB1_PeripheralName); /* Clear the bits*/
	loc_APB1ENR_Temp |= APB1_PeripheralName; 	/* Setting the bits*/
	RCC->RCC_APB1ENR = loc_APB1ENR_Temp;		/* ReAllocate Temp Back to APB1ENR register with the new Value*/

	return Ret_ErrorStatus;

}

/*
 * @brief    : Disable APB1 Peripheral.
 * @param	 : APB1_PeripheralName, The APB1 peripheral to be disabled.
 * @return   : enumError_t Error status indicating the success or failure of disabling the APB1 peripheral.
 * @details  : This function disables the specified peripheral connected to the APB1 bus.
 * @note     : APB1 Peripherals are APB1_ TIM 2,3,4,5 , APB1_WWDG , APB1_ SPI2,3 ,APB1_USART2 , APB1_ I2C1,2,3 , APB1_PWR
 */
enumError_t RCC_Disable_APB1_Peripheral(u32 APB1_PeripheralName)
{
	enumError_t Ret_ErrorStatus = Ok;

	u32 loc_APB1ENR_Temp = RCC->RCC_APB1ENR ;

	loc_APB1ENR_Temp &= ~(APB1_PeripheralName); /* Clear the bits*/
	RCC->RCC_APB1ENR = loc_APB1ENR_Temp;		/* ReAllocate Temp Back to APB1ENR register with the new Value*/

	return Ret_ErrorStatus;

}


/*
 * @brief    : Enable APB2 Peripheral.
 * @param	 : APB2_PeripheralName. The APB2 peripheral to be enabled.
 * @return   : enumError_t, Error status indicating the success or failure of enabling the APB2 peripheral.
 * @details  : This function enables the specified peripheral connected to the APB2 bus.
 * @note     : APB2 Peripherals are APB2_TIM1 , APB2_USART1,6 , APB2_ADC1 , APB2_SDIO , APB2_SPI1,4 , APB2_SYSCFG , APB2_TIM9,10,11
 */
enumError_t RCC_Enable_APB2_Peripheral(u32 APB2_PeripheralName)
{
	enumError_t Ret_ErrorStatus = Ok;

	u32 loc_APB2ENR_Temp = RCC->RCC_APB2ENR ;

	loc_APB2ENR_Temp &= ~(APB2_PeripheralName); /* Clear the bits*/
	loc_APB2ENR_Temp |= APB2_PeripheralName; 	/* Setting the bits*/
	RCC->RCC_APB2ENR = loc_APB2ENR_Temp;		/* ReAllocate Temp Back to APB2ENR register with the new Value*/

	return Ret_ErrorStatus;
}

/*
 * @brief    : Disable APB2 Peripheral.
 * @param	 : APB2_PeripheralName .The APB2 peripheral to be disabled.
 * @return   : enumError_t, Error status indicating the success or failure of disabling the APB2 peripheral.
 * @details  : This function disables the specified peripheral connected to the APB2 bus.
 * @note     : APB2 Peripherals are APB2_TIM1 , APB2_USART1,6 , APB2_ADC1 , APB2_SDIO , APB2_SPI1,4 , APB2_SYSCFG , APB2_TIM9,10,11
 */
enumError_t RCC_Disable_APB2_Peripheral(u32 APB2_PeripheralName)
{
	enumError_t Ret_ErrorStatus = Ok;

	u32 loc_APB2ENR_Temp = RCC->RCC_APB2ENR ;

	loc_APB2ENR_Temp &= ~(APB2_PeripheralName); /* Clear the bits*/
	RCC->RCC_APB2ENR = loc_APB2ENR_Temp;		/* ReAllocate Temp Back to APB2ENR register with the new Value*/

	return Ret_ErrorStatus;

}
