/*
Alunos:
    Gabriel Adib - 2510466,
    Gabriel Félix - 2510619
*/

#ifndef GRAFO_H
#define GRAFO_H

/* lista de adjacência */
typedef struct _viz Viz;
struct _viz {
 int noj;       // número do vértice vizinho
 float peso;    // peso da aresta
Viz* prox;      // próximo vizinho
};

typedef struct {
    int nv;     // número de vértices
    int na;     // número de arestas
    Viz **viz;  // vetor de listas de adjacência
}Grafo;

/* Cria um grafo vazio com nv vértices. */
Grafo* criaGrafo(int nv);

/*
    Adiciona uma aresta entre dois vértices.
    Como o mapa representa conexões físicas,
    o grafo é não direcionado:
    origem ---- destino

    também cria:
    destino ---- origem
*/
void adicionaAresta(Grafo *g, int origem, int destino, float peso);

/* Remove uma conexão entre dois ambientes. */
void removeAresta(Grafo *g, int origem, int destino);

/*
    Executa uma Busca em Profundidade (DFS).
    Percorre todos os vértices alcançáveis
    a partir do vértice inicial.
*/
void DFS(Grafo *g, int inicio);

/*
    Executa uma Busca em Largura (BFS).
    Utilizada para encontrar caminhos mínimos
    em grafos sem peso.
*/
void BFS(Grafo *g, int inicio, int destino);

#endif