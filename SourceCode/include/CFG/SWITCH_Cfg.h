/*
 ============================================================================
 Name        : SWITCH_Cfg.h
 Author      : Farah Mohey
 Description : Header File for Configuring the SWITCH Driver (for STM32F401xC)
 Created	 : 12-Apr-24
 ============================================================================
 */


#ifndef CFG_SWITCH_CFG_H_
#define CFG_SWITCH_CFG_H_


/**************************		Types Declaration	 ******************************/
/* Configure The Switches number in this Enum */
typedef enum
{
	Switch1,
	Switch2,
	Switch3,

	/*Indicate number of switches, don't use it */
    _Switch_Num
}SWITCHES_t;



#endif /* CFG_SWITCH_CFG_H_ */
