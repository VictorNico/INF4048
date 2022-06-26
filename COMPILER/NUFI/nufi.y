%{
/*The execution of this program show  us well what express an urge, sentiment or sensation*/
#include<stdio.h>
#include "simple.h"
#include <unistd.h>
void yyerror(char *str);
int yylex(void);
int error_syntaxical=1;
extern unsigned int lineno;
extern int error_lexical;
%}

/* L'union dans Bison est utilisee pour typer nos tokens ainsi que nos non terminaux. Ici nous avons declare une union avec deux types : nombre de type int et texte de type pointeur de char (char*) */

%union {
    long nombre;
    char* texte;
}

/* Nous avons la liste de nos tokens (les terminaux de notre grammaire) */
%token<texte>	WORD
%token<texte>	START_URGE
%token<texte>	KEY_URGE
%token<texte>	PRONOUN
%token<texte>	START_SENTIMENT

%%
S:
	X	{printf("La phrase de la ligne %d:\tvalide\n", lineno); }

X:
	A B	{printf("La phrase de la ligne %d:\texpression d'envie\n", lineno); }
	|G	{printf("La phrase de la ligne %d:\texpression de sentiment\n", lineno); }
A:
	START_URGE
B:
	C D
D:
	E F
E:
	KEY_URGE
F:
	PRONOUN
G:
	H I;
H:
	START_SENTIMENT
I:
	E F
C:
	WORD
%%

int main(int argc, char* argv[])
{
  	extern FILE *yyin;
  	
  	if(argc < 1)
	{
		printf("\nplease pass input path\n");
		return 1;
	}
	// step 2: make sure that we are access to the file target
	if(access(argv[1],F_OK) != 0)
	{
		printf("input path doesn't exist");
		return 1;
	}
	if(access(argv[1],R_OK) != 0)
	{
		printf("the path passed has not read access");
		return 1;
	}
	
	yyin = fopen(argv[1],"r");
	
	printf("Debut de l'analyse syntaxique :\n");
	yyparse();
	printf("Fin de l'analyse !\n");
	printf("Resultat :\n");
	if(error_lexical == 0){
	    printf("\t-- Echec : Certains lexemes ne font pas partie du lexique du langage ! --\n");
	    printf("\t-- Echec a l'analyse lexicale --\n");
	}
	else{
	    printf("\t-- Succes a l'analyse lexicale ! --\n");
	}
	if(error_syntaxical == 0){
	    printf("\t-- Echec : Certaines phrases sont syntaxiquement incorrectes ! --\n");
	    printf("\t-- Echec a l'analyse syntaxique --\n");
	}
	else{
	    printf("\t-- Succes a l'analyse syntaxique ! --\n");
	}
	return 0;
 
}
void yyerror(char *str)
{
	printf("Erreur de syntaxe a la ligne %d: %s\n", lineno, str);
	
}
