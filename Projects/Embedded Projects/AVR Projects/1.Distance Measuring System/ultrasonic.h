 /******************************************************************************
 *
 * Module: ULTRASONIC SENSOR
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for ULTRASONIC SENSOR
 *
 * Author: Karim Gomaa
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "std_types.h"
#include "icu.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ICU_CLOCK       F_CPU_8
#define ICU_EDGE        RISING

#define ULTRASONIC_TRIGGER_PORT  PORTB_ID
#define ULTRASONIC_TRIGGER_PIN   PIN5_ID

#define ULTRASONIC_ECHO_PORT   PORTD_ID
#define ULTRASONIC_ECHO_PIN    PIN6_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);

#endif
