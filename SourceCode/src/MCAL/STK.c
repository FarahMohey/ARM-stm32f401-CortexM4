/*
 ============================================================================
 Name        : STK.c
 Author      : Farah Mohey
 Description : Source file for STK ( SysTick for STM32F401xC)
 Created	 : 29-Mar-24
 ============================================================================
 */

/******************************** Includes **************************************/
#include "MCAL/STK.h"

/***************************** Definitions *************************************/
#define STK_BASE_ADDRESS        0xE000E010

#define STK_START_STOP_MASK     BIT0_MASK		/*Bit0 = 1*/
#define STK_MODE_CLR_MASK       0xFFFFFFF9		/*Bit1 = 0 , Bit2= 0*/
#define CLK_SRC_MASK            BIT2_MASK		/*Bit2 = 1 */

/*Range of SYSTICK 0-->24 , 2 pwr 24 = 16 million */
#define RELOAD_MIN_TIME     BIT0_MASK		/*Bit0 = 1*/
#define RELOAD_MAX_TIME     0x00FFFFFF		/*from bit 0- 24 =1 */

#define MICRO_TO_MILLI     1000
#define N_COUNT            1

/**************************** Types Declaration ********************************/
typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
} STK_PERI_t;


/****************************** Variables **************************************/

/* Pointer to the SysTick peripheral structure */
volatile STK_PERI_t *const STK = (volatile STK_PERI_t *) STK_BASE_ADDRESS;

/* Callback function pointer for SysTick interrupt */
static STK_CBF_t APP_CBF = NULL_PTR ;


/***************************** Implementation **********************************/

/*
 * @brief   : Starts the SysTick timer.
 * @param   : None
 * @return  : enumError_t - Indicating Status of the operation if Success or Failure
 * @details : This function starts the SysTick timer to generate interrupts according to the configured time interval.
 */
enumError_t STK_Start(void)
{
	/*Variable to store error status to be returned at the end of the function */
	u32 Ret_ErrorStatus = Nok;

	/* when ENABLE is set to 1,
	 * the counter loads the RELOAD value from the LOAD register and then counts down
	 */

	/* Store the current value of STK_CTRL register in Temp Variable to keep its value
	 * SET the start bit in CTRL Register by | with STK_START_STOP_MASK  0x00000001
	 * Re-Assign modified value back to CTRL Register
	 */

	u32 loc_Temp_Start = STK->STK_CTRL ;
	loc_Temp_Start |= STK_START_STOP_MASK;
	STK->STK_CTRL = loc_Temp_Start;

	/*Setting error status to OK after setting the enable in CTRL Register */
	Ret_ErrorStatus= Ok;

	return Ret_ErrorStatus;
}


/*
 * @brief   : Stops the SysTick timer.
 * @param   : None
 * @return  : Error status indicating success or failure.
 * @details : This function stops the SysTick timer from generating interrupts.
 */
enumError_t STK_Stop(void)
{
	/*Variable to store error status to be returned at the end of the function */
	u32 Ret_ErrorStatus = Nok;

	/*0 --> Counter disabled*/

	/* Store the current value of STK_CTRL register in Temp Variable to keep its value
	 * CLEAR the start bit in CTRL Register by & with ~ STK_START_STOP_MASK  0x00000001
	 * Re-Assign modified value back to CTRL Register
	 */
	u32 loc_Temp_Stop = STK->STK_CTRL ;
	loc_Temp_Stop &= ~(STK_START_STOP_MASK);
	STK->STK_CTRL =loc_Temp_Stop;

	/*Setting error status to OK after setting the enable in CTRL Register */
	Ret_ErrorStatus= Ok;

	return Ret_ErrorStatus;
}


/*
 * @brief   : Sets the configuration of the SysTick timer.
 * @param   : Mode - The mode to configure the SysTick timer.
 * @param	: Mode can be --> STK_AHB_8_DIS_INT ,  STK_AHB_DIS_INT
 * 							  STK_AHB_8_ENB_INT ,  STK_AHB_ENB_INT
 * @return  : enumError_t - Indicating Status of the operation if Success or Failure
 * @details : This function configures the SysTick timer according to the provided mode.
 */
enumError_t STK_SetConfig(u32 Mode)
{
	/*Variable to store error status to be returned at the end of the function */
	u32 Ret_ErrorStatus = Nok;

	/*Check if user entered a valid mode */
	if ( (Mode !=STK_AHB_8_ENB_INT ) && (Mode != STK_AHB_8_DIS_INT ) && (Mode != STK_AHB_DIS_INT) && (Mode != STK_AHB_ENB_INT) )
	{
		Ret_ErrorStatus = WrongInput ;

	}

	/* Store the current value of STK_CTRL register in Temp Variable to keep its value
	 * SET the bit2 = CLKSOURCE & bit1 = TICKINT in CTRL Register by | with Mode
	 * Re-Assign modified value back to CTRL Register
	 */
	else
	{
		u32 loc_Temp_Config = STK->STK_CTRL;
		loc_Temp_Config &= (STK_MODE_CLR_MASK);
		loc_Temp_Config |= Mode ;
		STK->STK_CTRL = loc_Temp_Config ;

		/*Setting error status to OK after setting the Mode in CTRL Register */
		Ret_ErrorStatus = Ok;
	}

	return Ret_ErrorStatus;
}


/*
 * @brief   : Sets the time interval for the SysTick timer.
 * @param   : TimeMs - The time interval in milliseconds.
 * @return  : Error status indicating success or failure.
 * @details : This function sets the time interval for the SysTick timer,
 * 				which determines the period between interrupts generated by the timer.
 */
enumError_t STK_SetTimeMs(u32 TimeMs)
{
	u32 Ret_ErrorStatus = Nok;

	/* Calculate the microcontroller clock in Micro */
	u32 MicroClk = 0;
	if ( (STK->STK_CTRL) & (CLK_SRC_MASK) )
	{
		/*  Bit 2 CLKSOURCE: Clock source selection
			1: Processor clock (AHB) */
		MicroClk = CLK_FREQUENCY_MHZ;
	}
	else
	{
		/*  Bit 2 CLKSOURCE: Clock source selection
			0: AHB/8   */

		MicroClk = CLK_FREQUENCY_MHZ/8;
	}


	/* Calculate the reload value for the given time interval */

	/* Convert Clk from Micro to Milli --> MicroClk / MICRO_TO_MILLI
	 * Multiplying Clk after conversion with Required Time set by user --> * TimeMs
	 * Use a RELOAD value of N-1.
	 * For example, if the SysTick interrupt is required every 100 clock pulses, set RELOAD to 99
	 * Then -1 --> N_COUNT
	 */

	u32 Temp_Load = ( (MicroClk/ MICRO_TO_MILLI) * TimeMs ) - N_COUNT ;


	/* Check if the provided time interval is within the valid range */
	/*Range of SYSTICK 0-->24 , 2 pwr 24 = 16 million */
	if (Temp_Load < RELOAD_MIN_TIME || Temp_Load > RELOAD_MAX_TIME)
	{
		Ret_ErrorStatus = WrongInput;
	}

	else
	{
		/* Set the reload value and clear the current value in VAL register to avoid and corruption from old values */

		STK->STK_LOAD = Temp_Load;
		STK->STK_VAL = 0;

		Ret_ErrorStatus = Ok;
	}

	/* Return the error status */
	return Ret_ErrorStatus;
}


/*
 * @brief   : Get Current Value of VAL Register - Remaining Time for SYSTICK.
 * @param   : *Curr_Val - Pointer to access register and store in it the value.
 * @return  : enumError_t - Indicating Status of the operation if Success or Failure
 */
enumError_t STK_GET_CurrentVal(u32 *Curr_Val)
{
	u32 Ret_ErrorStatus = Nok;

	/*Checking if the pointer is null pointer */
	if (Curr_Val == NULL_PTR)
	{
		Ret_ErrorStatus = NullPointer;
	}

	/*Storing the value of VAL register in Cur_Val*/
	else
	{
		*Curr_Val = STK->STK_VAL;
		Ret_ErrorStatus = Ok;
	}

	return Ret_ErrorStatus ;

}


/*
 * @brief   : Sets the callback function for the SysTick timer interrupt.
 * @param   : CallBack - Pointer to the callback function.
 * @return  : Error status indicating success or failure.
 * @details : This function sets the callback function to be called when the SysTick timer generates an interrupt.
 * 				The callback function will be executed each time the timer generates an interrupt.
 */
enumError_t STK_SetCallBack(STK_CBF_t CallBack)
{
	u32 Ret_ErrorStatus = Nok;

	/*Checking if the pointer is null pointer */
	if (CallBack == NULL_PTR)
	{
		Ret_ErrorStatus = NullPointer;
	}


	else
	{
		APP_CBF = CallBack;
		Ret_ErrorStatus = Ok;

	}

	return Ret_ErrorStatus;
}


/*
 * @brief   : SysTick interrupt handler.
 * @param   : None
 * @return  : None
 * @details : This function is the interrupt handler for the SysTick timer interrupt.
 *            It checks if a callback function (APP_CBF) is registered and calls it
 *            if it exists. This function is typically called every time the SysTick
 *            timer generates an interrupt.
 */
void SysTick_Handler(void)
{
	/* Check if a callback function is registered */
if (APP_CBF)
{
    /* Call the registered callback function */
    APP_CBF();
}
}
