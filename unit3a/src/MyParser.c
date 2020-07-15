#include <stdio.h> 

#include "MyParser.h"
#include "MK20DX256.h"

//#define TEST

#ifndef TEST
#define STATIC static
#else
#define STATIC
#endif

#define PARSER_BUFFER_LENGTH_MAX    23

STATIC ParserState_t state = PARSER_LOOKING_FOR_START;

static char buffer[PARSER_BUFFER_LENGTH_MAX];

char* Parser_AddChar(char NewChar)
{
    if (NewChar == '[')
    {
        state = PARSER_LOOKING_FOR_CMD;
    }
    else 
    {
        switch (state)
        {
        case PARSER_LOOKING_FOR_CMD:
            if ( (NewChar >= 'A') && (NewChar <= 'Z') )
            {
                state = PARSER_LOOKING_FOR_LEN;
            }
            else
            {
                state = PARSER_LOOKING_FOR_START;
            }
            
            break;

        case PARSER_LOOKING_FOR_LEN:
            if (NewChar == '0')
            {
                state = PARSER_LOOKING_FOR_END;
            }
            else
            {
                state = PARSER_LOOKING_FOR_START;
            }
            break;

        case PARSER_LOOKING_FOR_END:
            if (NewChar == "]")
            {

            }
            state = PARSER_LOOKING_FOR_START;
            break;
            
        default:
            break;
        }

    }

   
    return NULL;
}