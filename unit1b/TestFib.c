
#include <limits.h>

#include "unity.h"
#include "Fib.h"

#define DIMENSION_OF(a) (sizeof(a)/sizeof(a[0]))

void test_element0_should_return1(void)
{
    TEST_ASSERT_EQUAL_INT(1,Fibonacci_GetElement(0));

    TEST_ASSERT_EQUAL_INT(1,Fibonacci_IsInSequence(0));
}

void test_element1_should_return1(void)
{
    TEST_ASSERT_EQUAL_INT(1,Fibonacci_GetElement(1));

    TEST_ASSERT_EQUAL_INT(1,Fibonacci_IsInSequence(1));
}

void test_element2_should_return2(void)
{
    TEST_ASSERT_EQUAL_INT(2,Fibonacci_GetElement(2));

    TEST_ASSERT_EQUAL_INT(2,Fibonacci_IsInSequence(2));
}

void test_part_of_the_sequence(void)
{
    int expected[] ={1,1,2,3,5,8,13,21,34,55,89,144};
    int i;
        
    for (i = 0 ; i < DIMENSION_OF(expected); i++)
    {
        TEST_ASSERT_EQUAL_INT(expected[i], Fibonacci_GetElement(i));

        TEST_ASSERT_EQUAL_INT(expected[i], Fibonacci_IsInSequence(i));
    }
}

void test_negative(void)
{
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(-1));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(-3));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(-555));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(INT_MIN));

     TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(-1));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(-3));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(-555));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(INT_MIN));
}



void test_int_limit(void)
{
    const int first_bad_element = 46;
    const int last_good_element = first_bad_element - 1;
    int last_good_value = Fibonacci_GetElement(last_good_element);
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, sizeof(int), "This tests and program assumes 32bits int");
    TEST_ASSERT_MESSAGE(last_good_value > 1, "This value cant be zero");
    
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(first_bad_element));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(INT_MAX));

    TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(first_bad_element));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(INT_MAX));
    
}



void Tests_for_Fibonacci_GetElement(void)
{
    RUN_TEST(test_element0_should_return1);
    RUN_TEST(test_element1_should_return1);
    RUN_TEST(test_element2_should_return2);
    RUN_TEST(test_part_of_the_sequence);
    RUN_TEST(test_negative);
    RUN_TEST(test_int_limit);
}


int main(void) 
{
    UNITY_BEGIN();
    Tests_for_Fibonacci_GetElement();
    
    return UNITY_END();
}

