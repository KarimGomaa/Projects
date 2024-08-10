/******************************************************************************
 *
 * Module: MicroController 2
 *
 * File Name: hmi_ecu.c
 *
 * Description: Source file for MicroController 2 Application for DOOR PASSWORD
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/

#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include "keypad.h"
#include "lcd.h"
#include "timer1.h"
#include "uart.h"
#include <util/delay.h>
#include <avr/io.h>

#define MC1_READY                                 0x10 /* Macro to be recieved from MC1   */
#define MC2_READY                                 0x11 /*  Macro to be sent to MC1 */
#define RECIEVED                                  0x20 /* Macro to confirm receiving password1 or ande used in other resiving password  */
#define RECIEVED2                                 0x30 /* Macro to confirm receiving password2 by MC2   */
#define NOT_FIRST_TIME                            0x06 /* To Be used in eeprom as a flag that there is a password saved in it  */
#define PLEASE_CHANGE_PASSWORD                    0x44 /* MC2 sent this macro to MC1 to let him know that we are changing password   */
#define PLEASE_OPEN_DOOR                          0x33 /*  MC2 sent this macro to MC1 to let him know that we are opening the door */
#define OKAY                                      0x88 /* this is sent by MC1 to let MC2 know if the passwords are the same  */
#define NOT_OKAY                                  0x99 /* this is sent by MC1 to let MC2 know if the passwords are not the same  */
#define WE_ARE_OPENING_DOOR                       0x22 /* macro to be used in main in g_WHICH_FUNCTION */
#define WE_ARE_CHANGING_PASSWORD                  0x23 /* macro to be used in main in g_WHICH_FUNCTION */

static volatile uint8 g_STEP1Done=0;  /* Step1 is done correctly  */
static volatile uint8 g_DOOR_is_opening=0; /* to count 15 sec while door is opening*/
static volatile uint8 g_DOOR_is_closing=0; /* to count 18 sec while door is closing as 3 sec for stop and 15 sec motor rotates ccw*/
static volatile uint8 g_error_counter=0; /* to count errors and be activated after 3 times  */
static volatile uint8 g_error_time=0; /* to control timer to be 1 min  */
static volatile uint8 g_STEP2Done=0; /* Step2 is done correctly */
static volatile uint8 g_WHICH_FUNCTION=0; /*used in main to know which function to be called  */

/************************************************************************************
 *
 * Function Name : GET_password
 *
 * Description : to get Password from the user by keypad
 *
 * Note : 0 is disable due to bug that make the keypad cant use enter button, tried to solve
 * but didnt find any thing to change so i thing my proteus is the problem anyway you cant use 0 in your passwords
 * to see that error just remove || key_is_pressed[i]==0 found in while loop in function GET_password and try.
 *
 *************************************************************************************/

void GET_password(uint8 *str){

	uint8 i;
	uint8 key_is_pressed[5]={'k','k','k','k','k'};

	for(i=0;i<5;i++)
	{
		while(key_is_pressed[i]=='k' || key_is_pressed[i]=='+' || \
				key_is_pressed[i]=='-' || key_is_pressed[i]=='*' || \
				key_is_pressed[i]=='%' || key_is_pressed[i]==13 || key_is_pressed[i]=='=' || key_is_pressed[i]==0)
		{
			key_is_pressed[i]=KEYPAD_getPressedKey();
		}

		LCD_moveCursor(1,i);
		LCD_displayCharacter('*');
		_delay_ms(250);
	}
	for(i=0;i<5;i++)
	{
		str[i]=key_is_pressed[i];
	}
	str[5]='#';
	str[6]='\0';

	while (KEYPAD_getPressedKey() != 13 ) {}
	_delay_ms(100);
}

/************************************************************************************
 *
 * Function Name : TIMER1_Start
 *
 * Description : fun to initials timer1
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
 * Description : function to calculate 1 min
 *
 *************************************************************************************/

void ERROR_time(void){
	static volatile uint8 tik=0;
	if(tik==16){
		Timer1_deInit();
		g_error_time=1;
	}else{
		tik++;
	}
}

/************************************************************************************
 *
 * Function Name : DOOR_is_opening
 *
 * Description : fucntion to calculate  15 sec
 *
 *************************************************************************************/

void DOOR_is_opening(void){
	static volatile uint8 tik=0;
	if(tik==4){
		Timer1_deInit();
		g_DOOR_is_opening=1;
	}else{
		tik++;
	}
}

/************************************************************************************
 *
 * Function Name :  DOOR_is_closing
 *
 * Description : fucntion to calculate  18 sec
 *
 *************************************************************************************/

void DOOR_is_closing(void) {
	static volatile uint8 tik=0;
	if(tik==5){
		Timer1_deInit();
		g_DOOR_is_closing=1;
	}else{
		tik++;
	}
}

/************************************************************************************
 *
 * Function Name : OPEN_DOOR
 *
 * Description : function to open door
 *
 *************************************************************************************/

void OPEN_DOOR(){

	uint8 password_checker[7];
	uint8 flag;

	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("PLz enter Pass:");

	GET_password(password_checker);

	UART_sendByte(MC2_READY);

	UART_sendString(password_checker);
	while(UART_recieveByte() != RECIEVED ) {}

	while(UART_recieveByte() != MC1_READY){}
	flag=UART_recieveByte();

	if(flag == OKAY ){

		TIMER1_Start(DOOR_is_opening);
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("DOOR IS OPENING.");
		while(!(g_DOOR_is_opening)) {}
		g_DOOR_is_opening=0;

		TIMER1_Start(DOOR_is_closing);
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("DOOR IS CLOSING.");
		while(!(g_DOOR_is_closing)) {}
		g_DOOR_is_closing=0;

		g_error_counter=0;
		g_STEP2Done=1;

	}else if(flag == NOT_OKAY){
		g_WHICH_FUNCTION = WE_ARE_OPENING_DOOR;
		g_error_counter++;
		if(g_error_counter==3)
		{
			TIMER1_Start(ERROR_time);
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("    ..ERROR..  ");
			while(!(g_error_time)) {}
			g_error_time=0;
			g_error_counter=0;
			g_STEP2Done=1;
		}
	}

}

/************************************************************************************
 *
 * Function Name : CHANGE_Password
 *
 * Description : function to change password
 *
 *************************************************************************************/

void CHANGE_Password(){

	uint8 password_checker[7];
	uint8 password_changed1[7];
	uint8 password_changed2[7];
	uint8 flag;

	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("PLz enter Pass:");

	GET_password(password_checker);

	UART_sendByte(MC2_READY);

	UART_sendString(password_checker);
	while(UART_recieveByte() != RECIEVED ) {}

	while(UART_recieveByte() != MC1_READY){}
	flag=UART_recieveByte();

	if(flag == OKAY ){
		uint8 flag;
		uint8 i;

		do{
			flag=TRUE;
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("enter new pass!");

			GET_password(password_changed1);

			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Re-Enter Pass !");

			GET_password(password_changed2);

			for(i=0;i<5;i++)
			{
				if(password_changed2[i] != password_changed1[i])
				{
					flag=FALSE;
				}
			}
		} while(!flag);

		UART_sendByte(MC2_READY);
		UART_sendString(password_changed1);
		while(UART_recieveByte() != RECIEVED) {}

		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("DONE ^-^");

		g_error_counter=0;
		g_STEP2Done=1;
		_delay_ms(500);

	}else if(flag == NOT_OKAY){
		g_WHICH_FUNCTION = WE_ARE_CHANGING_PASSWORD;
		g_error_counter++;
		if(g_error_counter==3)
		{
			TIMER1_Start(ERROR_time);
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("    ..ERROR..  ");
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
 * Description : function to guide as to open door or change password
 *
 *************************************************************************************/

void STEP2(){
	g_STEP2Done=0;
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("+ : OPEN DOOR");
	LCD_moveCursor(1, 0);
	LCD_displayString("- : CHANGE PASS");

	while(1){
		if(KEYPAD_getPressedKey() == '+')
		{
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("OPEN DOOR IS");
			LCD_moveCursor(1,0);
			LCD_displayString("SELECTED  ^_^");
			_delay_ms(500);
			UART_sendByte(MC2_READY);
			UART_sendByte(PLEASE_OPEN_DOOR);
			OPEN_DOOR();
			break;
		}else if(KEYPAD_getPressedKey() == '-')
		{
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("CHANGE PASS IS");
			LCD_moveCursor(1,0);
			LCD_displayString("SELECTED  ^_^");
			_delay_ms(500);
			UART_sendByte(MC2_READY);
			UART_sendByte(PLEASE_CHANGE_PASSWORD);
			CHANGE_Password();
			break;
		}

	}
}

/************************************************************************************
 *
 * Function Name : STEP1
 *
 * Description : func to get two password and send them to MC1 used one time in the first of the program
 *
 *************************************************************************************/

void STEP1(){

	LCD_clearScreen();
	LCD_moveCursor(0,0);

	uint8 pass1[7];
	uint8 pass2[7];
	uint8 PASSWORD_CONDITION;

	LCD_displayString("Plz Enter Pass:");
	GET_password(pass1);

	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Re-Enter Pass: ");
	GET_password(pass2);

	UART_sendByte(MC2_READY);

	UART_sendString(pass1);
	while(UART_recieveByte() != RECIEVED ) {}

	UART_sendByte(MC2_READY);

	UART_sendString(pass2);
	while(UART_recieveByte() != RECIEVED2 ) {}

	while(UART_recieveByte() != MC1_READY){}
	PASSWORD_CONDITION=UART_recieveByte();
	UART_sendByte(RECIEVED);

	if(PASSWORD_CONDITION)
	{
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString(" DONE ^_^ ");
		g_STEP1Done=1;
		_delay_ms(1000);

	}else{
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("WRONG PASSWORD!");
		g_STEP1Done=0;
		_delay_ms(1000);
	}
}


int main () {
	/* Initializations of drivers */
	SREG |=(1<<7);
	LCD_init();

	UART_ConfigType UARTConfig;
	UARTConfig.baud_rate=9600;
	UARTConfig.bit_data=M_8_BITS;
	UARTConfig.parity=OFF;
	UARTConfig.stop_bit=M_1_BIT;
	UART_init(&UARTConfig);

	/*End Initializations of drivers */

	/* Flag to know if there is something saved in EEPROM */
	uint8 flag;
	UART_sendByte(MC2_READY);
	while(UART_recieveByte() != MC1_READY) {}
	flag=UART_recieveByte();


	while (1){

		if(flag != NOT_FIRST_TIME)
		{
			while(!(g_STEP1Done)){
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
