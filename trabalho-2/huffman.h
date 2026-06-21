/*
Alunos:
    Gabriel Adib - 2510466,
    Gabriel Félix - 2510619
*/

#ifndef HUFFMAN_H
#define HUFFMAN_H
#define ASCII 256

/*
    Estrutura de um nó da árvore de Huffman.
*/
typedef struct no{
    unsigned char caractere;
    int frequencia;
    struct no *esq;
    struct no *dir;
}No;

/*
    Tabela contendo:

    caractere
    frequência de ocorrência
*/
typedef struct{
    unsigned char caractere;
    int frequencia;
}TabelaFreq;

/*
    Tabela contendo:

    caractere
    código binário gerado
    tamanho do código
*/
typedef struct{
    unsigned char caractere;
    char codigo[256];
    int tamanho;
}TabelaCodigo;

/* Questão: criação do histograma */
void contarFrequencia(char *arquivo,
                      int freq[]);

/* Questão: construção da árvore de Huffman */
No* criarArvore(int freq[]);

/* Questão: geração da tabela de códigos */
void gerarCodigos(No *raiz,
                  char codigo[],
                  int pos,
                  TabelaCodigo tabela[],
                  int *tam);

/* Questão: compactação */
void compactar(char *entrada,
               char *saida,
               TabelaCodigo tabela[],
               int tam);

/* Questão: descompactação */
void descompactar(char *entrada,
                  char *saida,
                  No *raiz);

#endif