/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Karim Gomaa
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Karim Gomaa's ID = 1010 :) */
#define PORT_VENDOR_ID    (1010U)

/* Dio Module Id */
#define PORT_MODULE_ID    (124U)

/* Dio Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Dio Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros For Functions                                 *
 ******************************************************************************/
/* Service ID for PORT init */
#define PORT_INIT_SID                           (uint8)0x00

/* Service ID for PORT SetPinDirection */
#define PORT_SET_PIN_DIRECTION_SID              (uint8)0x01

/* Service ID for PORT refresh port direction */
#define PORT_REFRESH_PORT_DIRECTION_SID         (uint8)0x02

/* Service ID for PORT get version info */
#define PORT_GET_VERSION_INFO_SID               (uint8)0x03

/* Service ID for PORT set pin mode */
#define PORT_SET_PIN_MODE_SID                   (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                     (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE        (uint8)0x0B

/* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG                  (uint8)0x0C

/* API Port_SetPinMode service called when mode is unchangeable.  */
#define PORT_E_PARAM_INVALID_MODE            (uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable.  */
#define PORT_E_MODE_UNCHANGEABLE             (uint8)0x0E

/*
 * API service used without module initialization is reported using following
 * error code (Not exist in AUTOSAR 4.0.3 PORT SWS Document.
 */
#define PORT_E_UNINIT                         (uint8)0x0F

/*
 * The API service shall return immediately without any further action,
 * beside reporting this development error.
 */
#define PORT_E_PARAM_POINTER                   (uint8)0x10
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Port_PinType used by the Port APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinModeType used by the Port APIs */
typedef uint8 Port_PinModeType;

/* Type definition for Port_num used by the Port_ConfigChannel structure */
typedef uint8 Port_num;

/* Type definition for Port_num used by the Port_ConfigChannel structure */
typedef uint8 Pin_num;

/* Type definition for Pin_level used by the Port_ConfigChannel structure */
typedef uint8 Pin_level;

/* Data Enumeration required for Setting the Port Pin Resistor Type */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;


/* Data Enumeration required for Setting the Port Pin Direction Type */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
} Port_PinDirectionType;

typedef enum
{
    DIRECTION_NOT_CHANGEABLE,DIRECTION_CHANGEABLE
}Port_DirectionChangeable;

typedef enum
{
    MODE_NOT_CHANGEABLE,MODE_CHANGEABLE
}Port_ModeChangeable;

typedef enum
{
    DIO,ALT1,ALT2,ALT3,ALT4,ALT5,ALT6,ALT7,ALT8,ALT9,ALT14=14,ADC
}Port_ModeSelect;

typedef struct
{
    /* Member contains the Port Number of the Port that this channel belongs to */
    Port_num Port_Num;

    /* Member contains the Pin Number of the Channel*/
    Pin_num Pin_Num;

    /* Member contains the Mode of the Channel*/
    Port_ModeSelect mode;

    /* Member contains the Direction of the Channel*/
    Port_PinDirectionType direction;

    /* Member contains the resistor of the Channel*/
    Port_InternalResistor resistor;

    /* Member contains the initial value of the Channel*/
    Pin_level initial_value;

    /* Member contains if the direction is changeable during runtime or not */
    Port_DirectionChangeable direction_changeable;

    /* Member contains if the mode is changeable during runtime or not */
    Port_ModeChangeable mode_changeable;


}Port_ConfigChannel;

/* Structure for Port_ConfigType  */
typedef struct
{
    Port_ConfigChannel Port_Channels[PORT_CONFIGURED_CHANNLES];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function for PORT Set Pin Mode API */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode );

/* Function for PORT Refresh Port Direction API */
void Port_RefreshPortDirection( void );

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Function for PORT Set Pin Direction API */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction );
#endif

/* Function for PORT Initialization API */
void Port_Init( const Port_ConfigType* ConfigPtr );

/* Function for PORT Get Version Info API */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by PORT and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
