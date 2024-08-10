#include "lcd.h"
#include "ultrasonic.h"
#include "std_types.h"
#include <util/delay.h>
#include <avr/io.h>

int main() {
	SREG |= (1<<7);
	Ultrasonic_init();
	LCD_init();
	LCD_displayString("Distance = ");
	volatile int distance;
	while(1){
        distance=Ultrasonic_readDistance();
		LCD_moveCursor(0,10);
		LCD_intgerToString(distance);
		if(distance<10)
		{
			LCD_moveCursor(0,11);
			LCD_displayString(" cm  ");
		}else if(distance<100)
		{
			LCD_moveCursor(0,12);
			LCD_displayString(" cm ");
		}else{
		LCD_moveCursor(0,13);
		LCD_displayString(" cm");
	}
}
}
