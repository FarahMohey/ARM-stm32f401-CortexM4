/*
 ============================================================================
 Name        : Scheduler.h
 Author      : Farah Mohey
 Description : Header file for Scheduler
 Created	 : 12-Apr-24
 ============================================================================
 */


#ifndef SERVICE_SCHEDULER_H_
#define SERVICE_SCHEDULER_H_


/******************************** Includes ************************************/
#include "LIB/Std_Types.h"
#include "LIB/Masks.h"
#include "LIB/Errors_enum.h"
#include "MCAL/STK.h"
#include "CFG/RunnablesList_Cfg.h"

/***************************** Definitions *************************************/
#define TICK_TIME_MS 2

/***************************** Types Declaration *******************************/

/*Pointer to function --> To set the runnable or call by it */
typedef void (*RunnableCB_t)(void);

/*Structure to hold information about each runnable task.*/
/* User Configured info */
typedef struct
{

	char   *Name;		 /* Name or ID of the runnable task */
	u32    PeriodicityMs;	    /* Periodicity of the task in milliseconds */
	u32    DelayTimeMs;
	RunnableCB_t	cb;		    /* Callback function for the task */

} Runnable_t;

/**************************Functions Prototypes ******************************/

/*
 * @brief    : Initializes the scheduler.
 * @param[in]: None.
 * @return   : enumError_t - Error status indicating success or failure.
 * @details  : Initializes the scheduler by configuring the system timer and setting the tick time.
 */
enumError_t Sched_Init(void);


/*
 * @brief    : Starts the scheduler.
 * @param[in]: None.
 * @return   : enumError_t - Error status indicating success or failure of starting the scheduler.
 * @details  : Starts the scheduler by enabling the system timer interrupts
 * 				& Entering an infinite loop where it checks for pending ticks & Executes the scheduler function accordingly
 *             	  Task should be created between Init and start.
 */
enumError_t Sched_Start(void);


#endif /* SERVICE_SCHEDULER_H_ */















