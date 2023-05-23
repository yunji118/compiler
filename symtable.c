/* symtable.c - �� identifier�� Hash Table ����
* programmer - ������, �赵��, �����, ������
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



/*ReadID �Լ� : string �о ST�� �ֱ�(overst ���� üũ)*/
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
    printf("ident\t\t\t%d", nextid);  //symbol table���� ���� token�� ����� �ε��� ���
}


/* SymTable �Լ� : Hash Table ��ü �ý��� ���� */
void SymTable(char* string) {
    ReadID(string);
    ST[nextSTfree++] = '\0';
}