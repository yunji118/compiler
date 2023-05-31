/* printerror.c - Check identifier error
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/05/31
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
* PrintError 함수: errorTypes 객체 내용을 바탕으로 ERROR 정보를 출력
*
* error: illid(숫자와 함께 시작하는 식별자 에러)
*        illlen(식별자길이idlen을 넘는 식별자 에러)
*        illchar(허용되지 않은 문자가 들어온 경우 에러)
*        overst(크기로 overflow 발생)
*/

void PrintError(enum errorTypes error, char* string) {
    int i;
    printf("%d\t\t", cLine);
    switch (error) {
    case overst:
        printf("***Error***\t\tOVERFLOW\n");
        ++cErrors;
        exit(0);
        break;
    case illid:
        printf("***Error***\t\t%s start with digit\n", string);
        ++cErrors;
        break;
    case illlen:
        printf("***Error***\t\t%s over 10 words\n", string);
        ++cErrors;
        break;
    case illchar:
        printf("***Error***\t\t");
        ++cErrors;
        for (i = 0; i < strlen(string); i++) {
            if (!isLetter(string[i]) && !isDigit(string[i]))
            {
                printf("%c ", string[i]);
            }
        }
        printf("illegal Character\n");
        break;
    }
}
