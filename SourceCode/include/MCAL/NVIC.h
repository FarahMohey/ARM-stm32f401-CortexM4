/*
 ============================================================================
 Name        : NVIC.h
 Author      : Farah Mohey
 Description : Header file for NVIC (Nested vectored interrupt controller for STM32F401xC)
 Created	 : 27-Mar-24
 ============================================================================
 */

#ifndef MCAL_NVIC_H_
#define MCAL_NVIC_H_

/******************************* Includes *************************************/
#include "LIB/Std_Types.h"
#include "LIB/Masks.h"
#include "LIB/Errors_enum.h"
#include "LIB/STM32F401CC_IRQs.h"

/******************************** Definitions *********************************/
#define PRIORITY_GROUP0		0x05FA0000 /*[4] bits Preempt Group &  [0] bits Subpriority Group*/
#define PRIORITY_GROUP1		0x05FA0400 /*[3] bits Preempt Group &  [1] bits Subpriority Group*/
#define PRIORITY_GROUP2		0x05FA0500 /*[2] bits Preempt Group &  [2] bits Subpriority Group*/
#define PRIORITY_GROUP3		0x05FA0600 /*[1] bits Preempt Group &  [3] bits Subpriority Group*/
#define PRIORITY_GROUP5		0x05FA0700 /*[0] bits Preempt Group &  [4] bits Subpriority Group*/

/*************************** Functions Prototypes *****************************/

/*
 * @brief    : Enable NVIC IRQ
 * @param[in]: IRQn - Interrupt number
 * @return   : enumError_t - Indicating Status of the operation
 * @details  : Enables the specified NVIC interrupt.
 */
enumError_t NVIC_Enable_IRQ (IRQn_t IRQn);

/*
 * @brief    : Disable NVIC IRQ
 * @param[in]: IRQn - Interrupt number
 * @return   : enumError_t - Indicating Status of the operation
 * @details  : Disables the specified NVIC interrupt.
 */
enumError_t NVIC_Disable_IRQ(IRQn_t IRQn);

/*
 * @brief    : Set NVIC Pending IRQ
 * @param[in]: IRQn - Interrupt number
 * @return   : enumError_t - Indicating Status of the operation
 * @details  : Sets the specified NVIC interrupt as pending.
 */
enumError_t NVIC_SetPending_IRQ(IRQn_t IRQn);

/*
 * @brief    : Clear NVIC Pending IRQ
 * @param[in]: IRQn - Interrupt number
 * @return   : enumError_t - Indicating Status of the operation
 * @details  : Clears the pending status of the specified NVIC interrupt.
 */
enumError_t NVIC_ClearPending_IRQ(IRQn_t IRQn);

/*
 * @brief    : Get NVIC Pending IRQ status
 * @param[in]: IRQn - Interrupt number
 * @param[in]: *Ptr_IRQ - Pointer to store the status
 * @return   : enumError_t - Indicating Status of the operation
 * @details  : Retrieves the pending status of the specified NVIC interrupt.
 */
enumError_t NVIC_GetPending_IRQ(IRQn_t IRQn, u8 *Ptr_IRQ);

/*
 * @brief    : Get NVIC Active IRQ status
 * @param[in]: IRQn - Interrupt number
 * @param[in]: *Ptr_IRQ - Pointer to store the status
 * @return   : enumError_t - Indicating Status of the operation
 * @details  : Retrieves the active status of the specified NVIC interrupt.
 */
enumError_t NVIC_GetActive_IRQ(IRQn_t IRQn, u8 *Ptr_IRQ);

/*
 * @brief    : Set Interrupt Priority
 * @param[in]: IRQn - Interrupt number
 * @param[in]: PreemptGroup - Preemption priority group
 * @param[in]: SubpriorityGroup - Subpriority group
 * @param[in]: GroupPriority - Group priority value
 * @return   : enumError_t - Indicating Status of the operation
 * @details  : Sets the priority level for the specified NVIC interrupt.
 */
enumError_t NVIC_SetPriority(IRQn_t IRQn, u8 PreemptGroup ,u8 SubpriorityGroup ,u32 GroupPriority );

/*
 * @brief    : Get Interrupt Priority
 * @param[in]: IRQn - Interrupt number
 * @param[in]: Ptr_priorityLEV - Pointer to store the priority level
 * @return   : enumError_t - Indicating Status of the operation
 * @details  : Retrieves the priority level of the specified NVIC interrupt.
 */
enumError_t NVIC_GetPriority(IRQn_t IRQn, u8 *Ptr_priorityLEV);


/*
 * @brief    : Generate a Software  Interrupt
 * @param[in]: IRQn - Interrupt number
 * @return   : enumError_t - Indicating Status of the operation
 * @details  : The value to be written is the Interrupt ID of the required SGI, in the range 0-239.
 * 				For example, a value of 0x03 specifies interrupt IRQ3.
 */
enumError_t NVIC_SetSoftware_Interrupt(IRQn_t IRQn);

#endif /* MCAL_NVIC_H_ */


