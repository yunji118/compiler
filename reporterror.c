#include <stdio.h>
#include <string.h>
#include "tn.h"
#include "glob.h"


extern void PrintError(enum errorTypes error, char* string);


typedef enum errorTypes ERRORtypes;
ERRORtypes error;

extern void ReadID(char* string);

void ReportError(char* string) {
    if (strlen(string) > 10) {
        error = illlen;
        PrintError(illlen, string);
    }
    else {
        //글자수 안 넘는 정상 길이 ident
        printf("ident\t\t");
        ReadID(string); //ST-index 출력
        printf("\t\t%s", string);    //읽은 토큰 출력
    }
}
