#include "paises.h"

/**
 * Lista todos os países cadastrados no banco de dados
 * Autor: Ronneesley Moura Teles
 * Data: 15/08/2017
 */
void mostrarListagemPaises(){
	limparTela();
	printf("|-------------------------------------------------------------------------------------------------------------------|\n");
	printf("| LISTAGEM DE PAÍSES                                                                                                |\n");
	printf("|-------------------------------------------------------------------------------------------------------------------|\n");
	printf("| ID         | NOME                                                                                                 |\n");
	printf("|-------------------------------------------------------------------------------------------------------------------|\n");

	//Cria a variável de conexão com o MySQL
	MYSQL mysql;
	mysql_init(&mysql);

	//Efetua a conexão
	if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
		//Executa o comando de consulta
		if (mysql_query(&mysql, "select id, nome from paises order by nome") == 0){
			//Obtém o resultado
			MYSQL_RES *resultado = mysql_store_result(&mysql);

			//Cria uma variável para guardar a linha
			MYSQL_ROW linha;
			int *id; 
			char *nome;
			while ( (linha = mysql_fetch_row(resultado)) ){
				//Obtém cada coluna na órdem
				*id = atoi(linha[0]);
				nome = linha[1];

				//Imprime cada linha
				printf("| %10d | %-100s |\n", *id, nome);
			}

			//Libera os resultado e fecha a conexão
			mysql_free_result(resultado);
			mysql_close(&mysql);
		} else {
			printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
		}
	} else {
		printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
	}

	printf("|-------------------------------------------------------------------------------------------------------------------|\n");

	printf("Deseja cadastrar um novo país? (S/N) ");
	char resposta = getchar(); getchar();

	if (resposta == 'S' || resposta == 's'){
		mostrarCadastroPaises();
	}
}

/**
 * Apresenta o cadastro de países
 * Autor: Ronneesley Moura Teles
 * Data: 15/08/2017
 */
void mostrarCadastroPaises() {
	Pais p;

	limparTela();
	printf("|-------------------------------------------------------------------------------------------------------------------|\n");
	printf("| CADASTRO DE PAÍSES                                                                                                |\n");
	printf("|-------------------------------------------------------------------------------------------------------------------|\n");

	printf("| NOME: ");
	fgets(p.nome, sizeof(p.nome), stdin);	

	printf("|-------------------------------------------------------------------------------------------------------------------|\n");

	printf("Deseja realmente criar o país? (S/N) ");
	char resposta = getchar(); getchar();

	if (resposta == 'S' || resposta == 's'){
		inserirPais(p);
	}
}

/**
 * Função responsável pela inserção de um país no banco de dados
 * Autor: Ronneesley Moura Teles
 * Data: 15/08/2017
 */
void inserirPais(Pais p){
	//Inicializa a variável de conexão com o MySQL
	MYSQL mysql;
	mysql_init(&mysql);

	//Conecta no banco de dados
	if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
		//Cria o comando SQL para envio
		char sql[500];
		snprintf(sql, 500, "insert into paises(nome) values('%s')", p.nome);

		//Envia o comando e analisa a resposta
		if (mysql_query(&mysql, sql) == 0){
			mysql_close(&mysql); //Encerra a conexão

			printf("País cadastrado com sucesso\n"); //Exibe mensagem de sucesso
		} else {
			printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
		}
	} else {
		printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
	}
}
