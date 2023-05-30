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

void printType(int type) {
    switch (type) {
        case 1: printf(", integer scalar variable"); break;
        case 2: printf(", void scalar variable"); break;
        case 3: printf(", integer array variable"); break;
        case 4: printf(", function, return type void"); break;
        case 5: printf(", not defined"); break;
        case 6: printf(", float scalar variable"); break;
        case 7: printf(", float array variable"); break;
        case 8: printf(", function, return type int"); break;
        case 9: printf(", function, return type float"); break;
        case 10: printf(", integer scalar parameter"); break;
        case 11: printf(", float scalar parameter"); break;
        case 12: printf(", integer array parameter"); break;
        default: printf(", identifier parse error"); break;
    }
}

void PrintHStable()
{
    int i, j;
    HTpointer here;

    printf("\n\n[[ HASH TABLE ]]\n\n");

    for (i = 0; i < HTsize; i++) {
        if (HT[i] != NULL) {
            printf("Hash Code %3d : ", i);
            for (here = HT[i]; here != NULL; here = here->next) {
                j = here->index;
                printf("(");
                while (ST[j] != '\0' && j < STsize)
                    printf("%c", ST[j++]);
                printType(here->type);
                printf(", line %d)", here->line, here->type);
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
    cLine = 1;

    look_id = (HTpointer)malloc(sizeof(struct HTentry));
    look_tmp = (HTpointer)malloc(sizeof(struct HTentry));

    enum errorTypes error;

    printf("***MiniC parsing begins\n");
    yyparse();
    printf("Parsing ends.***\n");

    PrintHStable();

    printf("\n%d error(s) detected\n", cErrors);

}