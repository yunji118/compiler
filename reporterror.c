/* reporterror.c - identifier error 확인
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/04/26
*/
#include <stdio.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

extern void PrintError(enum errorTypes error, char* string);
extern void ReadID(char* string);
extern void ADDHT(int hscode);
extern void LookupHS(int nid, int hscode);
extern void ComputeHS(int nid, int nfree);

typedef enum errorTypes ERRORtypes;
ERRORtypes error;


/*ReportError 함수 - 현재 들어온 string이 10글자 이내인지 확인 */
void ReportError(char* string) {
    if (strlen(string) > 10) {
        error = illlen;
        PrintError(illlen, string);
    }
    else {
        //글자수 안 넘는 정상 길이 ident
        //여기서 hashtable에 저장!
        ReadID(string); //ST-index 출력
        ComputeHS(nextid, nextSTfree);
        LookupHS(nextid, hashcode);
        //printf("\t\t%s", string);    //읽은 토큰 출력
        if (nextSTfree - nextid - 1 > 10) {
            PrintError(illlen, string);
            nextSTfree = nextid;
        }
        else if (!found) {
            //printf("%6d              ", nextid);
            //printf("%s", string);
            //printf("       (entered)\n");
            ADDHT(hashcode);
        }
        else {
            //printf("%6d              ", sameid);
            //printf("%s", string);
            //printf("       (already existed)\n");
            nextSTfree = nextid;
        }
    }
}

