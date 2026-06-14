/*
Alunos:
    Gabriel Adib - 2510466,
    Gabriel Félix - 2510619
*/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/*
    Reserva memória para o grafo
    e inicializa todas as listas como vazias.
*/
Grafo* criaGrafo(int nv)
{
    Grafo *g = malloc(sizeof(Grafo));
    g->nv = nv;
    g->na = 0;

    // cria vetor de listas de adjacência
    g->viz = malloc(nv * sizeof(Viz*));

    // inicialmente nenhum vértice possui vizinhos
    for(int i=0;i<nv;i++)
        g->viz[i] = NULL;

    return g;
}

/*
    Insere uma nova conexão no grafo.
    Como o grafo é não direcionado,
    a aresta é adicionada nos dois sentidos.

    Exemplo:
    adicionaAresta(0,1)

    gera:
    0 -> 1
    e
    1 -> 0
*/
void adicionaAresta(Grafo *g, int origem, int destino, float peso)
{
    Viz *novo = malloc(sizeof(Viz));
    novo->noj = destino;
    novo->peso = peso;
    novo->prox = g->viz[origem];
    g->viz[origem] = novo;

    /*
    adiciona o caminho inverso
    grafo não direcionado
    */
    novo = malloc(sizeof(Viz));
    novo->noj = origem;
    novo->peso = peso;
    novo->prox = g->viz[destino];
    g->viz[destino] = novo;
    g->na++;
}

/*
    Função auxiliar da DFS.

    Recebe o vetor visitado para evitar
    visitar o mesmo vértice várias vezes.
*/
void DFS_rec(Grafo *g, int v, int visitado[])
{
    visitado[v] = 1;
    printf("%d\n",v);
    Viz *aux = g->viz[v];

    while(aux != NULL)
    {
        if(!visitado[aux->noj])
            DFS_rec(g, aux->noj, visitado);

        aux = aux->prox;
    }
}

void DFS(Grafo *g, int inicio)
{
    int visitado[g->nv];

    for(int i=0;i<g->nv;i++)
        visitado[i]=0;

    DFS_rec(g,inicio,visitado);
}

/*
    Busca em largura.

    Utiliza uma fila para explorar
    primeiro os vértices mais próximos
    do início.
*/
void BFS(Grafo *g, int inicio, int destino)
{
    int visitado[g->nv];
    int fila[g->nv];

    for(int i=0;i<g->nv;i++)
        visitado[i]=0;

    int ini=0;
    int fim=0;

    fila[fim++] = inicio;
    visitado[inicio]=1;

    while(ini < fim)
    {
        int atual = fila[ini++];
        printf("%d\n", atual);

        if(atual == destino)
            return;

        Viz *aux = g->viz[atual];
        while(aux)
        {
            if(!visitado[aux->noj])
            {
                visitado[aux->noj]=1;
                fila[fim++]=aux->noj;
            }

            aux = aux->prox;
        }
    }
}

/* Remove uma aresta da lista de adjacência. */
void removeAresta(Grafo *g,int origem,int destino)
{
    Viz *ant = NULL;
    Viz *aux = g->viz[origem];

    while(aux)
    {
        if(aux->noj == destino)
        {
            if(ant == NULL)
                g->viz[origem] = aux->prox;
            else
                ant->prox = aux->prox;

            free(aux);
            return;
        }
        ant = aux;
        aux = aux->prox;
    }
}