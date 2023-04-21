#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"
extern void PrintError(enum errorTypes error, char* string);
typedef enum errorTypes ERRORtypes;
ERRORtypes error;

void ReadID(char* string)
{
    nextid = nextSTfree;
    for (int i = 0; i< strlen(string); i++)
    {
        if (nextSTfree >= STsize) //STSize overflow
        {
            error = overst;
            PrintError(error, string);
            break;
        }
        else {
            ST[nextSTfree++] = string[i];
        }
    }

    //하나의 word를 입력하면 자동으로 공백 저장
    ST[nextSTfree++] = '\0';
}
