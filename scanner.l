%{
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
%}
letter  [a-zA-Z_]
digit   [0-9]
%%
"const"		return(TCONST);
"else"		return(TELSE);
"if"		return(TIF);
"int"		return(TINT);
"return"	return(TRETURN);
"void"		return(TVOID);
"while"		return(TWHILE);
"+"		return(TPLUS);
"-"		return(TMINUS);
"*"		return(TSTAR);
"/"		return(TSLASH);
"%"		return(TMOD);
"="		return(TASSIGN);
"+="		return(TADDASSIGN);
"-="		return(TSUBASSIGN);
"*="		return(TMULASSIGN);
"/="		return(TDIVASSIGN);
"%="		return(TMODASSIGN);
"!"		return(TNOT);
"&&"		return(TAND);
"||"		return(TOR);
"=="		return(TEQUAL);
"!="		return(TNOTEQU);
"<"		return(TLESS);
">"		return(TGREAT);
"<="		return(TLESSE);
">="		return(TGREATE);
"++"		return(TINC);
"--"		return(TDEC);
"("		return(TLSBRACKET);
")"		return(TRSBRACKET);
","		return(TCOMMA);
"{"		return(TLMBRACKET);
"}"		return(TRMBRACKET);
"["		return(TLLBRACKET);
"]"		return(TRLBRACKET);
";"		return(TSEMICOLON);
"//".*		return(TCOMMENT);
{letter}({letter}|{digit})*	return(TIDENT);
{digit}+		return(TNUMBER);
[ \t]		return(TSEPARATOR);
[\n]		return(TLINE);
{digit}+{letter}({letter}|{digit})*	return(TILLID);
.       return(TERROR);
%%
int yywrap()
{
    printf("KIM WONWOO, KIM JEEYOUN, KIM DOYEON, HA YUNJI\n");
    return 1;
}
