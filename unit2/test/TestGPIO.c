
#include "unity.h"
#include "driverGPIO.h"
#include "MK20DX256.h"


/*
 * setUp and tearDown functions are called before (setUp) and after (tearDown) each test
 */
void setUp(void)
{   
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Init(&GPIO_Handler);
}

void tearDown(void)
{

}

/*******************************************************************************************
 * GPIO_Init
 * ACTION: Configure the registers
 * CONDITION: 
 *******************************************************************************************/
void test_Init_should_ConfigurePins(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
    GPIO_Handler.PSOR = 0;
    GPIO_Handler.PCOR = 0;
    GPIO_Handler.PDDR = 0;

    GPIO_Init(&GPIO_Handler);

    TEST_ASSERT_EQUAL_HEX32(0x10102000,GPIO_Handler.PSOR);
    TEST_ASSERT_EQUAL_HEX32(0x00028000,GPIO_Handler.PCOR);
    TEST_ASSERT_EQUAL_HEX32(0x1012A000,GPIO_Handler.PDDR);
}

/*******************************************************************************************
 * GPIO_ReadPort
 * ACTION: Return port value
 * CONDITION: All port value, must handle reversed pins
 *******************************************************************************************/

void test_ReadPort_should_ShowProperValuesForReversedPins(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
    
    GPIO_Init(&GPIO_Handler);
    GPIO_Handler.PDDR = 0;
    
    GPIO_Handler.PDIR = 0;
    uint32_t returnValue = GPIO_ReadPort(&GPIO_Handler);
    TEST_ASSERT_NOT_EQUAL(GPIO_error, returnValue);
    TEST_ASSERT_EQUAL_HEX32(0x00000022,returnValue);

    GPIO_Handler.PDIR = 0xFFFFFFFF;
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFDD,GPIO_ReadPort(&GPIO_Handler));

}

/*******************************************************************************************
 * GPIO_ReadPin
 * ACTION: Return pin value 
 * CONDITION: Valid Pin, Pin set as Input
 *******************************************************************************************/
void test_ReadPin_returnValue(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
    GPIO_Handler.PDDR = 0;
    GPIO_Handler.PDIR = 0;

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsOutput(&GPIO_Handler,0));
    TEST_ASSERT_EQUAL(GPIO_error,GPIO_ReadPin(&GPIO_Handler,0));

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsOutput(&GPIO_Handler,0));
    TEST_ASSERT_UINT8_WITHIN(255,0,GPIO_ReadPin(&GPIO_Handler,0));
}

/*******************************************************************************************
 * GPIO_SetPin
 * ACTION: Set the pin HIGH
 * CONDITION: Valid Pin, Pin set as Output, Reversed Pins
 *******************************************************************************************/


void test_SetPin_should_setpinHigh(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
    GPIO_Handler.PSOR = 0;
    GPIO_Handler.PCOR = 0;

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsOutput(&GPIO_Handler,0));
    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPin(&GPIO_Handler,0));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0),GPIO_Handler.PSOR);
    TEST_ASSERT_EQUAL_HEX32(0,GPIO_Handler.PCOR);

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsOutput(&GPIO_Handler,16));
    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPin(&GPIO_Handler,16));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(16) | BIT_TO_MASK(0),GPIO_Handler.PSOR);
    TEST_ASSERT_EQUAL_HEX32(0,GPIO_Handler.PCOR);

    //Tests out range pin
    TEST_ASSERT_EQUAL(GPIO_error,GPIO_SetPin(&GPIO_Handler,32));

}

void test_SetPin_should_returnError_if_pinSetToInput(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
    GPIO_Handler.PSOR = 0;
    GPIO_Handler.PCOR = 0;

    //Tests if pin is set to Output
    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsInput(&GPIO_Handler,0));
    TEST_ASSERT_EQUAL(GPIO_error,GPIO_SetPin(&GPIO_Handler,0));

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsOutput(&GPIO_Handler,0));
    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPin(&GPIO_Handler,0));
}

void test_SetPin_should_HandleReversedPins(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
  
    GPIO_Init(&GPIO_Handler);
    GPIO_Handler.PSOR = 0;
    GPIO_Handler.PCOR = 0;

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsOutput(&GPIO_Handler,1));
    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPin(&GPIO_Handler,1));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(1),GPIO_Handler.PCOR);
    TEST_ASSERT_EQUAL_HEX32(0,GPIO_Handler.PSOR);

}

/*******************************************************************************************
 * GPIO_ResetPin
 * ACTION: Set the pin LOW
 * CONDITION: Valid Pin, Pin set as Output
 *******************************************************************************************/


void test_ResetPin_should_SetPinLow(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
    GPIO_Handler.PSOR = 0;
    GPIO_Handler.PCOR = 0;

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsOutput(&GPIO_Handler,0));
    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_ResetPin(&GPIO_Handler,0));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0),GPIO_Handler.PCOR);
    TEST_ASSERT_EQUAL_HEX32(0,GPIO_Handler.PSOR);

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsOutput(&GPIO_Handler,16));
    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_ResetPin(&GPIO_Handler,16));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(16) | BIT_TO_MASK(0),GPIO_Handler.PCOR);
    TEST_ASSERT_EQUAL_HEX32(0,GPIO_Handler.PSOR);

    //Tests out range pin
    TEST_ASSERT_EQUAL(GPIO_error,GPIO_SetPin(&GPIO_Handler,32));

}

/*******************************************************************************************
 * GPIO_SetPinAsOutput
 * Verify if the function configures the register
 * Verify if return error if configures an invalid pin
 *******************************************************************************************/

void test_SetPinAsOutput_should_ConfigurePinDirection(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
    GPIO_Handler.PDDR = 0;

    GPIO_SetPinAsOutput(&GPIO_Handler,0);
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0),GPIO_Handler.PDDR);

    GPIO_SetPinAsOutput(&GPIO_Handler,1);
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0) | BIT_TO_MASK(1),GPIO_Handler.PDDR);

    GPIO_Handler.PDDR = 0;

    GPIO_SetPinAsOutput(&GPIO_Handler,22);
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(22),GPIO_Handler.PDDR);
}


void test_SetPinAsOutput_shouldnot_updatepindirection_when_invalidPin(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;

    TEST_ASSERT_NOT_EQUAL(GPIO_ok,GPIO_SetPinAsOutput(&GPIO_Handler,32));
    TEST_ASSERT_EQUAL_HEX32(0,GPIO_Handler.PDDR);

}
/*******************************************************************************************
 * GPIO_SetPinAsInput
 *******************************************************************************************/


void test_SetPinAsInput_should_ConfigurePinDirection(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
    GPIO_Handler.PDDR = 0xFFFFFFFF;
    
    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsInput(&GPIO_Handler,0));
    TEST_ASSERT_EQUAL_HEX32(~BIT_TO_MASK(0),GPIO_Handler.PDDR);

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsInput(&GPIO_Handler,1));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(1)),GPIO_Handler.PDDR);

    GPIO_Handler.PDDR = 0xFFFFFFFF;

    TEST_ASSERT_EQUAL(GPIO_ok,GPIO_SetPinAsInput(&GPIO_Handler,22));
    TEST_ASSERT_EQUAL_HEX32(~BIT_TO_MASK(22),GPIO_Handler.PDDR);
}


void test_SetPinAsInput_shouldnot_updatepindirection_when_invalidPin(void)
{
    REGISTERS_GPIO_T GPIO_Handler;
    GPIO_Handler = PORTC;
    GPIO_Handler.PDDR = 0xFFFFFFFF;

    TEST_ASSERT_NOT_EQUAL(GPIO_ok,GPIO_SetPinAsInput(&GPIO_Handler,32));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF,GPIO_Handler.PDDR);
}

    



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_Init_should_ConfigurePins);

    RUN_TEST(test_SetPinAsOutput_should_ConfigurePinDirection);
    RUN_TEST(test_SetPinAsOutput_shouldnot_updatepindirection_when_invalidPin);
    
    RUN_TEST(test_SetPinAsInput_should_ConfigurePinDirection);
    RUN_TEST(test_SetPinAsInput_shouldnot_updatepindirection_when_invalidPin);
    
    RUN_TEST(test_SetPin_should_setpinHigh);
    RUN_TEST(test_SetPin_should_returnError_if_pinSetToInput);
    RUN_TEST(test_ResetPin_should_SetPinLow);
    RUN_TEST(test_SetPin_should_HandleReversedPins);
    
    RUN_TEST(test_ReadPin_returnValue);

    RUN_TEST(test_ReadPort_should_ShowProperValuesForReversedPins);
    

    return UNITY_END();
}
