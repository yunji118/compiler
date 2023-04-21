/* symtable.c - 각 identifier의 Hash Table 구성
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/04/21
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"


#define STsize 1000
#define Isize 25

extern void PrintError(enum errorTypes error, char* string);

typedef enum errorTypes ERROR;
ERROR error;

char separators[] = " \t\r\n";
//char ST[STsize];
//char string[Isize];
extern void ReportError(char* string);


//ReadID 함수: string 읽어서 ST에 넣기(overst 에러 체크)
void ReadID(char* string)
{
    nextid = nextSTfree;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (nextSTfree >= STsize) //STSize overflow
        {
            PrintError(overst, string);
            break;
        }
        else {
            ST[nextSTfree++] = string[i];
        }
    }
    printf("   %d", nextid);  //symbol table에서 현재 token이 저장된 인덱스 출력
}


// SymTable 함수: Hash Table 전체 시스템 구성
void SymTable(char* string) {
    ReadID(string);
    ST[nextSTfree++] = '\0';
}
