%{

#include "simple.h"
unsigned int lineno=1;
bool error_lexical=false;

%}

%option noyywrap

nombre 0|[1-9][[:digit:]]*
variable [[:alpha:]][[:alnum:]]*

%%

{nombre} {
    sscanf(yytext, "%ld", &yylval.nombre);
    return TOK_NOMBRE;
}

"afficher"      {return TOK_AFFICHER;}

"="             {return TOK_AFFECT;}

"+"             {return TOK_PLUS;}

"-"             {return TOK_MOINS;}

"*"             {return TOK_MUL;}

"/"             {return TOK_DIV;}

"("             {return TOK_PARG;}

")"             {return TOK_PARD;}

"et"            {return TOK_ET;}

"ou"            {return TOK_OU;}

"non"           {return TOK_NON;}

";"             {return TOK_FINSTR;}

"vrai"          {return TOK_VRAI;}

"faux"          {return TOK_FAUX;}

"\n"            {lineno++;}

{variable} {
    yylval.texte = yytext;
    return TOK_VAR;
}

" "|"\t" {}

. {
    fprintf(stderr,"\tERREUR : Lexeme inconnu a la ligne %d. Il s'agit de %s et comporte %d lettre(s)\n",lineno,yytext,yyleng);
    error_lexical=true;
    return yytext[0];
}

%%

