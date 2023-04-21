/* printtoken.c - 들어온 토큰을 종류에 맞게 분류 
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/04/21
*/
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
extern void ReportError(char* string);
extern void PrintError(enum errorTypes error, char *string);
int extern yylex();
extern char* yytext;

void printtoken(enum tnumber tn) {
    if (tn == TSEPARATOR) {
        return;
    } else if (tn == TLINE) {
        line++;
        return;
    } else {
        printf("%d\t", line);

        switch (tn) {
            case TCONST:
                printf("Constant\t");
                break;
            case TELSE:
                printf("Else\t");
                break;
            case TIF:
                printf("If\t");
                break;
            case TINT:
                printf("Integer\t");
                break;
            case TRETURN:
                printf("Return\t");
                break;
            case TVOID:
                printf("Void\t");
                break;
            case TWHILE:
                printf("While\t");
                break;

            case TPLUS:
                printf("Plus\t");
                break;
            case TMINUS:
                printf("Minus\t");
                break;
            case TSTAR:
                printf("Star\t");
                break;
            case TSLASH:
                printf("Slash\t");
                break;
            case TMOD:
                printf("Mod\t");
                break;

            case TASSIGN:
                printf("Assign\t");
                break;
            case TADDASSIGN:
                printf("Add and Assign\t");
                break;
            case TSUBASSIGN:
                printf("Subtract and Assign\t");
                break;
            case TMULASSIGN:
                printf("Multiply and Assign\t");
                break;
            case TDIVASSIGN:
                printf("Divide and Assign\t");
                break;
            case TMODASSIGN:
                printf("Mod and Assign\t");
                break;

            case TNOT:
                printf("Not\t");
                break;
            case TAND:
                printf("And\t");
                break;
            case TOR:
                printf("Or\t");
                break;

            case TEQUAL:
                printf("Equal\t");
                break;
            case TNOTEQU:
                printf("Not Equal\t");
                break;
            case TLESS:
                printf("Less\t");
                break;
            case TGREAT:
                printf("Great\t");
                break;
            case TLESSE:
                printf("Less Equal\t");
                break;
            case TGREATE:
                printf("Great Equal\t");
                break;

            case TINC:
                printf("Increase\t");
                break;
            case TDEC:
                printf("Decrease\t");
                break;

            case TLSBRACKET:
                printf("Left Small Bracket\t");
                break;
            case TRSBRACKET:
                printf("Right Small Bracket\t");
                break;
            case TCOMMA:
                printf("Comma\t");
                break;
            case TLMBRACKET:
                printf("Left Medium Bracket\t");
                break;
            case TRMBRACKET:
                printf("Right Medium Bracket\t");
                break;
            case TLLBRACKET:
                printf("Left Large Bracket\t");
                break;
            case TRLBRACKET:
                printf("Right Large Bracket\t");
                break;
            case TSEMICOLON:
                printf("Semicolon\t");
                break;
            case TIDENT:
                ReportError(yytext);
                break; //인식한 identifier의 오류를 점검
            case TNUMBER:
                printf("Number: %d\t", atoi(yytext));
                break;
            case TCOMMENT:
                printf("Comment Line\t");
                break;
            case TILLID:
                PrintError(illid, yytext);
                break; //숫자로 시작하는 identifier일 때 오류 출력
            case TERROR:
                PrintError(illsp, yytext);
                break; //illegal symbol일 때 출력
        }
        printf("\n");
    }
}
