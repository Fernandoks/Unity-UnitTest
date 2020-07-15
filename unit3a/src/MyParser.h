#ifndef MYPARSER_H
#define MYPARSER_H


typedef enum _PARSER_STATE_T
{
    PARSER_LOOKING_FOR_START = 0,
    PARSER_LOOKING_FOR_CMD,
    PARSER_LOOKING_FOR_LEN,
    PARSER_LOOKING_FOR_DATA,
    PARSER_LOOKING_FOR_END,
} ParserState_t;

char* Parser_AddChar(char NewChar);

#endif //MYPARSER_H
