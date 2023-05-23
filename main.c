/*main.c - ��ü ���α׷� ����
* programmer - ������, �赵��, �����, ������
* date - 2023/04/26
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

//extern yylex();
//extern char* yytext;
extern int yyparse();
extern void printtoken(int tn);

//int hashcode;   //hash code of identifier
//int sameid;   //first index of identifier

//int found;   // flag variable for the previous occurence of an indentifier

enum errorTypes error;

/*Hash code ���*/
void ComputeHS(int nid, int nfree)
{
    int code, i;
    code = 0; //word �ƽ�Ű�ڵ� �� ����
    for (i = nid; i < nfree - 1; i++) {
        code += (int)ST[i];
        hashcode = code % HTsize; //�ƽ�Ű�ڵ� �� mod �ؽ����̺� ������ -> hashcode
    }
}

void LookupHS(int nid, int hscode)
{
    HTpointer here; //HT ���� ������ �տ�
    int i, j;

    found = FALSE; //�̹� HT�� �ִ� ���ڿ��̸� TRUE �ƴϸ� FALSE
    if (HT[hscode] != NULL) { //NULL�� �ƴ� ��쿡�� Ž��
        here = HT[hscode];
        while (here != NULL && found == FALSE) {  //������ �� ã�� ���߰�, ���� ����Ʈ�� ���� �ƴϸ� ��� Ž��
            found = TRUE; //�̹� �����ϴ� �ܾ�� ����
            i = here->index;   //���� hash table�� ����ִ� �ܾ�
            j = nid;      //���� �ߺ� �˻縦 �ϴ� �ܾ�
            sameid = i;
            //HT�� hscode�� index�� ����� �ܾ �̹� �ִ� �ܾ����� �˻�
            while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {
                if (ST[i] != ST[j])  //�ٸ� �ܾ�
                    found = FALSE;
                else {  //���� ���ڰ� ������ ���� ���� Ž��
                    i++;
                    j++;
                }
            }
            here = here->next; //���� ���Ḯ��Ʈ�� ����� word�� ��ġ���� �˻�
        }
    }
}

void ADDHT(int hscode)
{
    HTpointer ptr;

    ptr = (HTpointer)malloc(sizeof(ptr));
    ptr->index = nextid;
    ptr->next = HT[hscode];
    HT[hscode] = ptr;
}

/*
void ReadID()
{
    int flag = 0;

    nextid = nextSTfree;

    if (isDigit(input)) {    //���ڷ� �����ϴ� ���
        error = illid;
    }

    while (input != EOF && (isLetter(input) || isDigit(input))) {  //����, ������ ���
        if (nextSTfree == STsize) {  //String Table�� ���� ���
            error = overst;
            PrintError(error);
        }
        //�����÷ο찡 �ƴϸ�
        ST[nextSTfree++] = input;
        input = fgetc(fp); //���� ���� �о ������ ���� ������ �ݺ�

        //���� ���� �ƴϰ� ������/����/���ڰ� �ƴ϶��
        while (input != EOF && !(isSeperator(input) || isLetter(input) || isDigit(input))) {
            flag = 1;
            ST[nextSTfree++] = input; //ST�迭�� input �ְ�
            input = fgetc(fp); //������/����/���� ���� ������ �ݺ�
        }
    }
    if (flag == 1 && error != illid) {
        error = illchar; //�߸��� ������
    }
    //�ϳ��� word�� �Է��ϸ� �ڵ����� ���� ����
    ST[nextSTfree++] = '\0';

    PrintError(error);
}*/

void PrintHStable()
{
    int i, j;   //i = hash table �迭 Ž��, j = hash code�� ���� ���Ḯ��Ʈ Ž��
    HTpointer here;

    printf("\n\n\n\n\n [[ HASH TABLE ]] \n\n");

    for (i = 0; i < HTsize; i++) {  //Hash Table�� ��� ��� Ž��
        if (HT[i] != NULL) {  //NULL�� �ƴ� ��쿡�� ���
            printf("  Hash Code %3d :", i);
            for (here = HT[i]; here != NULL; here = here->next) {
                j = here->index;
                while (ST[j] != '\0' && j < STsize)
                    printf("%c", ST[j++]);
                printf("     ");
            }
            printf("\n");
        }
    }
    printf("\n\n\n < %5d characters are used in the string table >\n", nextSTfree);
    printf("\n������(2076096), �����(2076073), �赵��(2076033), ������(2071051)\n");
}

/* main�Լ� : yylex�� EOF ���� ������ ��ū �о���� �������� ��ü ���� ���� ���*/
void main()
{
    nextid = 0;
    nextSTfree = 0;
    cErrors = 0;
    line = 1;

    int tn;  // token number
 //   enum errorTypes error;

 //   printf("Line number\tToken type\tST-index\tToken\n");
 //   while ((tn = yylex()) != TEOF) {
 //       printtoken(tn);
  //  }
    printf("***MiniC parsing begins\n");
    yyparse();
    printf("Parsing ends.***\n");

    if (cErrors == 0) printf("No errors detected");
    else printf("%d errors detected\n", cErrors);
    PrintHStable();
    printf("\n\n");

}