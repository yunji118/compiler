/* symtable.c - 각 identifier의 Hash Table 구성
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/04/26
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

extern void PrintError(enum errorTypes error, char* string);
extern void ReportError(char* string);

typedef enum errorTypes ERROR;
ERROR error;

char separators[] = " \t\r\n";
int hashcode;
int found;

void ComputeHS(int nid, int nfree)
{
    int code, i;
    code = 0;
    for (i = nid; i < nfree - 1; i++) {
        code += (int)ST[i];
    }

    hashcode = code % HTsize;
}

void LookupHS(int nid, int hscode)
{
    HTpointer here;
    int i, j;

    found = 0;
    if (HT[hscode] != NULL) {
        here = HT[hscode];
        while (here != NULL && found == 0) {
            found = 1;
            i = here->index;
            j = nid;

            while (ST[i] != '\0' && ST[j] != '\0' && found == 1) {
                if (ST[i] != ST[j])
                    found = 0;
                else {
                    i++;
                    j++;
                }
            }
            here = here->next;
        }
    }
}

void ADDHT(int hscode)
{
    HTpointer ptr;

    ptr = (HTpointer)malloc(sizeof(ptr));
    ptr->index = nextid;
    ptr->next = HT[hscode];
    HT[hscode] = ptr;
}

/*ReadID 함수 : string 읽어서 ST에 넣기(overst 에러 체크)*/
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
    //printf("ident\t\t\t%d", nextid);  //symbol table에서 현재 token이 저장된 인덱스 출력
}


/* SymTable 함수 : Hash Table 전체 시스템 구성 */
void SymTable(char* string) {
    ReadID(string);
    ComputeHS(nextid, nextSTfree);
    LookupHS(nextid, hashcode);

    if (!found) {
        printf("(entered) %s\n", string);
        ADDHT(hashcode);
    }
    else {
        printf("(already existed) %s\n", string);
        nextSTfree = nextid;
    }

    ST[nextSTfree++] = '\0';
}
