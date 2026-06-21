/*
Alunos:
    Gabriel Adib - 2510466,
    Gabriel Félix - 2510619

Compilação:
    gcc main.c huffman.c -o trab2
    ./trab2
*/

#include <stdio.h>
#include "huffman.h"

int main(){
    int freq[ASCII];

    /*
        Arquivo fornecido pelo enunciado
    */
    char arquivo[] =
    "textoCompactadorDescompactador.txt";

    /*
        Questão:
        Criação do histograma.
    */
    contarFrequencia(arquivo,
                     freq);
    printf("Tabela de frequencias:\n\n");

    for(int i=0;i<ASCII;i++){
        if(freq[i]>0)
            printf("%c : %d\n",
                   i,
                   freq[i]);
    }

    /*
        Questão:
        Construção da árvore.
    */
    No *raiz =
    criarArvore(freq);

    /*
        Questão:
        Geração dos códigos Huffman.
    */
    TabelaCodigo tabela[ASCII];
    int tamanho=0;
    char codigo[256];

    gerarCodigos(raiz,
                 codigo,
                 0,
                 tabela,
                 &tamanho);

    printf("\nTabela Huffman:\n\n");
    for(int i=0;i<tamanho;i++){
        printf("%c -> %s\n",
               tabela[i].caractere,
               tabela[i].codigo);
    }

    /*
        Questão:
        Compactação.
    */
    compactar(arquivo,
              "compactado.txt",
              tabela,
              tamanho);

    /*
        Questão:
        Descompactação.
    */
    descompactar("compactado.txt",
                 "descompactado.txt",
                 raiz);
    printf("\nProcesso finalizado.\n");

    return 0;
}