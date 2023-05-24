%{
/*scanner.l - lexical analyzer for MiniC
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/04/26
/*lex source for Mini C*/
#include "tn.h"
extern void PrintError(enum errorTypes error, char* string);
extern void SymTable(char* string);
//extern void printtoken(enum yytokentype tn);
%}
letter  [a-zA-Z_]
digit   [0-9]
%%
"const"      return(TCONST);
"else"      return(TELSE);
"if"      return(TIF);
"int"      return(TINT);
"return"   return(TRETURN);
"void"      return(TVOID);
"while"      return(TWHILE);
"+"      return(TPLUS);
"-"      return(TMINUS);
"*"      return(TSTAR);
"/"      return(TSLASH);
"%"      return(TMOD);
"="      return(TASSIGN);
"+="      return(TADDASSIGN);
"-="      return(TSUBASSIGN);
"*="      return(TMULASSIGN);
"/="      return(TDIVASSIGN);
"%="      return(TMODASSIGN);
"!"      return(TNOT);
"&&"      return(TAND);
"||"      return(TOR);
"=="      return(TEQUAL);
"!="      return(TNOTEQU);
"<"      return(TLESS);
">"      return(TGREAT);
"<="      return(TLESSE);
">="      return(TGREATE);
"++"      return(TINC);
"--"      return(TDEC);
"("      return(TLSBRACKET);
")"      return(TRSBRACKET);
","      return(TCOMMA);
"{"      return(TLMBRACKET);
"}"      return(TRMBRACKET);
"["      return(TLLBRACKET);
"]"      return(TRLBRACKET);
";"      return(TSEMICOLON);
"//".*      ;

[A-Za-z_][A-Za-z0-9_]*      if(yyleng>10){PrintError(illlen, yytext); return(TERROR);} else{SymTable(yytext); return(TIDENT);}
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?   return(TNUMBER);
[0-9]+[A-Za-z_][A-Za-z0-9_]*   PrintError(illid, yytext);
[ \t\n]  ;
.   return(yytext[0]);
%%

int yywrap() {
   return 1;
}