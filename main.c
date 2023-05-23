/*main.c - 전체 프로그램 실행
* programmer - 김지윤, 김도연, 김원우, 하윤지
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

/*Hash code 계산*/
void ComputeHS(int nid, int nfree)
{
    int code, i;
    code = 0; //word 아스키코드 합 변수
    for (i = nid; i < nfree - 1; i++) {
        code += (int)ST[i];
        hashcode = code % HTsize; //아스키코드 합 mod 해시테이블 사이즈 -> hashcode
    }
}

void LookupHS(int nid, int hscode)
{
    HTpointer here; //HT 시작 포인터 손온
    int i, j;

    found = FALSE; //이미 HT에 있는 문자열이면 TRUE 아니면 FALSE
    if (HT[hscode] != NULL) { //NULL이 아닌 경우에만 탐색
        here = HT[hscode];
        while (here != NULL && found == FALSE) {  //동일한 값 찾지 못했고, 연결 리스트의 끝이 아니면 계속 탐색
            found = TRUE; //이미 존재하는 단어로 가정
            i = here->index;   //현재 hash table에 들어있는 단어
            j = nid;      //지금 중복 검사를 하는 단어
            sameid = i;
            //HT의 hscode에 index상에 저장된 단어가 이미 있는 단어인지 검사
            while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {
                if (ST[i] != ST[j])  //다른 단어
                    found = FALSE;
                else {  //현재 글자가 같으면 다음 글자 탐색
                    i++;
                    j++;
                }
            }
            here = here->next; //다음 연결리스트에 저장된 word와 겹치는지 검사
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

    if (isDigit(input)) {    //숫자로 시작하는 경우
        error = illid;
    }

    while (input != EOF && (isLetter(input) || isDigit(input))) {  //숫자, 문자인 경우
        if (nextSTfree == STsize) {  //String Table이 꽉찬 경우
            error = overst;
            PrintError(error);
        }
        //오버플로우가 아니면
        ST[nextSTfree++] = input;
        input = fgetc(fp); //다음 글자 읽어서 구분자 나올 때까지 반복

        //문장 끝이 아니고 구분자/문자/숫자가 아니라면
        while (input != EOF && !(isSeperator(input) || isLetter(input) || isDigit(input))) {
            flag = 1;
            ST[nextSTfree++] = input; //ST배열에 input 넣고
            input = fgetc(fp); //구분자/문자/숫자 나올 때까지 반복
        }
    }
    if (flag == 1 && error != illid) {
        error = illchar; //잘못된 인자임
    }
    //하나의 word를 입력하면 자동으로 공백 저장
    ST[nextSTfree++] = '\0';

    PrintError(error);
}*/

void PrintHStable()
{
    int i, j;   //i = hash table 배열 탐색, j = hash code가 같은 연결리스트 탐색
    HTpointer here;

    printf("\n\n\n\n\n [[ HASH TABLE ]] \n\n");

    for (i = 0; i < HTsize; i++) {  //Hash Table의 모든 요소 탐색
        if (HT[i] != NULL) {  //NULL이 아닌 경우에만 출력
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
    printf("\n김지윤(2076096), 김원우(2076073), 김도연(2076033), 하윤지(2071051)\n");
}

/* main함수 : yylex로 EOF 만날 때까지 토큰 읽어오기 마지막에 전체 에러 개수 출력*/
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