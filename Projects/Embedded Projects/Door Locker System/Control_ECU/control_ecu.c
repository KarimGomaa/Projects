/******************************************************************************
 *
 * Module: MicroController 1
 *
 * File Name: control_ecu.c
 *
 * Description: Source file for MicroController 1 Application for DOOR PASSWORD
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/

#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include "timer1.h"
#include "uart.h"
#include "buzzer.h"
#include "twi.h"
#include "external_eeprom.h"
#include "motor.h"
#include "timer0.h"
#include <util/delay.h>
#include <avr/io.h>

#define MC1_READY                                 0x10  /* Macro to be sent by MC1 to MC2  */
#define MC2_READY                                 0x11  /*  Macro to be sent to MC2 */
#define RECIEVED                                  0x20 /* Macro to confirm receiving password1 or ande used in other resiving password  */
#define RECIEVED2                                 0x30 /* Macro to confirm receiving password2 by MC2   */
#define ADDRESS_OF_PASSWORD                       0x0030 /* Adress of password in EEPROM */
#define ADDRESS_OF_FLAG                           0x0111  /* Adress of flag in EEPROM */
#define NOT_FIRST_TIME                            0x06 /* To Be used in eeprom as a flag that there is a password saved in it  */
#define PLEASE_CHANGE_PASSWORD                    0x44 /* MC2 sent this macro to MC1 to let him know that we are changing password   */
#define PLEASE_OPEN_DOOR                          0x33 /*  MC2 sent this macro to MC1 to let him know that we are opening the door */
#define OKAY                                      0x88 /* this is sent by MC1 to let MC2 know if the passwords are the same  */
#define NOT_OKAY                                  0x99 /* this is sent by MC1 to let MC2 know if the passwords are not the same  */
#define WE_ARE_OPENING_DOOR                       0x22 /* macro to be used in main in g_WHICH_FUNCTION */
#define WE_ARE_CHANGING_PASSWORD                  0x23 /* macro to be used in main in g_WHICH_FUNCTION */

static volatile uint8 g_Step1Done=0;  /* Step1 is done correctly  */
static volatile uint8 g_Motor_CW_Done=0; /* Used to count time 15 sec in function DcMotor_CW_Stop  */
static volatile uint8 g_Motor_STOP_Done=0; /* Used to count time 3 sec in function Motor_STOP_Done  */
static volatile uint8 g_Motor_CCW_Done=0; /* Used to count time 15 sec in function DcMotor_CCW_Stop  */
static volatile uint8 g_error_counter=0; /* to count errors and be activated after 3 times  */
static volatile uint8 g_error_time=0; /* to control timer to be 1 min  */
static volatile uint8 g_STEP2Done=0; /* step2 is done correctly */
static volatile uint8 g_WHICH_FUNCTION=0; /*used in main to know which function to be called  */

/************************************************************************************
 *
 * Function Name : Recieve_PASSWORD
 *
 * Description : Function to receive password from MC2 using UART
 *
 *************************************************************************************/

void Recieve_PASSWORD(uint8* pass1){

	while (UART_recieveByte() != MC2_READY ) {}
	UART_receiveString(pass1);
}

/************************************************************************************
 *
 * Function Name : EEPROM_SavePassword
 *
 * Description : Function to save the password in EEPROM
 *
 *************************************************************************************/

void EEPROM_SavePassword(uint8* str){
	uint8 i;
	for(i=0;i<5;i++)
	{
		EEPROM_writeByte((ADDRESS_OF_PASSWORD+i), str[i]);
		_delay_ms(10);
	}
}

/************************************************************************************
 *
 * Function Name : EEPROM_GetPassword
 *
 * Description : Function to get the password from EEPROM
 *
 *************************************************************************************/

void EEPROM_GetPassword(uint8* str){
	uint8 i;
	for(i=0;i<5;i++)
	{
		EEPROM_readByte((ADDRESS_OF_PASSWORD+i),&str[i]);
		_delay_ms(10);
	}
	str[5]='\0';
}

/************************************************************************************
 *
 * Function Name : TIMER1_Start
 *
 * Description : Fun to initials timer1 to make interrupt every 3 second
 *
 *************************************************************************************/

void TIMER1_Start(void(*a_ptr)(void)){
	Timer1_ConfigType Timer1Config;
	Timer1Config.mode=Compare_Mode;
	Timer1Config.initial_value=0;
	Timer1Config.compare_value=23439;
	Timer1Config.prescaler=CLK_1024;
	Timer1_init(&Timer1Config);
	Timer1_setCallBack(a_ptr);

}

/************************************************************************************
 *
 * Function Name : ERROR_time
 *
 * Description : Fun to Count 1 min by timer1 and disable buzzer
 *
 *************************************************************************************/

void ERROR_time(void){
	static volatile uint8 tik=0;
	/* 4 tiks to get 15 sec so 16 tik for one minute  */
	if(tik==16){
		Timer1_deInit();
		BUZZER_off();
		g_error_time=1;
	}else{
		tik++;
	}
}

/************************************************************************************
 *
 * Function Name : CHANGE_Password
 *
 * Description : Function to change old password by new one sent by MC2
 *
 *************************************************************************************/

void CHANGE_Password(){
	uint8 flag=TRUE;
	uint8 i;
	uint8 password_check[6]; /*old Password sent by MC2  */
	uint8 saved_password[6]; /* Password in EEPROM */
	uint8 changed_password[6]; /* Password sent by MC2 to be new password */

	Recieve_PASSWORD(password_check);
	UART_sendByte(RECIEVED);

	EEPROM_GetPassword(saved_password);

	/*loop to check between Password sent by MC2 and the password saved in EEPROM  */
	for(i=0;i<5;i++)
	{
		if(saved_password[i] != password_check[i])
		{
			flag=FALSE;
		}
	}
	if(flag){
		UART_sendByte(MC1_READY);
		UART_sendByte(OKAY);

		Recieve_PASSWORD(changed_password);
		UART_sendByte(RECIEVED);

		EEPROM_SavePassword(changed_password);
		_delay_ms(20);

		g_error_counter=0;
		g_STEP2Done=1;

	}else{
		UART_sendByte(MC1_READY);
		UART_sendByte(NOT_OKAY);
		g_WHICH_FUNCTION= WE_ARE_CHANGING_PASSWORD;
		g_error_counter++;
		if(g_error_counter==3)
		{
			TIMER1_Start(ERROR_time);
			BUZZER_on();
			while(!(g_error_time)) {}
			g_error_time=0;
			g_error_counter=0;
			g_STEP2Done=1;
		}
	}
}

/************************************************************************************
 *
 * Function Name : DcMotor_CW_Stop
 *
 * Description : function to stop rotation of motor after 15 sec
 *
 *************************************************************************************/

void DcMotor_CW_Stop(void){
	static volatile uint8 tik=0;
	if(tik==4){
		Timer1_deInit();
		DcMotor_Rotate(STOP,0);
		g_Motor_CW_Done=1;
	}else{
		tik++;
	}
}

/************************************************************************************
 *
 * Function Name : DcMotor_STOP_done
 *
 * Description : Function to stop the motor for 3 sec
 *
 *************************************************************************************/

void DcMotor_STOP_done(void){
	g_Motor_STOP_Done=1;
}

/************************************************************************************
 *
 * Function Name : DcMotor_CCW_Stop
 *
 * Description : function to stop rotation of motor after 15 sec
 *
 *************************************************************************************/

void DcMotor_CCW_Stop(void){
	static volatile uint8 tik=0;
	if(tik==4){
		Timer1_deInit();
		DcMotor_Rotate(STOP,0);
		g_Motor_CCW_Done=1;
	}else{
		tik++;
	}
}

/************************************************************************************
 *
 * Function Name : OPEN_DOOR
 *
 * Description : function to open door and activate error massage
 *
 *************************************************************************************/

void OPEN_DOOR(){
	uint8 flag=TRUE;
	uint8 i;
	uint8 password_check[6];
	uint8 saved_password[6];

	Recieve_PASSWORD(password_check);
	UART_sendByte(RECIEVED);

	EEPROM_GetPassword(saved_password);

	/*loop to check between Password sent by MC2 and the password saved in EEPROM  */
	for(i=0;i<5;i++)
	{
		if(saved_password[i] != password_check[i])
		{
			flag=FALSE;
		}
	}

	if(flag)
	{
		UART_sendByte(MC1_READY);
		UART_sendByte(OKAY);

		TIMER1_Start(DcMotor_CW_Stop);
		DcMotor_Rotate(CW,200);
		while(!(g_Motor_CW_Done)) {};
		g_Motor_CW_Done=0;

		TIMER1_Start(DcMotor_STOP_done);
		while(!(g_Motor_STOP_Done)) {}
		g_Motor_STOP_Done=0;

		TIMER1_Start(DcMotor_CCW_Stop);
		DcMotor_Rotate(A_CW,200);
		while(!(g_Motor_CCW_Done)) {};
		g_Motor_CCW_Done=0;

		g_error_counter=0;
		g_STEP2Done=1;

	}else{
		UART_sendByte(MC1_READY);
		UART_sendByte(NOT_OKAY);
		g_WHICH_FUNCTION= WE_ARE_OPENING_DOOR;
		g_error_counter++;
		if(g_error_counter==3)
		{
			TIMER1_Start(ERROR_time);
			BUZZER_on();
			while(!(g_error_time)) {}
			g_error_time=0;
			g_error_counter=0;
			g_STEP2Done=1;
		}
	}
}

/************************************************************************************
 *
 * Function Name : STEP2
 *
 * Description : function to guide us to OPEN DOOR OR CHANGE PASSWORD
 *
 *************************************************************************************/

void STEP2(){
	g_STEP2Done=0;
	uint8 DIRECTION;
	while(UART_recieveByte() != MC2_READY) {}
	DIRECTION=UART_recieveByte();
	if (DIRECTION == PLEASE_OPEN_DOOR)
	{
		OPEN_DOOR();

	}else if(DIRECTION == PLEASE_CHANGE_PASSWORD){
		CHANGE_Password();
	}
}

/************************************************************************************
 *
 * Function Name : STEP1
 *
 * Description : Function used at the first of runtime the program to get two password from MC2
 * and compare them then save them in EEPROM
 *
 *************************************************************************************/

void STEP1(){

	uint8 password1[6];
	uint8 password2[6];
	uint8 i;
	uint8 PASSWORD_FLAG=TRUE;

	Recieve_PASSWORD(password1);
	UART_sendByte(RECIEVED);

	Recieve_PASSWORD(password2);
	UART_sendByte(RECIEVED2);

	/*loop to check the two Passwords sent by MC2 */
	for(i=0;i<5;i++)
	{
		if(password1[i] != password2[i])
		{
			PASSWORD_FLAG=FALSE;
		}
	}

	UART_sendByte(MC1_READY);
	UART_sendByte(PASSWORD_FLAG);
	while(UART_recieveByte() != RECIEVED) {}

	if(PASSWORD_FLAG)
	{
		EEPROM_SavePassword(password1);
		EEPROM_writeByte(ADDRESS_OF_FLAG,NOT_FIRST_TIME);
		g_Step1Done=1;
	}else {
		g_Step1Done=0;
	}
}


int main () {
	/* Initializations of drivers */
	SREG |=(1<<7);
	BUZZER_init();
	DcMotor_Init();

	UART_ConfigType UARTConfig;
	UARTConfig.baud_rate=9600;
	UARTConfig.bit_data=M_8_BITS;
	UARTConfig.parity=OFF;
	UARTConfig.stop_bit=M_1_BIT;
	UART_init(&UARTConfig);

	TWI_ConfigType TWIConfig;
	TWIConfig.address=0x02;
	TWIConfig.bit_rate=400000;
	TWI_init(&TWIConfig);
	/*End Initializations of drivers */

	/* Flag to know if there is something saved in EEPROM */
	uint8 flag;
	EEPROM_readByte(ADDRESS_OF_FLAG,&flag);
	_delay_ms(10);

	while(UART_recieveByte() != MC2_READY) {}
	UART_sendByte(MC1_READY);
	UART_sendByte(flag);

	while(1)
	{

		if(flag != NOT_FIRST_TIME)
		{
			while(!(g_Step1Done)){
				STEP1();
			}
		}

		STEP2();
		while(!(g_STEP2Done)){
			if(g_WHICH_FUNCTION == WE_ARE_OPENING_DOOR )
			{
				OPEN_DOOR();

			}else if (g_WHICH_FUNCTION == WE_ARE_CHANGING_PASSWORD)
				CHANGE_Password();
		}

	}
}
