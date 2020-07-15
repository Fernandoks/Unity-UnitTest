
#include "driverGPIO.h"
#include "MK20DX256.h"



GPIO_Status_t GPIO_Init(REGISTERS_GPIO_T* GPIOReg)
{
    /*
     * This simpler function was selected due the lack of requirements
     * so used the simpliest
     */

    GPIOReg->PSOR = 0x10102000;
    GPIOReg->PCOR = 0x00028000;
    GPIOReg->PDDR = 0x1012A000;

    ReversePinMask = 0x00000022; //0010 0010
        
    return GPIO_ok;
}

GPIO_Status_t GPIO_SetPinAsOutput(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin)
{   
    if (Pin >= 32) 
    {
        return GPIO_error;
    }
    GPIO_Handler->PDDR |= BIT_TO_MASK(Pin);
    return GPIO_ok;
}

GPIO_Status_t GPIO_SetPinAsInput(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin)
{   
    if (Pin >= 32) 
    {
        return GPIO_error;
    }
    GPIO_Handler->PDDR &= ~BIT_TO_MASK(Pin);
    return GPIO_ok;
}

GPIO_Status_t GPIO_SetPin(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin)
{
    uint32_t Mask = BIT_TO_MASK(Pin);

    if ( (Pin >= 0) && (Pin < 32) )
    {   
        if ( GPIO_Handler->PDDR & Mask )
        {   
            if (ReversePinMask & Mask)
            {
                GPIO_Handler->PCOR |= Mask;
            }
            else
            {
                GPIO_Handler->PSOR |= Mask;
            }           
            return GPIO_ok;
        }
    }   
    return GPIO_error;
}


GPIO_Status_t GPIO_ResetPin(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin)
{
    uint32_t Mask = BIT_TO_MASK(Pin);
    if ( (Pin >= 0) && (Pin < 32) )
    {   
        if ( GPIO_Handler->PDDR & Mask)
        {
            if (ReversePinMask & Mask)
            {
                GPIO_Handler->PSOR |= Mask;
            }
            else
            {
                GPIO_Handler->PCOR |= Mask;
            }           
            return GPIO_ok;
        }
    }   
    return GPIO_error;
}


int8_t GPIO_ReadPin(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin)
{
    //Verify if pin is in range
    if ( (Pin >= 0) && (Pin < 32) )
    {   
        //Verify if pin is set to Input
        if ( (GPIO_Handler->PDDR & BIT_TO_MASK(Pin)) == 0 )
        {
            return ( GPIO_Handler->PDIR & BIT_TO_MASK(Pin) );
        }
    }
    return GPIO_error; 
}


int32_t GPIO_ReadPort(REGISTERS_GPIO_T* GPIO_Handler)
{
        //Verify if port is set to Input
        if ( GPIO_Handler->PDDR == 0x0 )
        {
            return ( (GPIO_Handler->PDIR) ^ ReversePinMask ) ;
        }
    return GPIO_error;
}