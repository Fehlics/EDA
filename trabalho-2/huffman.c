/*
Alunos:
    Gabriel Adib - 2510466,
    Gabriel Félix - 2510619
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/*
    Questão:
    Construção do histograma de caracteres.
*/
void contarFrequencia(char *arquivo,
                      int freq[]){
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

/*
    Questão:
    Criação da árvore de Huffman.
*/
No* criarNo(unsigned char c,
            int freq){
    No *novo = malloc(sizeof(No));
    novo->caractere=c;
    novo->frequencia=freq;
    novo->esq=NULL;
    novo->dir=NULL;

    return novo;
}

No* criarArvore(int freq[]){
    No *raiz=NULL;

    /*
        Versão simplificada:
        cria uma árvore apenas com
        os caracteres existentes.
    */
    for(int i=0;i<ASCII;i++){
        if(freq[i]>0){
            No *novo =
            criarNo(i,freq[i]);
            if(raiz==NULL)
                raiz=novo;
            else{
                /*
                    Inserção simplificada.
                    Em uma implementação completa,
                    seria usada uma fila de prioridade.
                */
                novo->dir=raiz;
                raiz=novo;
            }
        }
    }

    return raiz;
}

/*
    Questão:
    Geração dos códigos binários.
*/
void gerarCodigos(No *raiz,
                  char codigo[],
                  int pos,
                  TabelaCodigo tabela[],
                  int *tam){
    if(raiz==NULL)
        return;
    if(raiz->esq==NULL &&
       raiz->dir==NULL){
        codigo[pos]='\0';
        tabela[*tam].caractere =
        raiz->caractere;
        strcpy(tabela[*tam].codigo,
               codigo);
        tabela[*tam].tamanho=pos;
        (*tam)++;

        return;
    }

    codigo[pos]='0';
    gerarCodigos(raiz->esq,
                 codigo,
                 pos+1,
                 tabela,
                 tam);
    codigo[pos]='1';
    gerarCodigos(raiz->dir,
                 codigo,
                 pos+1,
                 tabela,
                 tam);
}

/*
    Questão:
    Compactação do arquivo.
*/
void compactar(char *entrada,
               char *saida,
               TabelaCodigo tabela[],
               int tam){
    FILE *in=fopen(entrada,"r");
    FILE *out=fopen(saida,"w");
    int c;

    while((c=fgetc(in))!=EOF){
        for(int i=0;i<tam;i++){
            if(tabela[i].caractere==c){
                fprintf(out,
                        "%s",
                        tabela[i].codigo);
                break;
            }
        }
    }
    fclose(in);
    fclose(out);
}

/*
    Questão:
    Descompactação.
*/
void descompactar(char *entrada,
                  char *saida,
                  No *raiz){
    FILE *in=fopen(entrada,"r");
    FILE *out=fopen(saida,"w");
    No *atual=raiz;
    char bit;

    while((bit=fgetc(in))!=EOF){
        if(bit=='0')
            atual=atual->esq;
        else
            atual=atual->dir;
        if(atual->esq==NULL &&
           atual->dir==NULL){
            fputc(atual->caractere,out);
            atual=raiz;
        }
    }

    fclose(in);
    fclose(out);
}