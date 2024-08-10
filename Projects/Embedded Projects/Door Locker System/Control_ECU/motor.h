 /******************************************************************************
 *
 * File Name: Motor.h
 *
 * Description: Header file for the application
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/


#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"

typedef enum
{
	STOP,CW,A_CW
}DcMotor_State;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif
