%{
#include<stdio.h>
#include "simple.h"
unsigned int lineno=1;
int error_lexical=1;

%}
%option noyywrap

number [0-9]+
operator \+|\*|\=|\;|\=\=|\!\=|\<|\>
startUrge "nzhìè"
keyUrge "mànkō"
pronouns "ā"|"ō"|"ī"|"yāā"|"yēē"|"yōh"
startSentiment "Fōh"|"Túfhǔ"
acceptWords "wúzá"|"kǔ'"|"nshǐ"|"ndǔ'"|"péé"|"nàh nsíí"|"nàh nní"|"nàh njīī nó"|"nàh njēē ló"|"lǒ"|"nǒ"|"nkə̀mnkə̌b"

%%
{acceptWords} { yylval.texte=yytext;return WORD;}
{startUrge} { yylval.texte=yytext;return START_URGE;}
{keyUrge} { yylval.texte=yytext;return KEY_URGE;}
{pronouns} { yylval.texte=yytext;return PRONOUN;}
{startSentiment} { yylval.texte=yytext;return START_SENTIMENT;}
"\n" {lineno++;}
" "|"\t"|"." ;
{operator} {
    fprintf(stderr,"\tERREUR : Lexeme inconnu a la ligne %d. Il s'agit de %s et comporte %d lettre(s)\n",lineno,yytext,yyleng);
    error_lexical=0;
    return yytext[0];
}
{number} {
    fprintf(stderr,"\tERREUR : Lexeme inconnu a la ligne %d. Il s'agit de %s et comporte %d lettre(s)\n",lineno,yytext,yyleng);
    error_lexical=0;
    return yytext[0];
}

%%

/*flex -o tp7.yy.c tp7.lex
gcc -pedantic -Wall -O2 tp7.yy.c -o tp7 -lfl
utilisation : echo "12+6*8" | ./tp7 */

