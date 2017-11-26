#include "gerais.h"
#include "paises.h"
#include "produtos.h"
#include <string.h>
#include<stdio.h>


/**
 * Limpa a tela
 * Autor: Ronneesley Moura Teles
 * Data: 15/08/2017
 */
void limparTela(){
    system("clear");
}

/*
 Lê uma string do teclado coletando letra por letra com o getchar
 e inserindo em cada posição do vetor quando não se tem um '\n' nem '\0'
 e se a String não esgotou sua capacidade (tamanho-1).
 ao fim insere '\0' após a última letra.
 -João Neto-
 */
void leString(char s[], int tam) {
    char letra;
    int i;
    letra = getchar();
    for (i = 0; (letra != 10 && letra != 13) && i < tam - 1; i++) {
        s[i] = letra;
        letra = getchar();
    }
    s[i] = '\0';
}
