#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define nbre_chiffre_max 1000

Expression *liste;
Expression *liste_post_fixe;
Expression *operateurs;

int get_priorite(char operateur)
{
    if (operateur == '+' || operateur == '-')
        return 0;
    if (operateur == '*' || operateur == '/')
        return 1;
    else
        return -1;
}

long evaluation(Expression *e)
{
    Element *a = e->tete;
    while (a != NULL)
    {
        if (a->type == 1)
        {
            Element *prec = a->prec;
            int s = size(e);
            if(s > 3)
                supprimer_element(e, a);
            Element *b = a->prec;
            if (b->type != 0)
            {
                printf("Erreur de synthaxe\n");
                exit(EXIT_FAILURE);
            }

            long val1 = atol(prec->val);
            Element *c = b->prec;
            prec = prec->prec;
            if(s > 3)
                supprimer_element(e, b);
            if (c->type != 0)
            {
                printf("Erreur de synthaxe\n");
                exit(EXIT_FAILURE);
            }
            long val2 = atol(prec->val);
            prec = c->prec;
            supprimer_element(e, c);
            switch (a->val[0])
            {
            case '+':
                val1 += val2;
                break;
            case '-':
                val1 = val2-val1;
                break;
            case '/':
                val1 = val2/val1;
                break;
            case '*':
                val1 *= val2;
                break;
            }
            Element *n = malloc(sizeof(Element));
            char tab[100];
            sprintf(tab, "%ld", val1);
            n->val = malloc((strlen(tab) + 1)*sizeof(char));
            strcpy(n->val,tab);
            if(s <= 3)
                return val1;
            if (prec == NULL)
            {
                e->tete->prec = n;
                n->suivant = e->tete;
                n->prec = NULL;
                e->tete = n;
            }
            else{
                prec->suivant = n;
                n->suivant = a->suivant;
                n->prec = prec;
                a->suivant->prec = n;
            }
            a = e->tete;
            continue;
        }
        a = a->suivant;
    }
    afficher_expression(e);
    return -1;
}

void transform_post_fixe_avec_priorite(Expression *e)
{
    initialiser_expression(liste_post_fixe);
    initialiser_expression(operateurs);
    Element *a = e->tete;

    while (a != NULL)
    {
        if (a->type == 0)
        {
            insert_fin(liste_post_fixe, a->val, a->type);
        }
        else
        {
            if (est_vide_expression(operateurs) == 0)
            {
                Element *b = operateurs->queue;
                while (b != NULL && get_priorite(a->val[0]) < get_priorite(b->val[0]))
                {
                    insert_fin(liste_post_fixe, b->val, b->type);
                    b = b->prec;
                    supprimer_fin(operateurs);
                }
            }
            insert_fin(operateurs, a->val, a->type);
        }
        a = a->suivant;
    }
    if (est_vide_expression(operateurs) == 0)
    {
        Element *b = operateurs->queue;
        while (b != NULL)
        {
            insert_fin(liste_post_fixe, b->val, b->type);
            b = b->prec;
        }
        supprimer(operateurs);
    }
}

void transform_post_fixe_sans_priorite(Expression *e)
{
    initialiser_expression(liste_post_fixe);
    initialiser_expression(operateurs);
    Element *a = e->tete;

    while (a != NULL)
    {
        if (a->type == 0)
        {
            insert_fin(liste_post_fixe, a->val, a->type);
        }
        else
        {
            if (est_vide_expression(operateurs) == 0)
            {
                Element *b = operateurs->queue;
                while (b != NULL)
                {
                    insert_fin(liste_post_fixe, b->val, b->type);
                    b = b->prec;
                }
                supprimer(operateurs);
            }
            insert_fin(operateurs, a->val, a->type);
        }
        a = a->suivant;
    }
    if (est_vide_expression(operateurs) == 0)
    {
        Element *b = operateurs->queue;
        while (b != NULL)
        {
            insert_fin(liste_post_fixe, b->val, b->type);
            b = b->prec;
        }
        supprimer(operateurs);
    }
}

int indexof(const char mot[], char symbole)
{
    for (int i = 0; i <= strlen(mot); i++)
    {
        if (mot[i] == symbole)
            return i;
    }
    return -1;
}

char alphabet[] = "0123456789+*-/";
int transitions[2][14] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}};

void afficheLexemes(int q, char c, char nombre[])
{
    char op = '\0';
    if (q == 1)
    {
        op = nombre[strlen(nombre) - 1];
        nombre[strlen(nombre) - 1] = '\0';
    }
    if (strlen(nombre) > 0)
    {
        printf("<int:%ld>", atol(nombre));
        insert_fin(liste, nombre, 0);
    }

    nombre[0] = c;
    nombre[1] = '\0';
    if (q == 1)
    {
        char t[2];
        t[0] = op;
        t[1] = '\0';
        printf("<operateur:%c>", op);
        insert_fin(liste, t, 1);
    }
}

char nombre[nbre_chiffre_max];

void afficher_lexemes_fichier(const char file_name[])
{

    FILE *file = fopen(file_name, "r");
    char c;
    int q = 0, index_nombre = 0;
    nombre[0] = '\0';

    if (file == NULL)
    {
        fwrite("Erreur lors de l'ouverture du fichier\n", 39, 1, stderr);
        exit(EXIT_FAILURE);
    }
    while ((c = fgetc(file)) != EOF)
    {
        if (c == ' ')
            continue;
        if (c == '\n')
        {
            afficheLexemes(q, c, nombre);
            q = 0;
            nombre[0] = '\0';
            index_nombre = 0;
            printf("\n");
            transform_post_fixe_sans_priorite(liste);
            printf("\tValeur sans priorite:%ld\n", evaluation(liste_post_fixe));
            supprimer(liste_post_fixe);
            transform_post_fixe_avec_priorite(liste);
            printf("\tValeur avec priorite:%ld\n",evaluation(liste_post_fixe));
            supprimer(liste);
            supprimer(liste_post_fixe);
            continue;
        }
        if (indexof(alphabet, c) != -1)
        {
            if (q == 1)
            {
                afficheLexemes(q, c, nombre);
                index_nombre = 0;
            }
            nombre[index_nombre] = c;
            index_nombre++;
            nombre[index_nombre] = '\0';

            q = transitions[q][indexof(alphabet, c)];
        }
        else
        {
            printf("Parse error: unknow %c\n", c);
            exit(EXIT_FAILURE);
        }
    }
    afficheLexemes(q, c, nombre);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        liste = malloc(sizeof(Expression));
        liste_post_fixe = malloc(sizeof(Expression));
        operateurs = malloc(sizeof(Expression));
        initialiser_expression(liste);
        afficher_lexemes_fichier(argv[1]);
    }
    else
        printf("\nVeuillez spécifier dans la ligne de commande uniquement le fichier des expressions\n");

    return 0;
}
