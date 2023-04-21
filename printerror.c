/* printerror.c - Check identifier error
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/04/21
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"


#define isLetter(x) ((((x>='a'&&(x)<='z') || ((x)>='A'&&(x)<='Z')) || (x=='_')))
#define isDigit(x) ((x) >= '0' && (x) <= '9')

int nextid;
int nextSTfree;
int cErrors;

typedef enum errorTypes ERROR;
ERROR error = noerror;


//PrintError 함수: errorTypes 객체 내용을 바탕으로 ERROR 정보를 출력
// error: illsp(허용되지 않는 문자 사용한 식별자 에러)
//        illid(숫자와 함께 시작하는 식별자 에러)
//        illlen(식별자길이idlen을 넘는 식별자 에러)
//        overst(크기로 overflow 발생)


void PrintError(enum errorTypes error, char* string) {
    int i;
    switch (error) {
    case overst:
        printf("***Error***      OVERFLOW");
        ++cErrors;
        exit(0);
        break;
    case illsp:
        printf("***Error***\t\t\t%s illegal seperator", string);
        ++cErrors;
        break;
    case illid:
        printf("***Error***\t\t\t%s illegal IDENT", string);
        ++cErrors;
        break;
    case illlen:
        printf("***Error***\t\t\t%s over 10 words", string);
        ++cErrors;
        break;
    case illchar:
        printf("***Error***\t\t\t");
        ++cErrors;
        for (i = 0; i < strlen(string); i++) {
            if (!isLetter(string[i]) && !isDigit(string[i]))
            {
                printf("%c", string[i]);
            }
        }
        printf("illegal Character");
        break;
    }
}
