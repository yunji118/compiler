%{
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
%}
letter  [a-zA-Z_]
digit   [0-9]
%%
"const"   return(TCONST);
"else"    return(TELSE);
"if"      return(TIF);
"int"     return(TINT);
"return"  return(TRETURN);
"void"    return(TVOID);
"while"   return(TWHILE);
"=="    return(TEQUAL);
"!="    return(TNOTEQU);
"<="    return(TLESSE);
">="    return(TGREATE);
"&&"    return(TAND);
"||"    return(TOR);
"++"    return(TINC);
"--"    return(TDEC);
"+="    return(TADDASSIGN);
"-="    return(TSUBASSIGN);
"*="    return(TMULASSIGN);
"/="    return(TDIVASSIGN);
"%="    return(TMODASSIGN);
“;”	    return(TSEMICOLON);
{letter}({letter}|{digit})*   return(TIDENT);
{digit}+    return(TNUMBER);
"//".*                          ;
[ \t\n]                         ;
.*       return(yytext[0]);
%%
int yywrap()
{
    printf("KIM WONWOO,KIM JEEYOUN, KIM DOYEON, HA YUNJI\n");
    return 1;
}

