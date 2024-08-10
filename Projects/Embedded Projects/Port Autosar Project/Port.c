/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Karim Gomaa
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

/* ..........................................................*/

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigType * Port_Config = NULL_PTR;  /* Pointer to hold the Configuration */
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED; /* Holds if the  Module is initialized or not */

/************************************************************************************
 * Service Name: Port_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initialize the Port module.
 ************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
                        PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {
        Port_Config = ConfigPtr;
        Port_Status = PORT_INITIALIZED;

        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        Port_PinType i;
        for(i=0;i<PORT_CONFIGURED_CHANNLES;i++)
        {
            /* Enable clock and wait for clock to start */
            SYSCTL_RCGCGPIO_REG |= (1<<Port_Config->Port_Channels[i].Port_Num);
            while(!(SYSCTL_PRGPIO_REG & (1<<Port_Config->Port_Channels[i].Port_Num)));

            switch(Port_Config->Port_Channels[i].Port_Num)
            {
            case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;

            case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;

            case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;

            case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;

            case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;

            case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
            }

            if( ((Port_Config->Port_Channels[i].Port_Num == 3) && (Port_Config->Port_Channels[i].Pin_Num == 7)) || ((Port_Config->Port_Channels[i].Port_Num == 5) && (Port_Config->Port_Channels[i].Pin_Num == 0)) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if( (Port_Config->Port_Channels[i].Port_Num == 2) && (Port_Config->Port_Channels[i].Pin_Num <= 3) ) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            if(Port_Config->Port_Channels[i].mode == DIO )
            {
                /* Setup the pin mode as GPIO */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , (Port_Config->Port_Channels[i].Pin_Num));      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , (Port_Config->Port_Channels[i].Pin_Num));             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Config->Port_Channels[i].Pin_Num * 4));     /* Clear the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , (Port_Config->Port_Channels[i].Pin_Num));           /* enable the digital functionality on this pin */


            }else if(Port_Config->Port_Channels[i].mode == ADC )
            {

                /* Setup the pin mode as ADC */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , (Port_Config->Port_Channels[i].Pin_Num));      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , (Port_Config->Port_Channels[i].Pin_Num));             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Config->Port_Channels[i].Pin_Num * 4));     /* Clear the PMCx bits for this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , (Port_Config->Port_Channels[i].Pin_Num));        /* disable the digital functionality on this pin */

            }
            else{

                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);       /* enable the digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);             /* enable Alternative function for this pin by putting 1 to the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Config->Port_Channels[i].Pin_Num * 4));     /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( Port_Config->Port_Channels[i].mode << (Port_Config->Port_Channels[i].Pin_Num * 4));     /* Put the PMCx bits for this pin */

            }

            if(Port_Config->Port_Channels[i].direction == PORT_PIN_OUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                if(Port_Config->Port_Channels[i].initial_value == STD_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }
            else if(Port_Config->Port_Channels[i].direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                if(Port_Config->Port_Channels[i].resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(Port_Config->Port_Channels[i].resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
            }
            else
            {
                /* Do Nothing */
            }

        }
    }
}

/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin , Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the pin direction of this module.
 ************************************************************************************/
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction )
{
    uint8 error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the port is initialized or not */
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_UNINIT);
        error = TRUE;
    }else
    {
        /* No Action Required */
    }
    if(Pin >=PORT_CONFIGURED_CHANNLES )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_PARAM_PIN);
        error = TRUE;
    }else
    {
        /* No Action Required */
    }
    if(Port_Config->Port_Channels[Pin].direction_changeable == DIRECTION_NOT_CHANGEABLE )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE;
    }else
    {
        /* No Action Required */
    }
#endif
    if(error == FALSE)
    {
        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        switch(Port_Config->Port_Channels[Pin].Port_Num)
        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;

        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;

        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;

        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;

        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;

        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }

        if(Direction == PORT_PIN_OUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

            if(Port_Config->Port_Channels[Pin].initial_value == STD_HIGH)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
            }
        }
        else if(Direction == PORT_PIN_IN)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

            if(Port_Config->Port_Channels[Pin].resistor == PULL_UP)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
            }
            else if(Port_Config->Port_Channels[Pin].resistor == PULL_DOWN)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
            }
        }
        else
        {
            /* Do Nothing */
        }

    }
    else
    {
        /* No Action Required */
    }
}
#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None.
 * Return value: None
 * Description: Function to Refreshes port direction of this module.
 ************************************************************************************/
void Port_RefreshPortDirection( void )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the port is initialized or not */
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID,
                        PORT_E_UNINIT);
    }
    else
#endif
    {
        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        Port_PinType i;

        for(i=0;i<PORT_CONFIGURED_CHANNLES;i++)
        {
            if(Port_Config->Port_Channels[i].direction_changeable == DIRECTION_NOT_CHANGEABLE )
            {

                switch(Port_Config->Port_Channels[i].Port_Num)
                {
                case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;

                case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;

                case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;

                case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;

                case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;

                case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
                }

                if(Port_Config->Port_Channels[i].direction == PORT_PIN_OUT)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                    if(Port_Config->Port_Channels[i].initial_value == STD_HIGH)
                    {
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    }
                    else
                    {
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                    }
                }
                else if(Port_Config->Port_Channels[i].direction == PORT_PIN_IN)
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                    if(Port_Config->Port_Channels[i].resistor == PULL_UP)
                    {
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                    }
                    else if(Port_Config->Port_Channels[i].resistor == PULL_DOWN)
                    {
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                    }
                    else
                    {
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Config->Port_Channels[i].Pin_Num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                    }
                }
                else
                {
                    /* Do Nothing */
                }

            }
            else
            {
                /* Do Nothing As Pin is configured as ‘pin direction changeable during runtime‘ */
            }

        }
    }
}

/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
    uint8 error=FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }

    if(Port_Status == PORT_NOT_INITIALIZED)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }

#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    if(error == FALSE)
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
    else
    {
        /* No Action Required */
    }
}
#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin , Mode
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin mode of this module.
 ************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode )
{
    uint8 error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the port is initialized or not */
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_UNINIT);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    if(Pin >=PORT_CONFIGURED_CHANNLES )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_PARAM_PIN);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    if(Port_Config->Port_Channels[Pin].mode_changeable == MODE_NOT_CHANGEABLE )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_MODE_UNCHANGEABLE);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    if( ~( (Port_Config->Port_Channels[Pin].mode>=0 && Port_Config->Port_Channels[Pin].mode <10) || Port_Config->Port_Channels[Pin].mode == 14 || Port_Config->Port_Channels[Pin].mode == 15) )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_PARAM_INVALID_MODE);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    if(error == FALSE)
    {
        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        switch(Port_Config->Port_Channels[Pin].Port_Num)
        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;

        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;

        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;

        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;

        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;

        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }

        if( ((Port_Config->Port_Channels[Pin].Port_Num == 3) && (Port_Config->Port_Channels[Pin].Pin_Num == 7)) || ((Port_Config->Port_Channels[Pin].Port_Num == 5) && (Port_Config->Port_Channels[Pin].Pin_Num == 0)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else if( (Port_Config->Port_Channels[Pin].Port_Num == 2) && (Port_Config->Port_Channels[Pin].Pin_Num <= 3) ) /* PC0 to PC3 */
        {
            /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }

        if(Mode == DIO )
        {
            /* Setup the pin mode as GPIO */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Config->Port_Channels[Pin].Pin_Num * 4));     /* Clear the PMCx bits for this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);           /* enable the digital functionality on this pin */


        }else if(Mode == ADC )
        {

            /* Setup the pin mode as ADC */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Config->Port_Channels[Pin].Pin_Num * 4));     /* Clear the PMCx bits for this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);        /* disable the digital functionality on this pin */

        }
        else{

            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);       /* enable the digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config->Port_Channels[Pin].Pin_Num);             /* enable Alternative function for this pin by putting 1 to the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Config->Port_Channels[Pin].Pin_Num * 4));     /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( Port_Config->Port_Channels[Pin].mode << (Port_Config->Port_Channels[Pin].Pin_Num * 4));     /* Put the PMCx bits for this pin */
        }

    }
    else
    {
        /* No Action Required */
    }
}


