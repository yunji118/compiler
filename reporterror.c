#include <stdio.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

extern void ReadID(char* string);
extern void printerror(enum errorTypes error, char* string);

typedef enum errorTypes ERROR;
ERROR error;

void reporterror(char* string) {
    if(strlen(string)>10) {
        error = illlen;
        printerror(illlen, string);
    } else {
        //글자수 안 넘는 정상 길이 ident
        printf("ident\t");
        ReadID(string); //ST-index 출력
        printf("\t%s”", string);    //읽은 토큰 출력
    }
}
