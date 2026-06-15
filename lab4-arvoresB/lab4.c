/* Alunos: Gabriel Adib - 2510466, Gabriel Félix - 2510619 */

/* Questão 2: Implementação da função intervalo(t_no *arv, int lim_inf, int lim_sup) */

#include <stdio.h>
#include "lab4.h"

#define MAX 4
#define MIN 2

typedef struct _btree BTree;
typedef struct no t_no;

/*
 * intervalo — Percorre a Árvore B em ordem simétrica (in-order) e imprime
 *             todas as chaves x tais que lim_inf < x < lim_sup.
 *
 * Parâmetros:
 *   arv     — ponteiro para o nó atual (raiz da subárvore em recursão).
 *   lim_inf — limite inferior exclusivo do intervalo de busca.
 *   lim_sup — limite superior exclusivo do intervalo de busca.
 */

void intervalo(t_no *arv, int lim_inf, int lim_sup)
{
    int i;

    /* Caso base: subárvore vazia (ponteiro nulo). Encerra a recursão. */
    if (arv == NULL)
        return;

    /*
     * Percurso in-order: para cada chave do nó,
     * visita primeiro a subárvore à esquerda (ramo[i]),
     * depois verifica e eventualmente imprime a chave[i].
     */
    for (i = 0; i < arv->ndesc; i++)
    {
        /*
         * Passo 1 — Desce recursivamente pela subárvore esquerda de chave[i].
         * Todas as chaves em ramo[i] são menores que chave[i],
         * portanto devem ser visitadas antes dela (ordem crescente).
         */
        intervalo(arv->ramo[i], lim_inf, lim_sup);

        /*
         * Passo 2 — Verifica se a chave atual está dentro do intervalo aberto
         * (lim_inf, lim_sup). Os limites são exclusivos conforme o enunciado
         * (lim_inf < x < lim_sup). Se sim, imprime a chave.
         */
        if (arv->chave[i] > lim_inf &&
            arv->chave[i] < lim_sup)
        {
            printf("%d ", arv->chave[i]);
        }
    }

    /*
     * Passo 3 — Após processar todas as ndesc chaves do nó,
     * desce recursivamente pela última subárvore (ramo[ndesc]).
     * Essa subárvore contém todas as chaves maiores que a
     * última chave do nó (chave[ndesc-1]).
     */
    intervalo(arv->ramo[arv->ndesc],
              lim_inf,
              lim_sup);
}
