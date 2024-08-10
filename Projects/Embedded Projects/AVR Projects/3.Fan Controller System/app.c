#include "common_macros.h"
#include "std_types.h"
#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "motor.h"


int main () {
	volatile uint8 temp;

	ADC_ConfigType ADC_Config;
	ADC_Config.ref_volt=VOLT_2_56;
	ADC_Config.prescaler=PRESCALER_8;

	ADC_init(&ADC_Config);
	LCD_init();

	DcMotor_State state;
	DcMotor_Init();

	LCD_moveCursor(0,4);
	LCD_displayString("FAN is OFF");

	while(1){
		temp=LM35_getTemperature();
		LCD_moveCursor(1,3);
		LCD_displayString("Temp = ");

		if(temp<100)
		{
			if(temp<30)
			{
				LCD_moveCursor(0,4);
				LCD_displayString("FAN is OFF");
				state=STOP;
				DcMotor_Rotate(state,0);
			}else if(temp<60)
			{
				LCD_moveCursor(0,4);
				LCD_displayString("FAN is ON ");
				state=CW;
				DcMotor_Rotate(state,64);
			}else if(temp<90)
			{
				LCD_moveCursor(0,4);
				LCD_displayString("FAN is ON ");
				state=CW;
				DcMotor_Rotate(state,128);
			}else {

				LCD_moveCursor(0,4);
				LCD_displayString("FAN is ON ");
				state=A_CW;
				DcMotor_Rotate(state,192);
			}

			if(temp<10){

				LCD_moveCursor(1,10);
				LCD_intgerToString(temp);
				LCD_displayString(" ");
				LCD_displayString("C ");

			}else{
				LCD_moveCursor(1,10);
				LCD_intgerToString(temp);
				LCD_moveCursor(1,12);
				LCD_displayString(" ");
				LCD_displayString("C ");
			}

		}
		else {
			if(temp<120){
				LCD_moveCursor(0,4);
				LCD_displayString("FAN is ON ");
				state=CW;
				DcMotor_Rotate(state,192);
			}else {
				LCD_moveCursor(0,4);
				LCD_displayString("FAN is ON ");
				state=CW;
				DcMotor_Rotate(state,255);

			}

			LCD_moveCursor(1,10);
			LCD_intgerToString(temp);
			LCD_displayString(" C");
		}
	}
}
