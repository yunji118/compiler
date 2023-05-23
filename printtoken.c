/* printtoken.c - ���� ��ū�� ������ �°� �з�
* programmer - ������, �赵��, �����, ������
* date - 2023/04/26
*/
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
extern void ReportError(char* string);
extern void PrintError(enum errorTypes error, char* string);
extern yylex();
extern char* yytext;

/*printtoken �Լ� : token type ���� ���*/
void printtoken(int tn) {
    if (tn == TSEPARATOR) (void)0;
    else if (tn == TLINE) {
        line++;
        return;
    }
    else {
        printf("%5d\t\t", line);
        switch (tn) {
        case TCONST: printf("Constant\t\t\t\t%s", yytext); break;
        case TELSE: printf("Else\t\t\t\t\t%s", yytext); break;
        case TIF: printf("If\t\t\t\t\t\t%s", yytext); break;
        case TINT: printf("Integer\t\t\t\t\t%s", yytext); break;
        case TRETURN: printf("Return\t\t\t\t\t%s", yytext); break;
        case TVOID: printf("Void\t\t\t\t\t%s", yytext); break;
        case TWHILE: printf("While\t\t\t\t\t%s", yytext); break;

        case TPLUS: printf("Plus\t\t\t\t\t%s", yytext); break;
        case TMINUS: printf("Minus\t\t\t\t\t%s", yytext); break;
        case TSTAR: printf("Star\t\t\t\t\t%s", yytext); break;
        case TSLASH: printf("Slash\t\t\t\t\t%s", yytext); break;
        case TMOD: printf("Mod\t\t\t\t\t%s", yytext); break;

        case TASSIGN: printf("Assign\t\t\t\t\t%s", yytext); break;
        case TADDASSIGN: printf("Add and assign\t\t\t%s", yytext); break;
        case TSUBASSIGN: printf("Subtract and assign\t\t%s", yytext); break;
        case TMULASSIGN: printf("Multiply and assign\t\t%s", yytext); break;
        case TDIVASSIGN: printf("Divide and assign\t\t%s", yytext); break;
        case TMODASSIGN: printf("Mod and assign\t\t\t%s", yytext); break;

        case TNOT: printf("Not\t\t\t\t\t\t%s", yytext); break;
        case TAND: printf("And\t\t\t\t\t\t%s", yytext); break;
        case TOR: printf("Or\t\t\t\t\t\t%s", yytext); break;

        case TEQUAL: printf("Equal\t\t\t\t\t%s", yytext); break;
        case TNOTEQU: printf("Not Equal\t\t\t\t%s", yytext); break;
        case TLESS: printf("Less\t\t\t\t\t%s", yytext); break;
        case TGREAT: printf("Great\t\t\t\t\t%s", yytext); break;
        case TLESSE: printf("Less equal\t\t\t\t%s", yytext); break;
        case TGREATE: printf("Great equal\t\t\t\t%s", yytext); break;

        case TINC: printf("Increase\t\t\t\t%s", yytext); break;
        case TDEC: printf("Decrease\t\t\t\t%s", yytext); break;

        case TLSBRACKET: printf("Left Small Bracket\t\t%s", yytext); break;
        case TRSBRACKET: printf("Right Small Bracket\t\t%s", yytext); break;
        case TCOMMA: printf("Comma\t\t\t\t%s", yytext); break;
        case TLMBRACKET: printf("Left Medium Bracket\t\t%s", yytext); break;
        case TRMBRACKET: printf("Right Medium Bracket\t%s", yytext); break;
        case TLLBRACKET: printf("Left Large Bracket\t\t%s", yytext); break;
        case TRLBRACKET: printf("Right Large Bracket\t\t%s", yytext); break;
        case TSEMICOLON: printf("Semicolon\t\t\t\t%s", yytext); break;
        case TIDENT: ReportError(yytext); break; //�ν��� identifier�� ������ ����
        case TNUMBER: printf("Number\t\t\t\t\t%s", yytext); break;  //���⼭ atoi ����ߴ��� 012 -> 12�� ����
        case TSEPARATOR: break;
        case TLINE: break;
        case TILLID: PrintError(illid, yytext); break; //���ڷ� �����ϴ� identifier�� �� ���� ���
        case TERROR: PrintError(illchar, yytext); break; //illegal symbol�� �� ���
        }
        printf("\n");
    }
}
