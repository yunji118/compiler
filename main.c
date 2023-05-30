/*main.c - 전체 프로그램 실행
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/04/26
*/

#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"

extern yylex();
int extern yyparse();
extern char* yytext;

void PrintHStable()
{
    int i, j;
    HTpointer here;

    printf("\n\n\n\n\n [[ HASH TABLE ]] \n\n");

    for (i = 0; i < HTsize; i++) {
        if (HT[i] != NULL) {
            printf("  Hash Code %3d :", HT[i]->hscode);
            for (here = HT[i]; here != NULL; here = here->next) {
                j = here->index;
                while (ST[j] != '\0' && j < STsize)
                    printf("%c", ST[j++]);
                printf("     ");
            }
            printf("\n");
        }
    }
}

/* main함수 : yylex로 EOF 만날 때까지 토큰 읽어오기 마지막에 전체 에러 개수 출력*/
void main()
{
    nextid = 0;
    nextSTfree = 0;
    cErrors = 0;
    line = 1;

    enum errorTypes error;

    printf("***MiniC parsing begins\n");
    yyparse();
    printf("Parsing ends.***\n");

    PrintHStable();

    printf("\n%d error(s) detected\n", cErrors);

}
