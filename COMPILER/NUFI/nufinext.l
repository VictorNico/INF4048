%{
#include<stdio.h>
#include "simple.h"

%}
%option noyywrap

u2 "u2"
a1 "a1"
a2 "a2"
a3 "a3"
o3 "o3"
o2 "o2"
o7 "o7"
eu1 "eu1"
eu7 "eu7"
e3 "e3"
e2 "e2"
i2 "i2"
i3 "i3"
i7 "i7"
u7 "u7"
autre [.]+

%%
{u2} { fprintf(yyout,"ú");}
{a1} { fprintf(yyout,"à");}
{a2} { fprintf(yyout,"á");}
{a3} { fprintf(yyout,"ā");}
{o3} { fprintf(yyout,"ō");}
{o2} { fprintf(yyout,"ú");}
{o7} { fprintf(yyout,"ǒ");}
{eu1} { fprintf(yyout,"ə̀");}
{eu7} { fprintf(yyout,"ə̌");}
{e3} { fprintf(yyout,"ē");}
{e2} { fprintf(yyout,"é");}
{i2} { fprintf(yyout,"í");}
{i3} { fprintf(yyout,"ī");}
{i7} { fprintf(yyout,"ǐ");}
{u7} { fprintf(yyout,"ǔ");}
{autre} {fprintf(yyout,"%s",yytext);}


%%

int main(int argc, char* argv[])
{
	extern FILE *yyin,*yyout;
	yyin = fopen(argv[1],"r");
	yyout = fopen("translate.nufi","w");
	yylex();
	return 0;

}

