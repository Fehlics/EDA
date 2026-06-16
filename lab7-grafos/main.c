/*
Alunos:
    Gabriel Adib - 2510466,
    Gabriel Félix - 2510619

Compilação:
    gcc main.c grafo.c -o lab7
    ./lab7
*/

#include <stdio.h>
#include "grafo.h"

int main()
{
    /*--- QUESTÃO 1 ---*/
    /*
    Mapeamento dos vértices:
    0 - Recepção
    1 - Corredor A
    2 - Laboratório 1
    3 - Laboratório 2
    4 - Auditório
    5 - Corredor B
    6 - Escada
    7 - Saída
    */

    Grafo *g = criaGrafo(8);

    /* Criação das conexões do prédio */

    adicionaAresta(g,0,1,1);
    adicionaAresta(g,1,3,1);
    adicionaAresta(g,0,2,1);
    adicionaAresta(g,0,4,1);
    adicionaAresta(g,4,5,1);
    adicionaAresta(g,5,6,1);
    adicionaAresta(g,4,7,1);
    /*--- FIM QUESTÃO 1 ---*/

    /*--- QUESTÃO 2 ---*/
    printf("DFS Recepcao:\n");
    DFS(g,0);

    /*--- QUESTÃO 3 ---*/
    printf("\nBFS Lab1 -> Saida:\n");
    BFS(g,2,7);
    printf("\nBFS Lab2 -> Saida:\n");
    BFS(g,3,7);
    
    /*--- QUESTÃO 4 ---*/
    removeAresta(g,4,5);
    removeAresta(g,5,4);
    printf("\nDFS apos remocao:\n");
    DFS(g,0);

    return 0;
}