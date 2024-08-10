 /******************************************************************************
 *
 * File Name: Motor.c
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/

#include "gpio.h"
#include "timer0.h"
#include <avr/io.h>
#include "motor.h"
#include "std_types.h"

void DcMotor_Init(void){

	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
	Timer0_PWM_Init(0);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	PORTB= (PORTB & 0b11111100) | (state & 0b00000011);
	Timer0_PWM_Init(speed);
}
