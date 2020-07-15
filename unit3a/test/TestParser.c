
#include "unity.h"
#include "MyParser.h"
#include "MK20DX256.h"

extern ParserState_t state;

void test_Parser_AddChar_should_StartLookingForCMDonLeftBracket(void)
{
    state = PARSER_LOOKING_FOR_START;

    TEST_ASSERT_NULL(Parser_AddChar('['));

    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_CMD,state);
}

void test_Parser_AddChar_should_RejectNonStartCharWhenLookingForStart(void)
{
    state = PARSER_LOOKING_FOR_START;

    TEST_ASSERT_NULL(Parser_AddChar('"'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);

    TEST_ASSERT_NULL(Parser_AddChar('A'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);
    
    TEST_ASSERT_NULL(Parser_AddChar('g'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);

    TEST_ASSERT_NULL(Parser_AddChar('6'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);
}

void test_Parser_AddChar_should_AcceptValidCommandChar(void)
{
    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('A'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN,state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('N'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN,state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('Z'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN,state);
}

void test_Parser_AddChar_should_RejectInvalidCommandChar(void)
{
    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('@'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('\\'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('a'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);

}

void test_Parser_AddChar_should_AcceptLengthZero(void)
{
    state = PARSER_LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(Parser_AddChar('0'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_END,state);
}


void test_Parser_AddChar_should_RejectInvalidLength(void)
{
    state = PARSER_LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(Parser_AddChar(':'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);

    state = PARSER_LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(Parser_AddChar('/'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);

    state = PARSER_LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(Parser_AddChar('O'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);
}

void test_Parser_AddChar_should_HandleValidPackageWithNoData(void)
{
    TEST_ASSERT_NULL(Parser_AddChar('['));
    TEST_ASSERT_NULL(Parser_AddChar('A'));
    TEST_ASSERT_NULL(Parser_AddChar('0'));
    TEST_ASSERT_EQUAL_STRING("[A0]", Parser_AddChar('['));

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Parser_AddChar_should_StartLookingForCMDonLeftBracket);
    RUN_TEST(test_Parser_AddChar_should_RejectNonStartCharWhenLookingForStart);
    RUN_TEST(test_Parser_AddChar_should_AcceptValidCommandChar);
    RUN_TEST(test_Parser_AddChar_should_RejectInvalidCommandChar);
    RUN_TEST(test_Parser_AddChar_should_AcceptLengthZero);
    RUN_TEST(test_Parser_AddChar_should_RejectInvalidLength);
    RUN_TEST(test_Parser_AddChar_should_HandleValidPackageWithNoData);
    return UNITY_END();
}
