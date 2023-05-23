/* reporterror.c - identifier error Ȯ��
* programmer - ������, �赵��, �����, ������
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


/*ReportError �Լ� - ���� ���� string�� 10���� �̳����� Ȯ�� */
void ReportError(char* string) {
    if (strlen(string) > 10) {
        error = illlen;
        PrintError(illlen, string);
    }
    else {
        //���ڼ� �� �Ѵ� ���� ���� ident
        //���⼭ hashtable�� ����!
        ReadID(string); //ST-index ���
        ComputeHS(nextid, nextSTfree);
        LookupHS(nextid, hashcode);
        //printf("\t\t%s", string);    //���� ��ū ���
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

