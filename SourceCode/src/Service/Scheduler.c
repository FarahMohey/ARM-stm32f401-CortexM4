/*
 ============================================================================
 Name        : Scheduler.c
 Author      : Farah Mohey
 Description : Source file for Scheduler
 Created	 : 12-Apr-24
 ============================================================================
 */

/********************************* Includes **************************************/
#include "Service/Scheduler.h"

/***************************** Types Declaration **********************************/

/*Any info or new feature developer needs to add to the task during the run time should be configured here*/
/*User configured info + needed info during Runtime */

typedef struct
{
	const Runnable_t *runnable;
	u32 RemainingTimeMs;	/*Remaining time to execute the current task it should update automatically
	 *When the value of it reaches 0 --> this the time to execute the task
	 *Then should reset by PeriodicityMs value*/
} RunnableInfo_t;


/****************************** Variables *************************************/

extern const  Runnable_t RunnableList[_MaxRunnables];
static volatile u32 PendingTicks;
static RunnableInfo_t RunnableInfoList[_MaxRunnables];


/************************ Static Function Prototypes ***************************/

static void Sched(void);
static void Tickcb(void);

/***************************** Implementation **********************************/

/*
 * @brief    : Initializes the scheduler.
 * @param[in]: None.
 * @return   : enumError_t - Error status indicating success or failure.
 * @details  : Initializes the scheduler by configuring the system timer and setting the tick time.
 */
enumError_t Sched_Init(void)
{
	/*Variable to store error status to be returned at the end of the function */
	u32 Ret_ErrorStatus = Nok;

	/*Configure Systick */
	STK_SetConfig(STK_AHB_ENB_INT);
	STK_SetTimeMs(TICK_TIME_MS);
	STK_SetCallBack(Tickcb);

	/* Loop to fill struct RunnableInfoList with values of struct RunnableList
	 * & Initiate the remaining time with DelayTimeMs
	 */
	u8 loc_idx;
	for (loc_idx=0 ; loc_idx < _MaxRunnables ; loc_idx++ )
	{
		if(RunnableInfoList[loc_idx].runnable == NULL_PTR)
		{
			RunnableInfoList[loc_idx].runnable = &RunnableList[loc_idx];
			RunnableInfoList[loc_idx].RemainingTimeMs = RunnableInfoList[loc_idx].runnable->DelayTimeMs;
			Ret_ErrorStatus = Ok;
		}
		/*empty else */
		else
		{
		}
	}
	return Ret_ErrorStatus;
}

/*
 * @brief    : Starts the scheduler.
 * @param[in]: None.
 * @return   : enumError_t - Error status indicating success or failure of starting the scheduler.
 * @details  : Starts the scheduler by enabling the system timer interrupts
 * 				& Entering an infinite loop where it checks for pending ticks & Executes the scheduler function accordingly
 *             	  Task should be created between Init and start.
 */
enumError_t Sched_Start(void)
{
	/*Variable to store error status to be returned at the end of the function */
	u32 Ret_ErrorStatus = Nok;

	STK_Start();
	 /* Enter infinite loop for scheduler operation */
	 while (1)
	 {
		 if (PendingTicks)
		 {
			 PendingTicks -- ;
			 Sched();

			 Ret_ErrorStatus = Ok;
		 }
	 }

	return Ret_ErrorStatus;
}


/************************ Implementation of Static Functions ***************************/

/*
 * @brief    : Executes the scheduler.
 * @param[in]: None.
 * @return   : None.
 * @details  : Executes the scheduler by iterating through the list of runnables and calling their
 *             respective callback functions if the time condition is met.
 */
static void Sched(void)
{
	u32 loc_idx=0;
	for(loc_idx=0 ; loc_idx < _MaxRunnables ; loc_idx++)
	{
	  /* Checking that Callback equal value != nullptr && Remaining time == 0 --> time for this runnable to be executed */
		if ( (RunnableInfoList[loc_idx].runnable->cb) && (RunnableInfoList[loc_idx].RemainingTimeMs==0) )
		{
			/*  Calling the Call back function of this runnable
			 * &Setting the remaining time by the periodicity time of this runnable */
			RunnableList[loc_idx].cb();
			RunnableInfoList[loc_idx].RemainingTimeMs = RunnableInfoList[loc_idx].runnable->PeriodicityMs;

		}
		RunnableInfoList[loc_idx].RemainingTimeMs -= TICK_TIME_MS ;
	}
}


/*
 * @brief    : Callback function for system timer interrupts.
 * @param[in]: None.
 * @return   : None.
 * @details  : Increments the pending ticks counter upon system timer interrupt.
 */
static void Tickcb(void)
{

	PendingTicks++;
}


