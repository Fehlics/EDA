/* Alunos: Gabriel Adib - 2510466, Gabriel Félix - 2510619 */

#include <stdio.h>
#include "lab4.h"

typedef struct _btree BTree;
typedef struct _btreePage BTPage;
typedef struct no t_no;

/* Questão 1: Criação manual da Árvore B de ordem 2 do enunciado */

/*
 * cria_no — Aloca e inicializa um novo nó da Árvore B.
 *
 * Parâmetros:
 *   ndesc — número de chaves que o nó conterá (deve ser <= MAX).
 *
 * Retorno:
 *   Ponteiro para o novo nó alocado. Todos os ponteiros ramo[] são
 *   inicializados como NULL (nó folha por padrão).
 */
static t_no *cria_no(int ndesc)
{
    /* Aloca memória para o novo nó. */
    t_no *n = malloc(sizeof(t_no));

    /* Define a quantidade de chaves do nó. */
    n->ndesc = ndesc;

    /* Inicializa todos os ponteiros de ramo como NULL (folha). */
    for(int i = 0; i < MAX+1; i++)
        n->ramo[i] = NULL;

    return n;
}

int main()
{
    /* Folhas */
    t_no *n1 = cria_no(2);
    n1->chave[0] = 10;
    n1->chave[1] = 40;

    t_no *n2 = cria_no(2);
    n2->chave[0] = 60;
    n2->chave[1] = 70;

    t_no *n3 = cria_no(2);
    n3->chave[0] = 80;
    n3->chave[1] = 90;

    t_no *n4 = cria_no(2);
    n4->chave[0] = 110;
    n4->chave[1] = 115;

    t_no *n5 = cria_no(4);
    n5->chave[0] = 130;
    n5->chave[1] = 135;
    n5->chave[2] = 140;
    n5->chave[3] = 170;

    t_no *n6 = cria_no(4);
    n6->chave[0] = 220;
    n6->chave[1] = 230;
    n6->chave[2] = 240;
    n6->chave[3] = 250;

    /* Nó interno esquerdo [50 75] */
    t_no *esq = cria_no(2);
    esq->chave[0] = 50;
    esq->chave[1] = 75;

    esq->ramo[0] = n1;
    esq->ramo[1] = n2;
    esq->ramo[2] = n3;

    /* Nó interno direito [120 200] */
    t_no *dir = cria_no(2);
    dir->chave[0] = 120;
    dir->chave[1] = 200;

    dir->ramo[0] = n4;
    dir->ramo[1] = n5;
    dir->ramo[2] = n6;

    /* Raiz [100] */
    t_no *raiz = cria_no(1);
    raiz->chave[0] = 100;

    raiz->ramo[0] = esq;
    raiz->ramo[1] = dir;

    /* Questão 3: Testes */
    
    /* a) Intervalo [5, 300]: deve imprimir todas as chaves da árvore. */
    printf("a) [5,300]\n");
    intervalo(raiz, 5, 300);
    printf("\n\n");

    /* b) Intervalo [50, 100]: limites coincidem com chaves existentes
     *    (50 e 100 são excluídos), deve imprimir: 60 70 75 80 90. */
    printf("b) [50,100]\n");
    intervalo(raiz, 50, 100);
    printf("\n\n");

    /* c) Intervalo [70, 135]: deve imprimir: 75 80 90 100 110 115 120 130. */
    printf("c) [70,135]\n");
    intervalo(raiz, 70, 135);
    printf("\n");

    return 0;
}
