/**
 * Cadastro de clientes
 * 
 * Autores:
 * Bruno Geovane
 * Gilson Soares
 * Juliana Gomes
 * Marco Aurelio
 * Ruan Miller
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"

/**
 * Exibe a lista de clientes já cadastrados no banco de dados
 */
void mostrarListagemClientes(){
    int opcao;

    do {
        limparTela();
        printf("|--------------------------------------------------------------------|\n");
        printf("| LISTAGEM DE CLIENTES                                               |\n");
        printf("|--------------------------------------------------------------------|\n");
        printf("| ID    | NOME  | SEXO  | DATA NASCIMENTO  | ENDERECO  | CIDADE    | CEP   | TELEFONE  | CPF   | RG    | PROFISSAO |\n");
        printf("|--------------------------------------------------------------------|\n");

        //Cria a variável de conexão com o MySQL
        MYSQL mysql;
        mysql_init(&mysql);

        //Efetua a conexão
        if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
            
            //Executa o comando de consulta
            if (mysql_query(&mysql, "SELECT id, nome, sexo, data, endereco, cidade, cep, telefone, cpf, rg, profissao"
                    " FROM clientes ORDER BY nome") == 0){
                
                //Obtém o resultado
                MYSQL_RES *resultado = mysql_store_result(&mysql);

                //Cria uma variável para guardar a linha
                MYSQL_ROW linha;
                while ( (linha = mysql_fetch_row(resultado)) ){
                    
                    //Obtém cada coluna na ordem
                    int id = atoi(linha[0]);
                    char *nome = linha[1];
                    char *sexo = linha[2];
                    char *datanasc = linha[3];
                    char *endereco = linha[4];
                    char *cidade = linha[5];
                    char *cep = linha[6];
                    char *telefone = linha[7];
                    char *cpf = linha[8];
                    char *rg = linha[9];
                    char *profissao = linha[10];

                    //Imprime cada linha
                    printf("| %d | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s |\n",
                            id, nome, sexo, datanasc, endereco, cidade, cep, telefone, cpf, rg, profissao);
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

        printf("|--------------------------------------------------------------------|\n");

        printf("O que deseja fazer?\n");
        printf("1) Cadastrar um novo cliente\n");
        printf("2) Alterar um cliente\n");
        printf("3) Excluir um cliente\n");
        printf("4) Voltar ao menu principal\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao); getchar();

        switch (opcao){
            case 1: mostrarCadastroCliente(); break;
            case 2: mostrarAlteracaoCliente(); break;
            case 3: mostrarExclusaoCliente(); break;
        }
    } while (opcao != 4);
}

/**
 * Exibe a tela para cadastro de um novo cliente
 */
void mostrarCadastroCliente() {
    Cliente c;

    limparTela();
    printf("|--------------------------------------------------------------------|\n");
    printf("| CADASTRO DE CLIENTES                                               |\n");
    printf("|--------------------------------------------------------------------|\n");

    printf("| Informe o nome completo para cadastro: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    int tamanho = strlen(c.nome);
    c.nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	
    printf("|--------------------------------------------------------------------|\n");

    printf("| Informe o sexo [M] ou [F]: ");
    fgets(c.sexo, sizeof(c.sexo), stdin);
    tamanho = strlen(c.sexo);
    c.sexo[tamanho - 1] = '\0';	
    printf("|--------------------------------------------------------------------|\n");

    printf("| Informe data de nascimento [dd/mm/aaaa]: ");
    fgets(c.datanasc, sizeof(c.datanasc), stdin);
    tamanho = strlen(c.datanasc);
    c.datanasc[tamanho - 1] = '\0';	
    printf("|--------------------------------------------------------------------|\n");
    
    printf("| Informe o endereco de residencia:  ");
    fgets(c.endereco, sizeof(c.endereco), stdin);
    tamanho = strlen(c.endereco);
    c.endereco[tamanho - 1] = '\0';	
    printf("|--------------------------------------------------------------------|\n");
    
    printf("| Informe a cidade:  ");
    fgets(c.cidade, sizeof(c.cidade), stdin);
    tamanho = strlen(c.cidade); 
    c.cidade[tamanho - 1] = '\0';	
    printf("|--------------------------------------------------------------------|\n");
    
    printf("| Informe o CEP: ");
    fgets(c.cep, sizeof(c.cep), stdin);
    tamanho = strlen(c.cep); 
    c.cep[tamanho - 1] = '\0';	
    printf("|--------------------------------------------------------------------|\n");
    
    printf("| Informe o telefone de contato [(DD)9XXXX-XXXX]: ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    tamanho = strlen(c.telefone);
    c.telefone[tamanho - 1] = '\0';	
    printf("|--------------------------------------------------------------------|\n");
    
    printf("| Informe o CPF: ");
    fgets(c.cpf, sizeof(c.cpf), stdin);
    tamanho = strlen(c.cpf); 
    c.cpf[tamanho - 1] = '\0';	
    printf("|--------------------------------------------------------------------|\n");
    
    printf("| Informe o RG: ");
    fgets(c.rg, sizeof(c.rg), stdin);
    tamanho = strlen(c.rg); 
    c.rg[tamanho - 1] = '\0';	
    printf("|--------------------------------------------------------------------|\n");
    
    printf("| Informe a profissao: ");
    fgets(c.profissao, sizeof(c.profissao), stdin);
    tamanho = strlen(c.profissao); 
    c.profissao[tamanho - 1] = '\0';	
    printf("|--------------------------------------------------------------------|\n");
    
    printf("Deseja realmente criar o cliente? (S/N) ");
    char resposta = getchar(); getchar();

    if (resposta == 'S' || resposta == 's'){
        inserirCliente(c);
    }
}

/**
 * Efetua a insercao do novo cliente no banco de dados
 * @param c
 */
void inserirCliente(Cliente c){
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        //Cria o comando SQL para envio
        char sql[2000];
        snprintf(sql, 2000, "INSERT INTO clientes(nome, sexo, data, endereco, cidade, cep, telefone, cpf, rg, profissao)"
                " VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
                c.nome, c.sexo, c.datanasc, c.endereco, c.cidade, c.cep, c.telefone, c.cpf, c.rg, c.profissao);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão

            printf("Cliente cadastrado com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

/**
 * Efetua a alteracao dos campos do cliente no banco de dados
 * @param c
 */
void alterarCliente(Cliente c){
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "UPDATE clientes SET nome = '%s' WHERE id = %d", c.nome, c.id);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão

            printf("Cliente alterado com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

/**
 * Efetua a exclusao das informacoes do cliente do banco de dados
 * @param codigo
 */
void excluirCliente(int codigo){
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "DELETE FROM clientes WHERE id = %d", codigo);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão

            printf("Cliente excluído com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

/**
 * Efetua a selecao dos dados do cliente solicitado no banco de dados
 * @param codigo
 * @return 
 */
Cliente* selecionarCliente(int codigo){
    //Cria a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Efetua a conexão
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        char sql[500];
        snprintf(sql, 500, "SELECT id, nome FROM clientes WHERE id = %d", codigo);

        //Executa o comando de consulta
        if (mysql_query(&mysql, sql) == 0){
            
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            int id; 
            char *nome;
            if ( (linha = mysql_fetch_row(resultado)) ){
            
                //Obtém cada coluna na ordem
                id = atoi(linha[0]);

                //Libera os resultado e fecha a conexão
                mysql_free_result(resultado);
                mysql_close(&mysql);

                Cliente cliente;
                Cliente *c = &cliente;
                strncpy(c->nome, linha[1], 100);
                c->id = id;

                //Imprime cada linha
                return c;
            } else {
                //Libera os resultado e fecha a conexão
                mysql_free_result(resultado);
                mysql_close(&mysql);

                return NULL;
            }
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

/**
 * Exibe os dados do cliente antes de serem alterados
 */
void mostrarAlteracaoCliente(){
    int codigo;
    printf("Digite o código do cliente que deseja alterar: ");
    scanf("%d", &codigo); getchar();

    Cliente *c = selecionarCliente(codigo);

    limparTela();
    printf("|--------------------------------------------------------------------|\n");
    printf("| CADASTRO DE CLIENTES                                               |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("| Id: %d\n", c->id);
    printf("| Nome: %s\n", c->nome);
    printf("|--------------------------------------------------------------------|\n");

    printf("Digite o novo nome do cliente: ");
    char nome[100];
    fgets(nome, sizeof(nome), stdin);
    int tamanho = strlen(nome); nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(c->nome, nome, 100);
    printf("|--------------------------------------------------------------------|\n");

    printf("Deseja realmente salvar as alterações? (S/N) ");
    char resposta = getchar(); getchar();

    if (resposta == 'S' || resposta == 's'){
        alterarCliente(*c);
    }

    getchar();
}

/**
 * Exibe os dados dos clientes para selecionar qual deverá ser excluído do banco de dados
 */
void mostrarExclusaoCliente(){
    int codigo;
    printf("Digite o código do cliente que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    excluirCliente(codigo);
    getchar();
}