#include "estados.h"

/**
 * Lista todos os países cadastrados no banco de dados
 * Autor: Ana Luiza, Alexandre, Samuel, Antonio
 * Data: 02/10/2017
 */

void mostrarListagemEstados() {
    int opcao;
    
    do {
        limparTela();

        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        printf("| LISTAGEM DE ESTADOS                                                                                               |\n");
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        printf("| ID         | NOME                             | UF                     | ID PAÍS                                  |\n");
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        MYSQL mysql;
        mysql_init(&mysql);

        if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
            //Executa o comando de consulta
            if (mysql_query(&mysql, "select idEstado, nomeEstado, uf, idPais from estados order by nomeEstado") == 0) {
                //Obtém o resultado
                MYSQL_RES *resultado = mysql_store_result(&mysql);

                MYSQL_ROW linha;

                while ((linha = mysql_fetch_row(resultado))) {
                    int idEstado = atoi(linha[0]), idPais = atoi(linha[3]);
                    char *nomeEstado = linha[1], *uf = linha[2];

                    //Imprime
                    printf("| %10d | %-32s | %-22s | %40d |\n", idEstado, nomeEstado, uf, idPais);
                }

                mysql_free_result(resultado);
                mysql_close(&mysql);
            } else {
                printf("%s\n", mysql_error(&mysql));
            }
        } else {
            printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar
        }

        printf("|-------------------------------------------------------------------------------------------------------------------|\n");

        printf("O que deseja fazer?\n");
        printf("1) Cadastrar um novo Estado\n");
        printf("2) Alterar um Estado\n");
        printf("3) Excluir um Estado\n");
        printf("4) Listar Países\n");
        printf("5) Voltar ao menu principal\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1: 
                mostrarCadastroEstado();
                break;
            case 2: 
                mostrarAlteracaoEstado();
                break;
            case 3: 
                mostrarExclusaoEstado();
                break;
            case 4:
                mostrarListagemPaises_Cadastro();
                break;
        }
    } while (opcao != 5);
}

void mostrarListagemPaises_Cadastro(){    
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
        printf("Pressione qualquer tecla para retornar ao menu \n");
        getchar();  
}


void mostrarCadastroEstado() {
    Estado e;
    
    limparTela();    
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");
    printf("| CADASTRO DE ESTADOS                                                                                               |\n");
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");

    printf("| NOME: ");
    fgets(e.nomeEstado, sizeof (e.nomeEstado), stdin);
    int tamanhoNome = strlen(e.nomeEstado);
    e.nomeEstado[tamanhoNome - 1] = '\0'; //Retira o \n do final da string e coloca \0

    printf("| UF: ");
    fgets(e.uf, sizeof (e.uf), stdin);
    int tamanhoUf = strlen(e.uf);
    e.uf[tamanhoUf ] = '\0'; //Retira o \n do final da string e coloca \0
    
    printf("| ID PAÍS: ");
    scanf("%d", &e.idPais);
    getchar();
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");

    printf("Deseja realmente criar o país? (S/N) ");
    char resposta = getchar();
    getchar();

    if (resposta == 'S' || resposta == 's') {
        inserirEstado(e);
    }
}

void inserirEstado(Estado e) {
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "insert into estados(nomeEstado, uf, idPais) values('%s','%s',%d)", e.nomeEstado, e.uf, e.idPais);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão

            printf("Estado cadastrado com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar
    }
}

void alterarEstado(Estado e) {
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "update estados set nomeEstado = '%s', uf = '%s', idPais = %d where idEstado = %d", e.nomeEstado, e.uf, e.idPais, e.idEstado);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão

            printf("Estado alterado com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

void excluirEstado(int codigo) {
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "delete from estados where idEstado = %d", codigo);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão

            printf("Estado excluído com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

Estado* selecionarEstado(int codigo) {
    //Cria a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Efetua a conexão
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        char sql[500];
        snprintf(sql, 500, "select idEstado, nomeEstado, uf, idPais from estados where idEstado = %d", codigo);

        //Executa o comando de consulta
        if (mysql_query(&mysql, sql) == 0) {
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            int idEstado;
            char *nomeEstado;
            char *uf;
            int idPais;
            if ((linha = mysql_fetch_row(resultado))) {
                //Obtém cada coluna na órdem
                idEstado = atoi(linha[0]);
                idPais = atoi(linha[3]);

                //Libera os resultado e fecha a conexão
                mysql_free_result(resultado);
                mysql_close(&mysql);

                Estado *e = (Estado *) malloc(sizeof(Estado)); // alocação dinâmica de memória
                strncpy(e->nomeEstado, linha[1], 60);
                strncpy(e->uf, linha[2], 3);
                e->idEstado = idEstado;
                e->idPais = idPais;

                //Imprime cada linha
                return e;
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

void mostrarAlteracaoEstado() {
    int codigo;
    printf("Digite o código do estado que deseja alterar: ");
    scanf("%d", &codigo);
    getchar();

    Estado *e = selecionarEstado(codigo);

    limparTela();
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");
    printf("| CADASTRO DE ESTADO                                                                                                |\n");
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");
    printf("| Id: %d\n", e->idEstado);
    printf("| Nome: %s\n", e->nomeEstado);
    printf("| UF: %s\n", e->uf);
    printf("| idPais: %d\n", e->idPais);
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");

    printf("Digite o novo nome do estado: ");
    char nomeEstado[100];
    fgets(nomeEstado, sizeof (nomeEstado), stdin);
    int tamanhoNome = strlen(nomeEstado);
    nomeEstado[tamanhoNome - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(e->nomeEstado, nomeEstado, 100);

    printf("Digite o novo uf do estado: ");
    char uf[3];
    fgets(uf, sizeof (uf), stdin);
    int tamanhoUf = strlen(uf);
    uf[tamanhoUf] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(e->uf, uf, 3);

    printf("Digite o novo id do Pais: ");
    scanf("%d", &e->idPais);
    getchar();
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");

    printf("Deseja realmente salvar as alterações? (S/N) ");
    char resposta = getchar();
    getchar();

    if (resposta == 'S' || resposta == 's') {
        alterarEstado(*e);
    }
    
    getchar();
}

void mostrarExclusaoEstado() {
    int codigo;
    printf("Digite o código do estado que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    excluirEstado(codigo);
}