#ifndef DRIVERGPIO_H
#define DRIVERGPIO_H

#include <stdint.h>
#include "MK20DX256.h"


typedef enum
{
    GPIO_ok = 0,
    GPIO_error = -1
} GPIO_Status_t;

// This masks the reverse polarity pins 
uint32_t ReversePinMask;

GPIO_Status_t GPIO_Init(REGISTERS_GPIO_T* GPIOReg);

GPIO_Status_t GPIO_SetPinAsOutput(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin);
GPIO_Status_t GPIO_SetPinAsInput(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin);

GPIO_Status_t GPIO_SetPin(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin);
GPIO_Status_t GPIO_ResetPin(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin);

int8_t GPIO_ReadPin(REGISTERS_GPIO_T* GPIO_Handler, uint8_t Pin);
int32_t GPIO_ReadPort(REGISTERS_GPIO_T* GPIO_Handler);

#endif //GPIO_H
