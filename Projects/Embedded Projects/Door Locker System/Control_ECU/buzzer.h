 /******************************************************************************
 *
 * File Name: Buzzer.h
 *
 * Description: Header file for the application
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/


#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
#include "gpio.h"

#define BUZZER_PORT PORTA_ID
#define BUZZER_PIN  PIN0_ID
#define BUZZER_ON   1
#define BUZZER_OFF  0


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void BUZZER_init(void);
void BUZZER_on(void);
void BUZZER_off(void);

#endif
