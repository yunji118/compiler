/* glob.h - ������Ʈ�� ���� global variable ����
* programmer - ������, �赵��, �����, ������
* ST - string table
* string - ���� �а� �ִ� token
* nextid - ���� string table�� ���� string�� ���� �ε���
* nextSTfree - string table���� ���� ���� string�� ��ġ�� index
* line - �ش� ��ū�� �� ��ȣ
* cErrors - testdata�� ���� ����
* date - 2023/04/26
*/
#pragma once
#define STsize 1000
#define HTsize 100
#define Strsize 100

#define FALSE 0
#define TRUE 1

char ST[STsize];
char string[Strsize];
int nextid;
int nextSTfree;
int hashcode;
int line;
int found;
int cErrors;
int sameid;

enum errorTypes { noerror, illsp, illid, overst, illlen, illchar };
typedef struct HTentry* HTpointer;
typedef struct HTentry {
    int index;  //index of identifier in ST
    HTpointer next;  //pointer to next identifier
}HTentry;

HTpointer HT[HTsize];