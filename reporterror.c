/* reporterror.c - identifier error 확인
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/05/31
*/
#include <stdio.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

int yyerror(char* s) {
    if (s != "syntax error" && s != "parse error") {
        cErrors++;
        printf("%d\t\t%s\n", cLine, s);
    }
}

extern void PrintError(enum errorTypes error, char* string);

typedef enum errorTypes ERRORtypes;
ERRORtypes error;

extern void ReadID(char* string);

/*ReportError 함수 - 현재 들어온 string이 10글자 이내인지 확인 */
void ReportError(char* string) {
    if (strlen(string) > 10) {
        error = illlen;
        PrintError(illlen, string);
    }
    else {
        //글자수 안 넘는 정상 길이 ident
        ReadID(string); //ST-index 출력
        printf("\t\t%s", string);    //읽은 토큰 출력
    }
}
