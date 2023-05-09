/* glob.h - 프로젝트에 사용된 global variable 정의
* programmer - 김지윤, 김도연, 김원우, 하윤지
* ST - string table
* string - 현재 읽고 있는 token
* nextid - 현재 string table로 들어온 string의 시작 인덱스
* nextSTfree - string table에서 새로 들어온 string이 위치할 index
* line - 해당 토큰의 줄 번호
* cErrors - testdata의 에러 개수
* date - 2023/04/26
*/
#pragma once
#define STsize 1000
#define Strsize 100
char ST[STsize];
char string[Strsize];
int nextid;
int nextSTfree;
int line;
int cErrors;
