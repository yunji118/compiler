%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include "glob.h"

extern yylex();
extern int yyerror(char *s);

/*yacc source for Mini C*/
void semantic(int n);
%}

%nonassoc TLOWERTHANELSE
%nonassoc TELSE

%token TIDENT TNUMBER TCONST TELSE TIF  TINT TRETURN TVOID TWHILE
%token TADDASSIGN TSUBASSIGN TMULASSIGN TDIVASSIGN TMODASSIGN
%token TOR TAND TEQUAL TNOTEQU TGREATE TLESSE TINC TDEC
%token TPLUS TMINUS TSTAR TSLASH TMOD TASSIGN TNOT TLESS TGREAT
%token TLSBRACKET TRSBRACKET TCOMMA TLMBRACKET TRMBRACKET TLLBRACKET TRLBRACKET TSEMICOLON TCOMMENT TSEPERATOR TLINE TILLID TERROR

%%
mini_c          : translation_unit         ;
translation_unit    : external_dcl
         | translation_unit external_dcl
         ;
external_dcl       : function_def
           | declaration
           ;
function_def       : function_header compound_st      ;
function_header    : dcl_spec function_name formal_param   ;
dcl_spec       : dcl_specifiers         ;
dcl_specifiers       : dcl_specifier
          | dcl_specifiers dcl_specifier
          ;
dcl_specifier       : type_qualifier
         | type_specifier
         ;
type_qualifier       : TCONST            ;
type_specifier       : TINT
          | TVOID
          ;
function_name    : TIDENT               ;
formal_param       : TLSBRACKET opt_formal_param TRSBRACKET      ;
opt_formal_param    : formal_param_list
            |              ;
formal_param_list    : param_dcl
             | formal_param_list TCOMMA param_dcl    ;
param_dcl       : dcl_spec declarator         ;
compound_st       : TLMBRACKET opt_dcl_list opt_stat_list TRMBRACKET    ;
opt_dcl_list       : declaration_list
         |
         ;
declaration_list    : declaration
         | declaration_list declaration
         ;
declaration       : dcl_spec init_dcl_list TSEMICOLON      ;
init_dcl_list       : init_declarator
         | init_dcl_list TCOMMA init_declarator
         ;
init_declarator    : declarator
          | declarator TASSIGN TNUMBER
          ;
declarator       : TIDENT
              | TIDENT TLLBRACKET opt_number TRLBRACKET
              ;
opt_number       : TNUMBER
              |
              ;
opt_stat_list       : statement_list
          |
          ;
statement_list       : statement
          | statement_list statement
          ;
statement       : compound_st
            | expression_st
            | if_st
            | while_st
            | return_st
            ;
expression_st    : opt_expression TSEMICOLON         ;
opt_expression    : expression
          |
if_st          : TIF TLSBRACKET expression TRSBRACKET statement %prec TLOWERTHANELSE
         | TIF TLSBRACKET expression TRSBRACKET statement TELSE statement
while_st       : TWHILE TLSBRACKET expression TRSBRACKET statement    ;
return_st       : TRETURN opt_expression TSEMICOLON      ;
expression       : assignment_exp         ;
assignment_exp    : logical_or_exp
         | unary_exp TASSIGN assignment_exp
         | unary_exp TADDASSIGN assignment_exp
         | unary_exp TSUBASSIGN assignment_exp
         | unary_exp TMULASSIGN assignment_exp
         | unary_exp TDIVASSIGN assignment_exp
         | unary_exp TMODASSIGN assignment_exp
         ;
logical_or_exp    : logical_and_exp
         | logical_or_exp TOR logical_and_exp
         ;
logical_and_exp    : equality_exp
          | logical_and_exp TAND equality_exp
          ;
equality_exp       : relational_exp
         | equality_exp TEQUAL relational_exp
         | equality_exp TNOTEQU relational_exp
         ;
relational_exp    : additive_exp
         | relational_exp TGREAT additive_exp
         | relational_exp TLESS additive_exp
         | relational_exp TGREATE additive_exp
         | relational_exp TLESSE additive_exp
         ;
additive_exp       : multiplicative_exp
         | additive_exp TPLUS multiplicative_exp
         | additive_exp TMINUS multiplicative_exp
         ;
multiplicative_exp    : unary_exp
             | multiplicative_exp TSTAR unary_exp
             | multiplicative_exp TSLASH unary_exp
             | multiplicative_exp TMOD unary_exp
             ;
unary_exp       : postfix_exp
            | TMINUS unary_exp
            | TNOT unary_exp
            | TINC unary_exp
            | TDEC unary_exp
            ;
postfix_exp       : primary_exp
               | postfix_exp TLLBRACKET expression TRLBRACKET
               | postfix_exp TLSBRACKET opt_actual_param TRSBRACKET
               | postfix_exp TINC
               | postfix_exp TDEC
               ;
opt_actual_param    : actual_param
           |
           ;
actual_param       : actual_param_list         ;
actual_param_list    : assignment_exp
            | actual_param_list TCOMMA assignment_exp
            ;
primary_exp       : TIDENT
              | TNUMBER
              | TLSBRACKET expression TRSBRACKET
              ;
%%

void semantic(int n)
{
   //printf("reduced rule number = %d\n",n);
}