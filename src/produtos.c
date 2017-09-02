#include "produtos.h"
int TESTE;

/**
 * Mostra os produtos cadastrados
 * Autor: João Crisóstomo de Siqueira Neto 
 * Data: 26/08/2017
 */
void mostrarListagemProdutos(){ 
	int opcao;

	do {
		limparTela();
		printf("|------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		printf("|                                                               LISTAGEM DE PRODUTOS                                                                   |\n");
		printf("|------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		printf("| ID |         NOME         |    FORNECEDOR  | PREÇO/COMPRA | PREÇO/VENDA  |             DESCRIÇÃO                  | EM ESTOQUE |   DATA DE CADASTRO  |\n");
		printf("|------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		
		MYSQL mysql;
		mysql_init(&mysql);

		if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
			//Executa o comando de consulta
			if (mysql_query(&mysql, "SELECT id, nome, fornecedor, precoCompra, precoVenda, descricao, qtdEmEstoque, dataCadastro FROM produtos ORDER BY nome") == 0){
				//Obtém o resultado
				MYSQL_RES *resultado = mysql_store_result(&mysql);

				//Cria uma variável para guardar a linha
				MYSQL_ROW linha;
				while ( (linha = mysql_fetch_row(resultado)) ){
					//Obtém cada coluna na órdem
					int id = atoi(linha[0]), qtdEmEstoque = atoi(linha[6]),i , j;
					char *nome = linha[1], *fornecedor = linha[2], *descricao = linha[5], *dataCadastro = linha[7];

					

					float precoCompra = atof(linha[3]), precoVenda = atof(linha[4]);

					//Imprime cada linha
					printf("| %2d | %-20s | %-15s| R$ %-10.2f| R$ %-10.2f| %-39s| %-10d | %-5s |\n",
					 id, nome,fornecedor, precoCompra, precoVenda, descricao, qtdEmEstoque, dataCadastro);
					
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

		printf("|------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		printf("\nO que deseja fazer?\n");
		printf("1) Cadastrar um novo produto\n");
		printf("2) Alterar um produto\n");
		printf("3) Excluir um produto\n");
		printf("4) Voltar ao menu principal\n\n");
		printf("Digite a opção desejada: ");
		scanf("%d", &opcao); getchar();

		switch (opcao){
			case 1: mostrarCadastroProduto(); break;
			//case 2: alterarProduto(); break;
			//case 3: excluirProduto(); break;
		}
	} while (opcao != 4);
}




/**
 * mostra tela de cadastro de produtos.
 * Autor: João Crisóstomo de Siqueira Neto 
 * Data: 26/08/2017
 */
void mostrarCadastroProduto() {
	Produto p;

	limparTela();
	printf("|-------------------------------------------------------------------------------------------------------------------|\n");
	printf("|                                             CADASTRO DE PRODUTO                                                   |\n");
	printf("|-------------------------------------------------------------------------------------------------------------------|\n");

	printf("| NOME: ");
	fgets(p.nome, sizeof(p.nome), stdin);
	int tamanho = strlen(p.nome); p.nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	

	printf("| FORNECEDOR: ");
	fgets(p.fornecedor, sizeof(p.fornecedor), stdin);
	tamanho = strlen(p.fornecedor); p.fornecedor[tamanho -1] = '\0';

	printf("| PREÇO DE COMPRA: R$ ");
	scanf("%f",&p.precoCompra);
	getchar();

	printf("| PREÇO DE VENDA: R$ ");
	scanf("%f",&p.precoVenda);
	getchar();

	printf("| DESCRIÇÃO: ");
	fgets(p.descricao, sizeof(p.descricao), stdin);
	tamanho = strlen(p.descricao); p.descricao[tamanho -1] = '\0';

	printf("| QUANTIDADE EM ESTOQUE: ");
	scanf("%d",&p.qtdEmEstoque);
	getchar();	

	printf("|-------------------------------------------------------------------------------------------------------------------|\n");

	printf("Deseja realmente criar o produto? (S/N) ");
	char resposta = getchar(); getchar();

	if (resposta == 'S' || resposta == 's'){
		inserirProduto(p);
	}
}

/**
 * Insere um novo produto
 * Autor: João Crisóstomo de Siqueira Neto 
 * Data: 26/08/2017
 */
	//Inicializa a variável de conexão com o MySQL
void inserirProduto(Produto p){
	MYSQL mysql;
	mysql_init(&mysql);

	//Conecta no banco de dados
	if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
		//Cria o comando SQL para envio
		char sql[500];

		snprintf(sql, 500, "INSERT INTO produtos(nome,fornecedor,precoCompra,precoVenda,descricao,qtdEmEstoque) values('%s','%s',%f,%f,'%s',%d)"
			, p.nome, p.fornecedor,p.precoCompra,p.precoVenda,p.descricao,p.qtdEmEstoque);
		

		//Envia o comando e analisa a resposta
		if (mysql_query(&mysql, sql) == 0){
			mysql_close(&mysql); //Encerra a conexão

			printf("Produto cadastrado com sucesso\n"); //Exibe mensagem de sucesso
		} else {
			printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
		}
	} else {
		printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
	}
}

/**
 * Insere um novo produto
 * Autor:  
 * Data: /08/2017
 */

//void alterarProduto(){

//}

 /**
 * Exclui um  produto
 * Autor:  
 * Data: /08/2017
 */

//void excluirProduto(){

//}