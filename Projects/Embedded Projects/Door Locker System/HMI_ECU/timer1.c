/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.c
 *
 * Description: Source file for the Timer1 driver
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/

#include "timer1.h"
#include "std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/*
 * Function to initials Timer1
 *
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCNT1=Config_Ptr->initial_value;

	if(Config_Ptr->mode==Normal_mode)
	{
		TCCR1A=0;
		TCCR1B = (TCCR1B & 0x00) | Config_Ptr->prescaler;
		TIMSK |= (1<< TOIE1);
	}else if(Config_Ptr->mode==Compare_Mode)
	{
		OCR1A = Config_Ptr->compare_value;
		TCCR1A = (1<<FOC1A) ;
		TCCR1B =(TCCR1B & 0x00) | (1<< WGM12) | Config_Ptr->prescaler ;
		TIMSK |= (1<< OCIE1A);
	}

}

/*
 * Function to Stops Timer1
 *
 */
void Timer1_deInit(void){
	TCCR1B &= 0xf8;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
