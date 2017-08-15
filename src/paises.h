#ifndef PAISES_H
#define PAISES_H

#include <stdio.h>
#include <mysql/mysql.h>
#include "diretivas_conexao.h"
#include "gerais.h"

/**
 * Estrutura para representar um pais
 */
typedef struct {
	int id;
	char nome[100];
} Pais;

/**
 * Lista todos os países cadastrados no banco de dados
 */
void mostrarListagemPaises();

/**
 * Apresenta o cadastro de países
 */
void mostrarCadastroPaises();

/**
 * Função para inserção de um país no banco de dados
 */
void inserirPais(Pais p);

#endif
