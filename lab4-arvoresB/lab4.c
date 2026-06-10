#include <stdio.h>
#include "lab4.h"

//Alunos: Gabriel Adib - 2510466, Gabriel Félix - 2510619

#define MAX 4
#define MIN 2

typedef struct _btree BTree;
typedef struct _btreePage BTPage;
typedef struct no t_no;

void intervalo(t_no *arv, int lim_inf, int lim_sup)
{
    int i;

    if (arv == NULL)
        return;

    for (i = 0; i < arv->ndesc; i++)
    {
        intervalo(arv->ramo[i], lim_inf, lim_sup);

        if (arv->chave[i] > lim_inf &&
            arv->chave[i] < lim_sup)
        {
            printf("%d ", arv->chave[i]);
        }
    }

    intervalo(arv->ramo[arv->ndesc],
              lim_inf,
              lim_sup);
}
