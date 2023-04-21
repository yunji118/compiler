#include <stdio.h>
#include "tn.h"
#include "glob.h"

int extern yylex();
extern char* yytext;
extern void printtoken(enum tnumber tn);

int main()
{
    enum tnumber tn;  // token number
    line = 1;

    printf("Line number\tToken type\tST-index\tToken\n");
    while ((tn = yylex()) != TEOF) {
        printtoken(tn);
    }

    if (cErrors == 0) printf("No errors detected");
    else printf("%d errors detected\n", cErrors);
    printf("\n\n");

    return 0;
}

