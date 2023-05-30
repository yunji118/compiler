%{
/*scanner.l - lexical analyzer for MiniC
* programmer - 김지윤, 김도연, 김원우, 하윤지
* date - 2023/04/26
/*lex source for Mini C*/
#include "tn.h"
#include "glob.h"

extern void PrintError(enum errorTypes error, char* string);
extern void SymTable(char* string);
%}
letter  [a-zA-Z_]
digit   [0-9]
%%
"const"      return(TCONST);
"else"      return(TELSE);
"if"      return(TIF);
"int"      return(TINT);
"float"      return(TFLOAT);
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
"\n"     {
            cLine++;
         }
{letter}({letter}|{digit})* {
                                if (yyleng <= 10) {
                                    SymTable(yytext);
                                    return(TIDENT);
                                } else {
                                    PrintError(illlen, yytext);
                                    return(TERROR);
                                }
                            }
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?   return(TNUMBER);
{digit}+{letter}[A-Za-z0-9_]*   PrintError(illid, yytext);
"//".*   ;
[ \t]  ;
.   PrintError(illchar, yytext);
%%

int yywrap() {
   return 1;
}
