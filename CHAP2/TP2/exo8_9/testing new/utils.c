#include "utils.h"
#include <string.h>

void afficher_element(Element *e)
{
    if (e != NULL)
    {
        printf("val=%s type=%d", e->val, e->type);
        if (e->suivant == NULL)
        {
            printf("next=NULL");
        }
        if (e->prec == NULL)
        {
            printf("prec=NULL");
        }
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }
}
void initialiser_expression(Expression *exp)
{
    exp->tete = NULL;
    exp->queue = NULL;
}

void supprimer(Expression *exp)
{
    exp->tete = NULL;
    exp->queue = NULL;
}

int est_vide_expression(Expression *exp)
{
    if (exp->tete == NULL && exp->queue == NULL)
        return 1;
    return 0;
}

void insert_fin(Expression *exp, char val[], int type)
{
    Element *e = malloc(sizeof(Element));
    e->val = malloc((strlen(val) + 1) * sizeof(char));
    strcpy(e->val, val);
    e->type = type;
    e->suivant = NULL;

    if (est_vide_expression(exp) == 1)
    {
        e->prec = NULL;
        exp->queue = e;
        exp->tete = e;
    }
    else
    {
        e->prec = exp->queue;
        exp->queue->suivant = e;
        exp->queue = e;
    }
}

void afficher_expression(Expression *exp)
{
    if (est_vide_expression(exp) == 1)
    {
        printf("Expression Vide\n");
    }
    else
    {
        Element *a = exp->tete;
        while (a != NULL)
        {
            if (a->type == 0)
                printf("%ld|", atol(a->val));
            else
                printf("%s|", a->val);
            a = a->suivant;
        }
        printf("\n");
    }
}

void supprimer_fin(Expression *exp)
{
    if (exp->queue == exp->tete)
    {
        exp->queue = NULL;
        exp->tete = NULL;
    }
    else
        exp->queue = exp->queue->prec;
}

void supprimer_element(Expression *exp, Element *e)
{
    Element *a = exp->tete;
    while (a != NULL)
    {
        if (a == e)
        {
            if (a == exp->tete)
            {
                if (exp->tete != NULL)
                {
                    exp->tete = exp->tete->suivant;
                }
                break;
            }
            else
            {
                a->prec->suivant = a->suivant;
                a->suivant->prec = a;

                break;
            }
        }
        a = a->suivant;
    }
}

int size(Expression *e){
    Element* a = e->tete;
    int s = 0;
    while(a != NULL){
        s++;
        a = a->suivant;
    }
    return s;
}