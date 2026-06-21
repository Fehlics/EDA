/*
Alunos:
    Gabriel Adib - 2510466,
    Gabriel Félix - 2510619
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/* ==================================================
   ESTRUTURAS AUXILIARES - FILA DE PRIORIDADE
   ================================================== */
typedef struct{
    No **dados;
    int tamanho;
}FilaPrioridade;

/*
    Cria um nó da árvore de Huffman.
*/
No* criarNo(unsigned char caractere, int frequencia){
    No *novo = malloc(sizeof(No));
    novo->caractere = caractere;
    novo->frequencia = frequencia;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

/*
    Insere um nó na fila mantendo
    a menor frequência no início.
*/
void inserirFila(FilaPrioridade *fila, No *novo){
    int i;
    i = fila->tamanho;

    while(i > 0 && fila->dados[i-1]->frequencia > novo->frequencia){
        fila->dados[i] = fila->dados[i-1];
        i--;
    }
    fila->dados[i] = novo;
    fila->tamanho++;
}

/*
    Remove o nó de menor frequência.
*/
No* removerFila(FilaPrioridade *fila){
    No *menor;
    menor = fila->dados[0];

    for(int i=1;i<fila->tamanho;i++){
        fila->dados[i-1] = fila->dados[i];
    }
    fila->tamanho--;
    return menor;
}

/* ==================================================
   QUESTÃO: CONTAGEM DE FREQUÊNCIAS
   ================================================== */
void contarFrequencia(char *arquivo, int freq[]){
    FILE *fp = fopen(arquivo,"r");
    if(fp == NULL)
        return;
    for(int i=0;i<ASCII;i++)
        freq[i]=0;
    int c;

    while((c=fgetc(fp)) != EOF){
        freq[c]++;
    }
    fclose(fp);
}

/* ==================================================
   QUESTÃO: CONSTRUÇÃO DA ÁRVORE DE HUFFMAN
   ================================================== */
No* criarArvore(int freq[]){
    FilaPrioridade fila;
    fila.dados = malloc(ASCII * sizeof(No*));
    fila.tamanho = 0;

    /*
        Cria um nó para cada caractere existente
        e insere na fila.
    */
    for(int i=0;i<ASCII;i++){
        if(freq[i] > 0){
            No *novo = criarNo(i,freq[i]);
            inserirFila(&fila,novo);
        }
    }

    /*
        Junta sempre os dois nós
        de menor frequência.
    */
    while(fila.tamanho > 1){
        No *esq = removerFila(&fila);
        No *dir = removerFila(&fila);
        No *pai = criarNo('\0', esq->frequencia + dir->frequencia);
        pai->esq = esq;
        pai->dir = dir;
        inserirFila(&fila,pai);
    }
    No *raiz = removerFila(&fila);
    free(fila.dados);
    return raiz;
}

/* ==================================================
   QUESTÃO: GERAÇÃO DOS CÓDIGOS
   ================================================== */
void gerarCodigos(No *raiz, char codigo[], int pos, TabelaCodigo tabela[], int *tam){
    if(raiz == NULL)
        return;

    /*
        Caso folha:
        guarda o código encontrado.
    */
    if(raiz->esq == NULL && raiz->dir == NULL){
        codigo[pos]='\0';
        tabela[*tam].caractere = raiz->caractere;
        strcpy(tabela[*tam].codigo, codigo);
        tabela[*tam].tamanho = pos;
        (*tam)++;
        return;
    }
    codigo[pos]='0';
    gerarCodigos(raiz->esq, codigo, pos+1, tabela, tam);
    codigo[pos]='1';
    gerarCodigos(raiz->dir, codigo, pos+1, tabela, tam);
}

/* ==================================================
   QUESTÃO: COMPACTAÇÃO
   ================================================== */
void compactar(char *entrada, char *saida, TabelaCodigo tabela[], int tam){
    FILE *in = fopen(entrada,"r");
    FILE *out = fopen(saida,"w");
    int c;

    while((c=fgetc(in)) != EOF){
        for(int i=0;i<tam;i++){
            if(tabela[i].caractere == c){
                fprintf(out, "%s", tabela[i].codigo);
                break;
            }
        }
    }
    fclose(in);
    fclose(out);
}

/* ==================================================
   QUESTÃO: DESCOMPACTAÇÃO
   ================================================== */
void descompactar(char *entrada, char *saida, No *raiz){
    FILE *in = fopen(entrada,"r");
    FILE *out = fopen(saida,"w");
    No *atual = raiz;
    char bit;

    while((bit=fgetc(in)) != EOF){
        if(bit == '0')
            atual = atual->esq;
        else
            atual = atual->dir;
        /*
            Chegou em uma folha:
            recupera o caractere.
        */
        if(atual->esq == NULL && atual->dir == NULL)
        {
            fputc(atual->caractere, out);
            atual = raiz;
        }
    }
    fclose(in);
    fclose(out);
}