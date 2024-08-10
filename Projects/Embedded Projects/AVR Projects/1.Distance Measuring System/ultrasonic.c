#include "std_types.h"
#include "common_macros.h"
#include "icu.h"
#include "gpio.h"
#include "ultrasonic.h"
#include <util/delay.h>

uint8 g_count=0;
static volatile uint16 timer_value;

void Ultrasonic_init(void){

	Icu_ConfigType Icu_Config;
	Icu_Config.clock=ICU_CLOCK;
	Icu_Config.edge=ICU_EDGE;

	Icu_init(&Icu_Config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,PIN_OUTPUT);

}

void Ultrasonic_Trigger(void){

	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOGIC_HIGH);
	_delay_us(13);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOGIC_LOW);

}

uint16 Ultrasonic_readDistance(void){
     uint16 distance;
	Ultrasonic_Trigger();

	while (timer_value==0) ;
    distance=(timer_value/58.8)/0.98;
    timer_value=0;
    return distance;

}

void Ultrasonic_edgeProcessing(void){

    if(g_count==0)
    {
    	Icu_clearTimerValue();
    	g_count++;
    	Icu_setEdgeDetectionType(FALLING);

    }else if(g_count==1)
	{
    	timer_value=Icu_getInputCaptureValue();
    	Icu_setEdgeDetectionType(RISING);
    	g_count=0;
	}
}

