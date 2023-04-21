/*main.c - 전체 프로그램 실행
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/04/21
*/

#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"


extern yylex();
extern char* yytext;

void extern printtoken(enum tokentypes tn);

void main()
{
    nextid = 0;
    nextSTfree = 0;
    cErrors = 0;
    line = 1;

    enum tokentypes tn;  // token number
    enum errorTypes error;
    line = 1;

    printf("Line number\tToken type\tST-index\tToken\n");
    while ((tn = yylex()) != TEOF) {
        printtoken(tn);
    }
    if (cErrors == 0) printf("No errors detected");
    else printf("%d errors detected\n", cErrors);
    printf("\n\n");

}
