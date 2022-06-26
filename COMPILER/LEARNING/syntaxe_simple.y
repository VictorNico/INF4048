%{

#include "simple.h"
#include <string.h>
bool error_syntaxical=false;
extern unsigned int lineno;
extern bool error_lexical;

%}

/* L'union dans Bison est utilisee pour typer nos tokens ainsi que nos non terminaux. Ici nous avons declare une union avec deux types : nombre de type int et texte de type pointeur de char (char*) */

%union {
    long nombre;
    char* texte;
}

/* Nous avons ici les operateurs, ils sont definis par leur ordre de priorite. Si je definis par exemple la multiplication en premier et l'addition apres, le + l'emportera alors sur le * dans le langage. Les parenthese sont prioritaires avec %right */

%left                   TOK_PLUS        TOK_MOINS       /* +- */
%left                   TOK_MUL         TOK_DIV         /* /* */
%left                   TOK_ET         
%left                   TOK_OU          TOK_NON         /* et ou non */
%right                  TOK_PARG        TOK_PARD        /* () */

/* Nous avons la liste de nos expressions (les non terminaux). Nous les typons tous en texte (pointeur vers une zone de char). On a legitimement cree un non terminal variable afin d'isoler le token TOK_VAR et avoir une expression qui contiendra uniquement le nom de la variable */

%type<texte>            code
%type<texte>            instruction
%type<texte>            variable
%type<texte>            affectation
%type<texte>            affichage
%type<texte>            expression_arithmetique
%type<texte>            expression_booleenne
%type<texte>            addition
%type<texte>            soustraction
%type<texte>            multiplication
%type<texte>            division

/* Nous avons la liste de nos tokens (les terminaux de notre grammaire) */

%token<texte>           TOK_NOMBRE
%token                  TOK_VRAI        /* true */
%token                  TOK_FAUX        /* false */
%token                  TOK_AFFECT      /* = */
%token                  TOK_FINSTR      /* ; */
%token                  TOK_AFFICHER    /* afficher */
%token<texte>           TOK_VAR         /* variable */

%%

/* Nous definissons toutes les regles grammaticales de chaque non terminal de notre langage. Par defaut on commence a definir l'axiome, c'est a dire ici le non terminal code. Si nous le definissons pas en premier nous devons le specifier en option dans Bison avec %start */

code:           %empty{}
            |
            code instruction{
                    printf("Resultat : C'est une instruction valide !\n\n");
            }
            |
            code error{
                    fprintf(stderr,"\tERREUR : Erreur de syntaxe a la ligne %d.\n",lineno);
                    error_syntaxical=true;
            };

instruction:    affectation{
                    printf("\tInstruction type Affectation\n");
            }
            |
            affichage{
                     printf("\tInstruction type Affichage\n");
            };

/* L'expression variable contient uniquement le nom de la variable */
variable:       TOK_VAR{
                    /* $1 est la chaine de texte de l'expression retournee par l'analyseur lexical Flex. */
                    printf("\t\t\tVariable %s\n",$1);
                    /* On affecte comme valeur a l'expression (variable Bison $$) une copie de $1. Copie car $1 sera automatiquement efface apres sortie de la "routine". Toutes ces variables Bison nous permettent en realite de construire un arbre syntaxique. */
                    $$=strdup($1);
            };

affectation:    variable TOK_AFFECT expression TOK_FINSTR{
                    /* $1 est la valeur du premier non terminal. Ici c'est la valeur du non terminal variable. $3 est la valeur du 2nd non terminal. */
                    printf("\t\tAffectation sur la variable %s\n",$1);
            };

affichage:      TOK_AFFICHER expression TOK_FINSTR{
                    printf("\t\tAffichage de la valeur de l'expression %s\n",$2);
            };

expression_arithmetique:        TOK_NOMBRE{
                                    printf("\t\t\tNombre : %ld\n",$1);
                                    /* Comme le token TOK_NOMBRE est de type entier et que on a type expression_arithmetique comme du texte, il nous faut convertir la valeur en texte. */
                                    int length=snprintf(NULL,0,"%ld",$1);
                                    char* str=malloc(length+1);
                                    snprintf(str,length+1,"%ld",$1);
                                    $$=strdup(str);
                                    free(str);
                            }
                            |
                            variable{
                            }
                            |
                            addition{
                            }
                            |
                            soustraction{
                            }
                            |
                            multiplication{
                            }
                            |
                            division{
                            }
                            |
                            TOK_PARG expression_arithmetique TOK_PARD{
                                    printf("\t\t\tC'est une expression artihmetique entre parentheses\n");
                                    $$=strcat(strcat(strdup("("),strdup($2)),strdup(")"));
                            };

expression_booleenne:           TOK_VRAI{
                                    printf("\t\t\tBooleen Vrai\n");
                                    $$=strdup("vrai");
                            }
                            |
                            TOK_FAUX{
                                    printf("\t\t\tBooleen Faux\n");
                                    $$=strdup("faux");
                            }
                            |
                            variable{
                                    $$=strdup($1);
                            }
                            |
                            TOK_NON expression_booleenne{
                                    printf("\t\t\tOperation booleenne Non\n");
                                    $$=strcat(strdup("non "), strndup($2,sizeof(char)*strlen($2)));
                            }
                            |
                            expression_booleenne TOK_ET expression_booleenne{
                                    printf("\t\t\tOperation booleenne Et\n");
                                    $$=strcat(strcat(strdup($1),strdup(" et ")),strdup($3));
                            }
                            |
                            expression_booleenne TOK_OU expression_booleenne{
                                    printf("\t\t\tOperation booleenne Ou\n");
                                    $$=strcat(strcat(strdup($1),strdup(" ou ")),strdup($3));
                            }
                            |
                            TOK_PARG expression_booleenne TOK_PARD{
                                    printf("\t\t\tC'est une expression booleenne entre parentheses\n");
                                    $$=strcat(strcat(strdup("("),strdup($2)),strdup(")"));
                            };

addition:       expression_arithmetique TOK_PLUS expression_arithmetique{printf("\t\t\tAddition\n");$$=strcat(strcat(strdup($1),strdup("+")),strdup($3));};
soustraction:   expression_arithmetique TOK_MOINS expression_arithmetique{printf("\t\t\tSoustraction\n");$$=strcat(strcat(strdup($1),strdup("-")),strdup($3));};
multiplication: expression_arithmetique TOK_MUL expression_arithmetique{printf("\t\t\tMultiplication\n");$$=strcat(strcat(strdup($1),strdup("*")),strdup($3));};
division:       expression_arithmetique TOK_DIV expression_arithmetique{printf("\t\t\tDivision\n");$$=strcat(strcat(strdup($1),strdup("/")),strdup($3));};

%%

/* Dans la fonction main on appelle bien la routine yyparse() qui sera genere par Bison. Cette routine appellera yylex() de notre analyseur lexical. */

int main(void){
    printf("Debut de l'analyse syntaxique :\n");
    yyparse();
    printf("Fin de l'analyse !\n");
    printf("Resultat :\n");
    if(error_lexical){
            printf("\t-- Echec : Certains lexemes ne font pas partie du lexique du langage ! --\n");
            printf("\t-- Echec a l'analyse lexicale --\n");
    }
    else{
            printf("\t-- Succes a l'analyse lexicale ! --\n");
    }
    if(error_syntaxical){
            printf("\t-- Echec : Certaines phrases sont syntaxiquement incorrectes ! --\n");
            printf("\t-- Echec a l'analyse syntaxique --\n");
    }
    else{
            printf("\t-- Succes a l'analyse syntaxique ! --\n");
    }
    return EXIT_SUCCESS;
}
void yyerror(char *s) {
    fprintf(stderr, "Erreur de syntaxe a la ligne %d: %s\n", lineno, s);
}

