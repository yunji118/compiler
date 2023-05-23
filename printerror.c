/* printerror.c - Check identifier error
* programmer - ������, �赵��, �����, ������
* date - 2023/04/26
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

#define isLetter(x) ((((x>='a'&&(x)<='z') || ((x)>='A'&&(x)<='Z')) || (x=='_')))
#define isDigit(x) ((x) >= '0' && (x) <= '9')

typedef enum errorTypes ERROR;
ERROR error = noerror;

/*
* PrintError �Լ�: errorTypes ��ü ������ �������� ERROR ������ ���
*
* error: illid(���ڿ� �Բ� �����ϴ� �ĺ��� ����)
*        illlen(�ĺ��ڱ���idlen�� �Ѵ� �ĺ��� ����)
*        illchar(������ ���� ���ڰ� ���� ��� ����)
*        overst(ũ��� overflow �߻�)
*/

void PrintError(enum errorTypes error, char* string) {
    int i;
    switch (error) {
    case overst:
        printf("***Error***\t\t\t\tOVERFLOW\n");
        ++cErrors;
        exit(0);
        break;
    case illid:
        printf("***Error***\t\t\t\t%s illegal IDENT", string);
        ++cErrors;
        break;
    case illlen:
        printf("***Error***\t\t\t%s over 10 words", string);
        ++cErrors;
        break;
    case illchar:
        printf("***Error***\t\t\t\t");
        ++cErrors;
        for (i = 0; i < (int)strlen(string); i++) {
            if (!isLetter(string[i]) && !isDigit(string[i]))
            {
                printf("%c ", string[i]);
            }
        }
        printf("illegal Character");
        break;
    }
}

yyerror(sb)
char* sb;
{
    printf("%s\n", sb);
}