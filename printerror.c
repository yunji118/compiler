#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

#define isLetter(x) ((((x>='a'&&(x)<='z') || ((x)>='A'&&(x)<='Z')) || (x=='_')))
#define isDigit(x) ((x) >= '0' && (x) <= '9')

extern void PrintID();

typedef enum errorTypes ERROR;
ERROR error = noerror;

int found = 0;

void PrintError(ERROR error, char *string)
{
    int i;
    switch (error) {
        case overst:
            printf(" ***Error***      OVERFLOW ");
            exit(0);
            break;
        case illsp:
            printf(" ***Error***        %s            is illegal seperator \n", string);
            break;
        case illid:
            printf(" ***Error***        ");
            PrintID();
            printf("        start with digit \n");
            nextSTfree = nextid;
            break;
        case illlen:
            printf(" ***Error***        ");
            PrintID();
            printf("        too long identifier \n");
            break;
        case wrongid:
            printf(" ***Error***        ");
            PrintID();
            printf("       ");
            for (i = nextid; i < nextSTfree - 1; i++)
            {
                if (!(isDigit(ST[i]) || isLetter(ST[i])))
                    printf("%c ", ST[i]);
            }
            printf("is not allowed\n");
            nextSTfree = nextid;
            break;
    }
}
