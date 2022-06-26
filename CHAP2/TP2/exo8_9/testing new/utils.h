#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Element
{
    char *val;
    struct Element *suivant;
    struct Element *prec;
    int type;
};
typedef struct Element Element;

struct Expression
{
    Element *tete;
    Element *queue;
};
typedef struct Expression Expression;

void afficher_element(Element *e);
void initialiser_expression(Expression *exp);
void supprimer(Expression *exp);
void supprimer_fin(Expression *exp);
int est_vide_expression(Expression *exp);
void insert_fin(Expression *exp, char val[], int type);
void afficher_expression(Expression *exp);
void supprimer_element(Expression *exp, Element *e);
int size(Expression *e);
#endif