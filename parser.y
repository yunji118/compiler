%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "glob.h"

int param=0;
int type_void;
int type_int;
int type_char;
int type_const;
int type_string;
int line;
int isArray;
int isFunc;

void updateAttribute();
extern yylex();
extern int yyerror(char *s);
extern void ComputeHS(char* string);

/*yacc source for Mini C*/
%}

%error-verbose

%union
{
        char *id;
}

%nonassoc TLOWERTHANELSE
%nonassoc TELSE

%token <id> TIDENT
%token TNUMBER TCONST TELSE TIF  TINT TRETURN TVOID TWHILE
%token TADDASSIGN TSUBASSIGN TMULASSIGN TDIVASSIGN TMODASSIGN
%token TOR TAND TEQUAL TNOTEQU TGREATE TLESSE TINC TDEC
%token TPLUS TMINUS TSTAR TSLASH TMOD TASSIGN TNOT TLESS TGREAT
%token TLSBRACKET TRSBRACKET TCOMMA TLMBRACKET TRMBRACKET TLLBRACKET TRLBRACKET TSEMICOLON TCOMMENT TSEPERATOR TLINE TILLID error

%%
mini_c             : translation_unit   ;
translation_unit       : external_dcl
               | translation_unit external_dcl
               ;
external_dcl         : function_def
                 | declaration
               ;
function_def          : function_header compound_st
                     ;
//함수 헤더 선언자+함수이름+매개변수
function_header       : dcl_spec function_name formal_param
                     ;
//선언자 집합
dcl_spec             : dcl_specifiers  ;
//선언자 나열한거
dcl_specifiers          : dcl_specifier
         | dcl_specifiers dcl_specifier
         ;
//선언자는 TCONST, TINT, TVOID
dcl_specifier          : type_qualifier
               | type_specifier
               ;
type_qualifier          : TCONST    ;
type_specifier          : TINT      ;
         | TVOID
         ;
//함수 이름은 식별자
function_name     : TIDENT
		  | //함수 이름 없는 경우
		  {
		    yyerrok;
		    yyerror("no function name");
		  }
		 ;
//매개변수 감싸는 괄호 (a, b, c)
formal_param       : TLSBRACKET opt_formal_param TRSBRACKET //opt_formal_param은 존재 유무만
         | TLSBRACKET opt_formal_param error
         {
            yyerrok;
            yyerror("no right small bracket");
         }
         ;
//매개변수 있을 수도 없을 수도
opt_formal_param       : formal_param_list //매개변수 목록
                  | //매개변수 없으면 이거
                  ;
//매개변수 목록
formal_param_list       : param_dcl //매개변수
                   | formal_param_list TCOMMA param_dcl //매개변수는 ,로 구분되어 연결
                  ;
//매개변수 선언
param_dcl          : dcl_spec declarator //dcl_spec: 변수 타입 + declarator: 변수 이름
                  ;
//구문 감싸는 중괄호
compound_st        : TLMBRACKET opt_dcl_list opt_stat_list TRMBRACKET
         | TLMBRACKET opt_dcl_list opt_stat_list error
         {
            yyerrok;
            yyerror("no right medium bracket");
         }
         ;
//변수 선언 있을 수도 없을 수도
opt_dcl_list          : declaration_list //존재하면 선언된 변수 목록
               | //없으면 이거
               ;
//선언된 변수 목록
declaration_list       : declaration //하나일 때
               | declaration_list declaration //하나 이상일 때
               ;
declaration          : dcl_spec init_dcl_list TSEMICOLON //변수 타입 + 변수 선언 목록 + ;
         | dcl_spec init_dcl_list error
         {
            yyerrok;
            yyerror("no semicolon");
         }
         ;
//쉼표로 구분되어 선언된 변수 목록
init_dcl_list          : init_declarator //변수 하나 선언
         | init_dcl_list TCOMMA init_declarator //변수 한 줄에 여러개 선언할 때 쉼표로 구분
         | init_dcl_list init_declarator error
         {
            yyerrok;
            yyerror("no comma");
         }
         ;
//변수 하나
init_declarator       : declarator //변수 이름 식별자+[]?
                | declarator TASSIGN TNUMBER //변수 이름에 숫자 할당
               ;
//변수 이름(식별자)
declarator          : TIDENT //변수 이름
			{
				updateAttribute();
			}
		 | TIDENT TLLBRACKET opt_number TRLBRACKET //배열 변수
		 | TIDENT TLLBRACKET opt_number error
		  {
		    yyerrok;
		    yyerror("no right large bracket");
		  }
		 ;
//숫자 있을 수도 없을 수도
opt_number          : TNUMBER //있으면 숫자주고
                    | //없으면 공백
                  ;
//문장 목록 있을 수도 없을 수도
opt_stat_list          : statement_list //있으면 문장 목ㄹ고
                | //없으면 이거
               ;
//문장 목록
statement_list          : statement //문장 하나
                | statement_list statement //문장 여러개
               ;
//문장 하나
statement          : compound_st //중괄호로 감싸진 구문
                  | expression_st //표현문
         | if_st //if문
         | while_st //while문
         | return_st //return 문
         ;
//표현문
expression_st       : opt_expression TSEMICOLON //표현식 + ;
                  ;
//표현식 있을 수도 없을 수도
opt_expression       : expression
           |
         ;
//if(조건)문 + if(조건) else문
if_st                : TIF TLSBRACKET expression TRSBRACKET statement %prec TLOWERTHANELSE
               | TIF TLSBRACKET expression TRSBRACKET statement TELSE statement
         | TIF TLSBRACKET expression error
         {
            yyerrok;
            yyerror("no right small bracket");
         }
         ;
//while(조건)문
while_st            : TWHILE TLSBRACKET expression TRSBRACKET statement
         | TWHILE TLSBRACKET expression error
         {
            yyerrok;
            yyerror("no right small bracket");
         }
         ;
return_st          : TRETURN opt_expression TSEMICOLON    ;
//표현식이 뭐임 씨앙
expression          : assignment_exp     ;
//표현식에 들어갈 수 있는 애들
assignment_exp       : logical_or_exp //a||b
         | unary_exp TASSIGN assignment_exp //x=5
         | unary_exp TADDASSIGN assignment_exp //x+=5
         | unary_exp TSUBASSIGN assignment_exp //x-=5
         | unary_exp TMULASSIGN assignment_exp //x*=5
         | unary_exp TDIVASSIGN assignment_exp //x/=5
         | unary_exp TMODASSIGN assignment_exp //x%=5
         ;
logical_or_exp       : logical_and_exp
               | logical_or_exp TOR logical_and_exp
               ;
logical_and_exp       : equality_exp
                | logical_and_exp TAND equality_exp
               ;
equality_exp          : relational_exp
         | equality_exp TEQUAL relational_exp
         | equality_exp TNOTEQU relational_exp
         ;
relational_exp       : additive_exp
         | relational_exp TGREAT additive_exp
         | relational_exp TLESS additive_exp
         | relational_exp TGREATE additive_exp
         | relational_exp TLESSE additive_exp
         ;
additive_exp          : multiplicative_exp
               | additive_exp TPLUS multiplicative_exp
               | additive_exp TMINUS multiplicative_exp
               ;
multiplicative_exp       : unary_exp
                   | multiplicative_exp TSTAR unary_exp
                   | multiplicative_exp TSLASH unary_exp
                   | multiplicative_exp TMOD unary_exp
                  ;
//단항식(항 하나)
unary_exp          : postfix_exp
             | TMINUS unary_exp
             | TNOT unary_exp
             | TINC unary_exp
             | TDEC unary_exp
            ;
//후위표기식
postfix_exp          : primary_exp
              | postfix_exp TLLBRACKET expression TRLBRACKET
              | postfix_exp TLSBRACKET opt_actual_param TRSBRACKET
              | postfix_exp TINC
              | postfix_exp TDEC
              ;
opt_actual_param       : actual_param
                 |
               ;
actual_param          : actual_param_list
                     ;
actual_param_list       : assignment_exp
                  | actual_param_list TCOMMA assignment_exp
                  ;
primary_exp          : TIDENT
                    | TNUMBER
                    | TLSBRACKET expression TRSBRACKET
                  ;
%%
void updateAttribute()
{
	int code, i, j;
	code = 0;
	for (i = nextid; i < nextSTfree - 1; i++) {
		code += (int)ST[i];
		printf("%c ", ST[i]);
	}

	int hashcode = code % HTsize;

	HTpointer here = HT[hashcode];
	int found=0;

	while (here != NULL && found == 0) {
	    found = 1;
	    i = here->index;
	    j = nextid;

	    while (ST[i] != '\0' && ST[j] != '\0' && found == 1) {
		if (ST[i] != ST[j]) {
		    found = 0;
		    break;
	    	}
		else {
		    i++;
		    j++;
		}
	    }

	    if(!found) {
	    	here = here->next;
	    } else {
	    	break;
	    }
	}

	printf("(%s)\n", here->name);

}
