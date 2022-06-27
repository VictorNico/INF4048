%{
#include<stdio.h>
#include "simple.h"

%}

entier [0-9]+
operateur \+|\*|\=|\;|\=\=|\!\=|\<|\>
parenthese \(|\)
variable a|b|c|d

%%
{entier} { yylval=atoi(yytext);return INTEGER;}
{operateur} {return *yytext;}
{variable}  {yylval=*yytext; return VARIABLE;}
print {return PRINT;}
[\n] ;
[ ] ;
[\t] ;
. { printf("parse error (lex) + %s -\n",yytext); }

%%

