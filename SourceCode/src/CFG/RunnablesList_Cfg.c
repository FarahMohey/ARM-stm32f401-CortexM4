/*
 ============================================================================
 Name        : Scheduler_Cfg.c
 Author      : Farah Mohey
 Description : Source File for Configuring the LCD Driver (for STM32F401xC)
 Created	 : 12-Apr-24
 ============================================================================
 */

/******************************* Includes **************************************/

#include "CFG/RunnablesList_Cfg.h"
#include "Service\Scheduler.h"

/*************************** Functions Prototypes *******************************/

/*
extern void Runnable_Toggle_Led1(void) ;
extern void Runnable_Toggle_Led2(void) ;
extern void HSwitch_Runnable(void) ;
extern void Runnable_APP3(void);
extern void  Traffic_Runnable(void);
extern void LCD_Runnable(void) ;
*/

/***************************** Implementation **********************************/

/*Global array to set RunnablesList configuration */
const  Runnable_t RunnableList[_MaxRunnables] =
{
   /*Ex : Set RunnableList1 Configuration*/
  //  [SWITCH] = {.Name = "SwitchRunnable", .PeriodicityMs = 5,  .cb = HSwitch_Runnable , .DelayTimeMs = 0},
    //[app3] = {.Name = "ToggleLedbySwitch", .PeriodicityMs = 150,  .cb = Runnable_APP3 , .DelayTime = 0}
    // [app1] = {.Name = "ToggleLed1", .PeriodicityMs = 20,  .cb = Runnable_Toggle_Led1 , .DelayTime = 1000},
    // [app2] = {.Name = "ToggleLed2", .PeriodicityMs = 10,  .cb = Runnable_Toggle_Led2 , .DelayTime = 0},
    //[Traffic] = {.Name = "TrafficLight", .PeriodicityMs = 2000,  .cb = Traffic_Runnable , .DelayTime = 0},
    //[LCD] = {.Name = "LCD", .PeriodicityMs = 2,  .cb = LCD_Runnable , .DelayTime = 0},
  //  [LCDTest]={.Name = "LCDTest", .PeriodicityMs = 1000,  .cb =LCDTest_Runnable , .DelayTime = 20}
};
