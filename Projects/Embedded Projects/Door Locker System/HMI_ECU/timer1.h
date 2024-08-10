/******************************************************************************
 *
 * File Name: Timer1.h
 *
 * Description: Header file for the application
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/


#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

typedef enum
{
    NO_CLK,CLK_1,CLK_8,CLK_64,CLK_256,CLK_1024,EXTERNAL_CLK_FALLING_EDGE,EXTERNAL_CLK_RAISING_EDGE
}Timer1_Prescaler;

typedef enum
{
	Normal_mode,Compare_Mode
}Timer1_Mode;

typedef struct {
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));

#endif
