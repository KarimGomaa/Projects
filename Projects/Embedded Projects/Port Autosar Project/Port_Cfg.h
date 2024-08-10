/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Karim Gomaa
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for Set PIN DIRECTION API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Number of the configured Port Channels */
#define PORT_CONFIGURED_CHANNLES              (43U)

/*Port Pin ID number */
/*Used as a parameters to SetPin_Direction();*/
#define PORT_A_PIN_0    (Port_PinType)0
#define PORT_A_PIN_1    (Port_PinType)1
#define PORT_A_PIN_2    (Port_PinType)2
#define PORT_A_PIN_3    (Port_PinType)3
#define PORT_A_PIN_4    (Port_PinType)4
#define PORT_A_PIN_5    (Port_PinType)5
#define PORT_A_PIN_6    (Port_PinType)6
#define PORT_A_PIN_7    (Port_PinType)7

#define PORT_B_PIN_0    (Port_PinType)8
#define PORT_B_PIN_1    (Port_PinType)9
#define PORT_B_PIN_2    (Port_PinType)10
#define PORT_B_PIN_3    (Port_PinType)11
#define PORT_B_PIN_4    (Port_PinType)12
#define PORT_B_PIN_5    (Port_PinType)13
#define PORT_B_PIN_6    (Port_PinType)14
#define PORT_B_PIN_7    (Port_PinType)15

#define PORT_C_PIN_0    (Port_PinType)16
#define PORT_C_PIN_1    (Port_PinType)17
#define PORT_C_PIN_2    (Port_PinType)18
#define PORT_C_PIN_3    (Port_PinType)19
#define PORT_C_PIN_4    (Port_PinType)20
#define PORT_C_PIN_5    (Port_PinType)21
#define PORT_C_PIN_6    (Port_PinType)22
#define PORT_C_PIN_7    (Port_PinType)23

#define PORT_D_PIN_0    (Port_PinType)24
#define PORT_D_PIN_1    (Port_PinType)25
#define PORT_D_PIN_2    (Port_PinType)26
#define PORT_D_PIN_3    (Port_PinType)27
#define PORT_D_PIN_4    (Port_PinType)28
#define PORT_D_PIN_5    (Port_PinType)29
#define PORT_D_PIN_6    (Port_PinType)30
#define PORT_D_PIN_7    (Port_PinType)31

#define PORT_E_PIN_0    (Port_PinType)32
#define PORT_E_PIN_1    (Port_PinType)33
#define PORT_E_PIN_2    (Port_PinType)34
#define PORT_E_PIN_3    (Port_PinType)35
#define PORT_E_PIN_4    (Port_PinType)36
#define PORT_E_PIN_5    (Port_PinType)37

#define PORT_F_PIN_0    (Port_PinType)38
#define PORT_F_PIN_1    (Port_PinType)39
#define PORT_F_PIN_2    (Port_PinType)40
#define PORT_F_PIN_3    (Port_PinType)41
#define PORT_F_PIN_4    (Port_PinType)42


/*PORT INDEXS*/

#define PORT_A     (0U)
#define PORT_B     (1U)
#define PORT_C     (2U)
#define PORT_D     (3U)
#define PORT_E     (4U)
#define PORT_F     (5U)

/*PIN INDEXS*/
#define PORT_PIN0               (uint8)0
#define PORT_PIN1               (uint8)1
#define PORT_PIN2               (uint8)2
#define PORT_PIN3               (uint8)3
#define PORT_PIN4               (uint8)4
#define PORT_PIN5               (uint8)5
#define PORT_PIN6               (uint8)6
#define PORT_PIN7               (uint8)7

/* Pin Modes */
#define MODE_DIO                DIO
#define MODE_ALT1               ALT1
#define MODE_ALT2               ALT2
#define MODE_ALT3               ALT3
#define MODE_ALT4               ALT4
#define MODE_ALT5               ALT5
#define MODE_ALT6               ALT6
#define MODE_ALT7               ALT7
#define MODE_ALT8               ALT8
#define MODE_ALT9               ALT9
#define MODE_ALT14              ALT14
#define MODE_ADC                ADC


/* Pin Direction Type . RunTime */
#define PORT_A_PIN_0_DIRECTION     PORT_PIN_IN
#define PORT_A_PIN_1_DIRECTION     PORT_PIN_IN
#define PORT_A_PIN_2_DIRECTION     PORT_PIN_IN
#define PORT_A_PIN_3_DIRECTION     PORT_PIN_IN
#define PORT_A_PIN_4_DIRECTION     PORT_PIN_IN
#define PORT_A_PIN_5_DIRECTION     PORT_PIN_IN
#define PORT_A_PIN_6_DIRECTION     PORT_PIN_IN
#define PORT_A_PIN_7_DIRECTION     PORT_PIN_IN

#define PORT_B_PIN_0_DIRECTION     PORT_PIN_IN
#define PORT_B_PIN_1_DIRECTION     PORT_PIN_IN
#define PORT_B_PIN_2_DIRECTION     PORT_PIN_IN
#define PORT_B_PIN_3_DIRECTION     PORT_PIN_IN
#define PORT_B_PIN_4_DIRECTION     PORT_PIN_IN
#define PORT_B_PIN_5_DIRECTION     PORT_PIN_IN
#define PORT_B_PIN_6_DIRECTION     PORT_PIN_IN
#define PORT_B_PIN_7_DIRECTION     PORT_PIN_IN

#define PORT_C_PIN_0_DIRECTION     PORT_PIN_IN
#define PORT_C_PIN_1_DIRECTION     PORT_PIN_IN
#define PORT_C_PIN_2_DIRECTION     PORT_PIN_IN
#define PORT_C_PIN_3_DIRECTION     PORT_PIN_IN
#define PORT_C_PIN_4_DIRECTION     PORT_PIN_IN
#define PORT_C_PIN_5_DIRECTION     PORT_PIN_IN
#define PORT_C_PIN_6_DIRECTION     PORT_PIN_IN
#define PORT_C_PIN_7_DIRECTION     PORT_PIN_IN

#define PORT_D_PIN_0_DIRECTION     PORT_PIN_IN
#define PORT_D_PIN_1_DIRECTION     PORT_PIN_IN
#define PORT_D_PIN_2_DIRECTION     PORT_PIN_IN
#define PORT_D_PIN_3_DIRECTION     PORT_PIN_IN
#define PORT_D_PIN_4_DIRECTION     PORT_PIN_IN
#define PORT_D_PIN_5_DIRECTION     PORT_PIN_IN
#define PORT_D_PIN_6_DIRECTION     PORT_PIN_IN
#define PORT_D_PIN_7_DIRECTION     PORT_PIN_IN

#define PORT_E_PIN_0_DIRECTION     PORT_PIN_IN
#define PORT_E_PIN_1_DIRECTION     PORT_PIN_IN
#define PORT_E_PIN_2_DIRECTION     PORT_PIN_IN
#define PORT_E_PIN_3_DIRECTION     PORT_PIN_IN
#define PORT_E_PIN_4_DIRECTION     PORT_PIN_IN
#define PORT_E_PIN_5_DIRECTION     PORT_PIN_IN

#define PORT_F_PIN_0_DIRECTION     PORT_PIN_IN
#define PORT_F_PIN_1_DIRECTION     PORT_PIN_OUT     /*Output for LED */
#define PORT_F_PIN_2_DIRECTION     PORT_PIN_IN
#define PORT_F_PIN_3_DIRECTION     PORT_PIN_IN
#define PORT_F_PIN_4_DIRECTION     PORT_PIN_IN

/* Pin Resistor */
#define PORT_A_PIN_0_RESISTOR         OFF
#define PORT_A_PIN_1_RESISTOR         OFF
#define PORT_A_PIN_2_RESISTOR         OFF
#define PORT_A_PIN_3_RESISTOR         OFF
#define PORT_A_PIN_4_RESISTOR         OFF
#define PORT_A_PIN_5_RESISTOR         OFF
#define PORT_A_PIN_6_RESISTOR         OFF
#define PORT_A_PIN_7_RESISTOR         OFF

#define PORT_B_PIN_0_RESISTOR         OFF
#define PORT_B_PIN_1_RESISTOR         OFF
#define PORT_B_PIN_2_RESISTOR         OFF
#define PORT_B_PIN_3_RESISTOR         OFF
#define PORT_B_PIN_4_RESISTOR         OFF
#define PORT_B_PIN_5_RESISTOR         OFF
#define PORT_B_PIN_6_RESISTOR         OFF
#define PORT_B_PIN_7_RESISTOR         OFF

#define PORT_C_PIN_0_RESISTOR         OFF
#define PORT_C_PIN_1_RESISTOR         OFF
#define PORT_C_PIN_2_RESISTOR         OFF
#define PORT_C_PIN_3_RESISTOR         OFF
#define PORT_C_PIN_4_RESISTOR         OFF
#define PORT_C_PIN_5_RESISTOR         OFF
#define PORT_C_PIN_6_RESISTOR         OFF
#define PORT_C_PIN_7_RESISTOR         OFF

#define PORT_D_PIN_0_RESISTOR         OFF
#define PORT_D_PIN_1_RESISTOR         OFF
#define PORT_D_PIN_2_RESISTOR         OFF
#define PORT_D_PIN_3_RESISTOR         OFF
#define PORT_D_PIN_4_RESISTOR         OFF
#define PORT_D_PIN_5_RESISTOR         OFF
#define PORT_D_PIN_6_RESISTOR         OFF
#define PORT_D_PIN_7_RESISTOR         OFF

#define PORT_E_PIN_0_RESISTOR         OFF
#define PORT_E_PIN_1_RESISTOR         OFF
#define PORT_E_PIN_2_RESISTOR         OFF
#define PORT_E_PIN_3_RESISTOR         OFF
#define PORT_E_PIN_4_RESISTOR         OFF
#define PORT_E_PIN_5_RESISTOR         OFF

#define PORT_F_PIN_0_RESISTOR         OFF
#define PORT_F_PIN_1_RESISTOR         OFF
#define PORT_F_PIN_2_RESISTOR         OFF
#define PORT_F_PIN_3_RESISTOR         OFF
#define PORT_F_PIN_4_RESISTOR         PULL_UP       /* pull up for the button */

/* pin level */
#define PORT_A_PIN_0_LEVEL         STD_OFF
#define PORT_A_PIN_1_LEVEL         STD_OFF
#define PORT_A_PIN_2_LEVEL         STD_OFF
#define PORT_A_PIN_3_LEVEL         STD_OFF
#define PORT_A_PIN_4_LEVEL         STD_OFF
#define PORT_A_PIN_5_LEVEL         STD_OFF
#define PORT_A_PIN_6_LEVEL         STD_OFF
#define PORT_A_PIN_7_LEVEL         STD_OFF

#define PORT_B_PIN_0_LEVEL         STD_OFF
#define PORT_B_PIN_1_LEVEL         STD_OFF
#define PORT_B_PIN_2_LEVEL         STD_OFF
#define PORT_B_PIN_3_LEVEL         STD_OFF
#define PORT_B_PIN_4_LEVEL         STD_OFF
#define PORT_B_PIN_5_LEVEL         STD_OFF
#define PORT_B_PIN_6_LEVEL         STD_OFF
#define PORT_B_PIN_7_LEVEL         STD_OFF

#define PORT_C_PIN_0_LEVEL         STD_OFF
#define PORT_C_PIN_1_LEVEL         STD_OFF
#define PORT_C_PIN_2_LEVEL         STD_OFF
#define PORT_C_PIN_3_LEVEL         STD_OFF
#define PORT_C_PIN_4_LEVEL         STD_OFF
#define PORT_C_PIN_5_LEVEL         STD_OFF
#define PORT_C_PIN_6_LEVEL         STD_OFF
#define PORT_C_PIN_7_LEVEL         STD_OFF

#define PORT_D_PIN_0_LEVEL         STD_OFF
#define PORT_D_PIN_1_LEVEL         STD_OFF
#define PORT_D_PIN_2_LEVEL         STD_OFF
#define PORT_D_PIN_3_LEVEL         STD_OFF
#define PORT_D_PIN_4_LEVEL         STD_OFF
#define PORT_D_PIN_5_LEVEL         STD_OFF
#define PORT_D_PIN_6_LEVEL         STD_OFF
#define PORT_D_PIN_7_LEVEL         STD_OFF

#define PORT_E_PIN_0_LEVEL         STD_OFF
#define PORT_E_PIN_1_LEVEL         STD_OFF
#define PORT_E_PIN_2_LEVEL         STD_OFF
#define PORT_E_PIN_3_LEVEL         STD_OFF
#define PORT_E_PIN_4_LEVEL         STD_OFF
#define PORT_E_PIN_5_LEVEL         STD_OFF

#define PORT_F_PIN_0_LEVEL         STD_OFF
#define PORT_F_PIN_1_LEVEL         STD_OFF
#define PORT_F_PIN_2_LEVEL         STD_OFF
#define PORT_F_PIN_3_LEVEL         STD_OFF
#define PORT_F_PIN_4_LEVEL         STD_ON

/* Pin Direction Changeable */
#define PORT_A_PIN_0_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_A_PIN_1_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_A_PIN_2_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_A_PIN_3_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_A_PIN_4_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_A_PIN_5_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_A_PIN_6_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_A_PIN_7_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE

#define PORT_B_PIN_0_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_B_PIN_1_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_B_PIN_2_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_B_PIN_3_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_B_PIN_4_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_B_PIN_5_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_B_PIN_6_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_B_PIN_7_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE

#define PORT_C_PIN_0_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_C_PIN_1_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_C_PIN_2_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_C_PIN_3_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_C_PIN_4_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_C_PIN_5_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_C_PIN_6_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_C_PIN_7_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE

#define PORT_D_PIN_0_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_D_PIN_1_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_D_PIN_2_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_D_PIN_3_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_D_PIN_4_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_D_PIN_5_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_D_PIN_6_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_D_PIN_7_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE

#define PORT_E_PIN_0_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_E_PIN_1_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_E_PIN_2_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_E_PIN_3_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_E_PIN_4_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_E_PIN_5_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE

#define PORT_F_PIN_0_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_F_PIN_1_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_F_PIN_2_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_F_PIN_3_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE
#define PORT_F_PIN_4_DIRECTION_CHANGABLE     DIRECTION_NOT_CHANGEABLE

/* Pin Mode Changeable */
#define PORT_A_PIN_0_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_A_PIN_1_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_A_PIN_2_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_A_PIN_3_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_A_PIN_4_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_A_PIN_5_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_A_PIN_6_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_A_PIN_7_MODE_CHANGABLE     MODE_NOT_CHANGEABLE

#define PORT_B_PIN_0_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_B_PIN_1_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_B_PIN_2_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_B_PIN_3_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_B_PIN_4_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_B_PIN_5_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_B_PIN_6_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_B_PIN_7_MODE_CHANGABLE     MODE_NOT_CHANGEABLE

#define PORT_C_PIN_0_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_C_PIN_1_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_C_PIN_2_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_C_PIN_3_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_C_PIN_4_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_C_PIN_5_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_C_PIN_6_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_C_PIN_7_MODE_CHANGABLE     MODE_NOT_CHANGEABLE

#define PORT_D_PIN_0_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_D_PIN_1_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_D_PIN_2_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_D_PIN_3_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_D_PIN_4_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_D_PIN_5_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_D_PIN_6_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_D_PIN_7_MODE_CHANGABLE     MODE_NOT_CHANGEABLE

#define PORT_E_PIN_0_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_E_PIN_1_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_E_PIN_2_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_E_PIN_3_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_E_PIN_4_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_E_PIN_5_MODE_CHANGABLE     MODE_NOT_CHANGEABLE

#define PORT_F_PIN_0_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_F_PIN_1_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_F_PIN_2_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_F_PIN_3_MODE_CHANGABLE     MODE_NOT_CHANGEABLE
#define PORT_F_PIN_4_MODE_CHANGABLE     MODE_NOT_CHANGEABLE

#endif /* PORT_CFG_H */

