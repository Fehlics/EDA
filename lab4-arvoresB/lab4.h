/* Alunos: Gabriel Adib - 2510466, Gabriel Félix - 2510619 */

#include <stdio.h>
#include <stdlib.h> 

#define MAX 4
#define MIN 2

typedef struct no t_no;
typedef struct _btree BTree;
struct _btree {
 t_no* root;    /* Ponteiro para o nó raiz da árvore. */
 int order;     /* Ordem p da árvore B. */
};

struct no {
int ndesc;          /* Quantidade de chaves válidas no nó. */
int chave[MAX];     /* Chaves do nó (não inclui overflow). */
t_no *ramo[MAX+1];  /* Ponteiros para os nós filhos (MAX+1 ramos). */
};

/*
 * intervalo — Percorre a Árvore B em ordem simétrica (in-order) e imprime
 *             todas as chaves x tais que lim_inf < x < lim_sup.
 *
 * Parâmetros:
 *   arv     — ponteiro para o nó atual (raiz da subárvore em recursão).
 *   lim_inf — limite inferior exclusivo do intervalo de busca.
 *   lim_sup — limite superior exclusivo do intervalo de busca.
 */
void intervalo(t_no *arv, int lim_inf, int lim_sup);
