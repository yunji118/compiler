#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "testdata.txt"

#define STsize 1000   //size of string table
#define HTsize 100     //size of hash table

#define FALSE 0
#define TRUE 1

#define isLetter(x) (((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'Z') || (x) == '_')  // 언더바 추가
#define isDigit(x) ((x) >= '0' && (x) <= '9')

typedef struct HTentry* HTpointer;
typedef struct HTentry {
    int index;  //index of identifier in ST
    HTpointer next;  //pointer to next identifier
}HTentry;

enum errorTypes{noerror, illsp, illid, overst, illlen, wrongid};   // illlen추가(길이가 10초과인 경우), wrongid는 잘못된 인자가 있는 경우
typedef enum errorTypes ERRORtypes;

char seperators[] = " .,;:?!\t\n";

HTpointer HT[HTsize];
char ST[STsize];

int nextid = 0;  //the current identifier
int nextSTfree = 0;  //the next available index of ST

int hashcode;   //hash code of identifier
int sameid;   //first index of identifier

int found;   // flag variable for the previous occurence of an indentifier

ERRORtypes error;

FILE* fp;    //to be a pointer to FILE
char input;    //current read character from FILE

//txt파일을 한글자씩 읽음
void initialize()
{
    fp = fopen(FILE_NAME, "r");
    input = fgetc(fp);
}

void PrintHeading()
{
    printf("\n\n");
    printf("  -----------   ------------ \n");
    printf("  Index in ST    identifier  \n");
    printf("  -----------   ------------ \n");
    printf("\n");
}

/*구분자 판별하는 함수. 구분자인 경우 1을 반환. 구분자 아닐 경우 0을 반환*/
int isSeperator(char c)
{
    int i;
    int sep_len;

    sep_len = strlen(seperators);   //구분자 배열의 길이 (=구분자의 개수)
    for (i = 0; i < sep_len; i++) { //길이만큼 반복함
        if (c == seperators[i]) //배열내에 존재하면
            return 1; //구분자 o
    }
    return 0; //구분자 x
}

/*Hash Table 출력*/
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
}

void PrintError(ERRORtypes error)
{
    int i;

    switch (error){
        case overst :
            printf(" ***Error***      OVERFLOW ");
            PrintHStable();
            exit(0);
            break;
        case illsp :
            printf(" ***Error***        %c            is illegal seperator \n", input);
            break;
        case illid :
            printf(" ***Error***        ");
            while (input != EOF && (isLetter(input) || isDigit(input))) {
                printf("%c", input);
                input = fgetc(fp);
            }
            printf("        start with digit \n");
            break;
        case illlen :
            printf(" ***Error***        ");
            for (i = nextid; i < nextSTfree - 1; i++)
                printf("%c", ST[i]);
            printf("        too long identifier \n");
            break;
        case wrongid :
            printf(" ***Error***        ");
            for (int i = nextid; i < nextSTfree; i++)
            {
                printf("%c", ST[i]);
            }
            printf("       ");
            for (i = nextid; i < nextSTfree; i++)
            {
                if (!(isDigit(ST[i]) || isLetter(ST[i])))
                    printf("%c ", ST[i]);
            }
            printf("is not allowed\n");
            break;
    }
}

/* 9개의 구분자(spaces tabs . , : ; ? ! \n) 건너뛰는 함수*/
void SkipSeperators()
{
    while (input != EOF && !(isLetter(input) || isDigit(input)))
    { //파일의 끝이 아니면서 유효한 문자나 숫자가 아닌 경우
        if (!isSeperator(input)) {  //구분자가 아니고
            error = illsp;
            PrintError(error);
        }
        input = fgetc(fp); //다음 글자 읽어서 반복
    } //문자, 숫자면 while loop 탈출
}

//txt에 적힌 하나의 word를 ST로 옮기는 함수
void ReadID()
{
    int flag = 0;

    nextid = nextSTfree;
    if (isDigit(input)) {    //숫자로 시작하는 경우
        error = illid;
        PrintError(error);
    }
    else {  //문자로 시작
        while (input != EOF && (isLetter(input) || isDigit(input))) {  //숫자, 문자인 경우
            if (nextSTfree == STsize) {  //String Table이 꽉찬 경우
                error = overst;
                PrintError(error);
            } //오버플로우가 아니면
            ST[nextSTfree++] = input;
            input = fgetc(fp); //다음 글자 읽어서 구분자 나올 때까지 반복
            //문장 끝이 아니고 구분자/문자/숫자가 아니라면
            while (input != EOF && !(isSeperator(input) || isLetter(input) || isDigit(input))) {
                flag = 1;
                ST[nextSTfree++] = input; //ST배열에 input 넣고
                input = fgetc(fp); //구분자/문자/숫자 나올 때까지 반복
            }
        }
        if (flag == 1) {
            error = wrongid; //잘못된 인자임
            PrintError(error);
            nextSTfree = nextid;
        }
    }
}

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

int main()
{
    int i;
    PrintHeading(); //header 프린트
    initialize(); //txt파일에서 한 글자를 input 변수에 넣음

    while (input != EOF)
    {
        error = noerror;
        //word의 처음이 숫자/문장일 때까지 반복
        SkipSeperators(); //word의 처음이 구분자면, skip. 잘못된 구분자면, error.
        //인자로 들어갈 수 있는 input은 문자/숫자만 가능
        ReadID(); //구분자(잘못된 구분자 포함)가 나오기 전까지 문자/숫자로 이루어진 word를 ST테이블에 저장
        SkipSeperators();

        //ST에 넣은 word를 HT에 배치
        if (error != illid && error != wrongid) {
            //nestSTfree는 값을 넣은 후에 ++되므로, ++된 이후에 한번도 overflow검사를 진행하지 않았기때문에 한번 더 검사
            if (nextSTfree == STsize) {
                error = overst;
                PrintError(error); //overflow되면 종료
            }
            //하나의 word를 입력하면 자동으로 공백 저장
            ST[nextSTfree++] = '\0';

            ComputeHS(nextid, nextSTfree);
            LookupHS(nextid, hashcode);

            if (nextSTfree - nextid - 1 > 10) {
                error = illlen;
                PrintError(error);
                nextSTfree = nextid;
            }
            else if (!found) {
                printf("%6d              ", nextid);
                for (i = nextid; i < nextSTfree - 1; i++) {
                    printf("%c", ST[i]);
                }
                printf("       (entered)\n");
                ADDHT(hashcode);
            }
            else {
                printf("%6d              ", sameid);
                for (i = nextid; i < nextSTfree - 1; i++)
                    printf("%c", ST[i]);
                printf("       (already existed)\n");
                nextSTfree = nextid;
            }
        }
    }
    PrintHStable();
}
