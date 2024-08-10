 /******************************************************************************
 *
 * File Name: Buzzer.c
 *
 * Description: Source file for Buzzer
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/

#include "gpio.h"
#include "buzzer.h"

/* initials Buzzer  */
void BUZZER_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,BUZZER_OFF);
}

/* Activate Buzzer  */
void BUZZER_on(void) {
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,BUZZER_ON);
}

/* stop Buzzer  */
void BUZZER_off(void) {
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,BUZZER_OFF);
}
