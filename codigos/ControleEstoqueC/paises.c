#include "paises.h"

/**
 * Lista todos os países cadastrados no banco de dados
 * Autor: Ronneesley Moura Teles
 * Data: 15/08/2017
 */
void mostrarListagemPaises(){
    int opcao;

    do {
        limparTela();
        printf("|--------------------------------------------------------------------|\n");
        printf("| LISTAGEM DE PAÍSES                                                 |\n");
        printf("|--------------------------------------------------------------------|\n");
        printf("| ID         | NOME                                                  |\n");
        printf("|--------------------------------------------------------------------|\n");

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
                while ( (linha = mysql_fetch_row(resultado)) ){
                    //Obtém cada coluna na órdem
                    int id = atoi(linha[0]);
                    char *nome = linha[1];

                    //Imprime cada linha
                    printf("| %10d | %-53s |\n", id, nome);
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
        printf("1) Cadastrar um novo país\n");
        printf("2) Alterar um país\n");
        printf("3) Excluir um país\n");
        printf("4) Voltar ao menu principal\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao); getchar();

        switch (opcao){
            case 1: mostrarCadastroPais(); break;
            case 2: mostrarAlteracaoPais(); break;
            case 3: mostrarExclusaoPais(); break;
        }
    } while (opcao != 4);
}

/**
 * Apresenta o cadastro de países
 * Autor: Ronneesley Moura Teles
 * Data: 15/08/2017
 */
void mostrarCadastroPais() {
    Pais p;

    limparTela();
    printf("|--------------------------------------------------------------------|\n");
    printf("| CADASTRO DE PAÍSES                                                 |\n");
    printf("|--------------------------------------------------------------------|\n");

    printf("| NOME: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    int tamanho = strlen(p.nome); p.nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	
    printf("|--------------------------------------------------------------------|\n");

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

void alterarPais(Pais p){
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "update paises set nome = '%s' where id = %d", p.nome, p.id);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão

            printf("País alterado com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

void excluirPais(int codigo){
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "delete from paises where id = %d", codigo);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão

            printf("País excluído com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

Pais* selecionarPais(int codigo){
    //Cria a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Efetua a conexão
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        char sql[500];
        snprintf(sql, 500, "select id, nome from paises where id = %d", codigo);

        //Executa o comando de consulta
        if (mysql_query(&mysql, sql) == 0){
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            int id; 
            char *nome;
            if ( (linha = mysql_fetch_row(resultado)) ){
                //Obtém cada coluna na órdem
                id = atoi(linha[0]);

                //Libera os resultado e fecha a conexão
                mysql_free_result(resultado);
                mysql_close(&mysql);

                Pais pais;
                Pais *p = &pais;
                strncpy(p->nome, linha[1], 100);
                p->id = id;

                //Imprime cada linha
                return p;
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
    getchar();
}

void mostrarAlteracaoPais(){
    int codigo;
    printf("Digite o código do país que deseja alterar: ");
    scanf("%d", &codigo); getchar();

    Pais *p = selecionarPais(codigo);

    limparTela();
    printf("|--------------------------------------------------------------------|\n");
    printf("| CADASTRO DE PAÍSES                                                 |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("| Id: %d\n", p->id);
    printf("| Nome: %s\n", p->nome);
    printf("|--------------------------------------------------------------------|\n");

    printf("Digite o novo nome do país: ");
    char nome[100];
    fgets(nome, sizeof(nome), stdin);
    int tamanho = strlen(nome); nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(p->nome, nome, 100);
    printf("|--------------------------------------------------------------------|\n");

    printf("Deseja realmente salvar as alterações? (S/N) ");
    char resposta = getchar(); getchar();

    if (resposta == 'S' || resposta == 's'){
        alterarPais(*p);
    }

    getchar();
}

void mostrarExclusaoPais(){
    int codigo;
    printf("Digite o código do país que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    excluirPais(codigo);
    getchar();
}