#include "funcionarios.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Mostra os Funcionarios cadastrados
 * Autor: Bruno Qualhato
 * Data: 26/08/2017
 */

// teste

void mostrarListagemFuncionarios() {
    int opcao;

    do {
        limparTela();
        printf("|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        printf("|                                                                                                    LISTAGEM DE FUNCIONARIOS                                                                                       |\n");
        printf("|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        printf("| ID |         NOME         |    SEXO  | DATA DE NASCIMENTO | ENDEREÇO  |   CIDADE   | CEP |   TELEFONE  |    CPF    |  RG  |  PROFISSAO  |  PIS/PASEP |          \n");
        printf("|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");

        MYSQL mysql;
        mysql_init(&mysql);

        if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
            //Executa o comando de consulta
            if (mysql_query(&mysql, "SELECT  idFuncionario,"
                    " NomeFuncionario,"
                    " SexoFuncionario,"
                    " DataNascimentoFuncionario,"
                    " EnderecoFuncionario,"
                    " cidadeFuncionario,"
                    " cepFuncionario,"
                    " telefoneFuncionario,"
                    "cpfFuncionario, FROM Funcionarios ORDER BY nome") == 0) {
                //Obtém o resultado
                MYSQL_RES *resultado = mysql_store_result(&mysql);

                //Cria uma variável para guardar a linha
                MYSQL_ROW linha;
                while ((linha = mysql_fetch_row(resultado))) {
                    //Obtém cada coluna na órdem
                    int id = atoi(linha[0]);
                    char *nome = linha[1];
                    char *sexo = linha[2];
                    char *datanascimento = linha[3];
                    char *endereco = linha[4];
                    char *cidade = linha[5];
                    int cep = atoi(linha[6]);
                    int telefone = atoi(linha[7]);
                    int cpf = atoi(linha[8]);
                    int rg = atoi(linha[9]);
                    char *profissao = linha[10];
                    int pispasep = atoi(linha[11]);
                    char *dataCadastro = linha[12];
                    //atoi = converter para "string" para int
                    //atof = converter para 'string' para double


                    //Imprime cada linha
                    printf("| %d | %s | %s| %s | %s| %s | %d | %d | %d | %d | %s | %d | %s |\n",
                            id, nome, sexo, datanascimento, endereco, cidade, cep, telefone, cpf, rg, profissao, pispasep, dataCadastro);

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
        printf("1) Cadastrar um novo Funcionario\f");
        printf("2) Alterar um Funcionario\f");
        printf("3) Excluir um Funcionario\f");
        printf("4) Voltar ao menu principal\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: mostrarCadastroFuncionario();
                break;
            case 2: mostrarListagemFuncionarios();
                break;
            case 3: mostrarExclusaoFuncionario();
                break;

        }
    } while (opcao != 4);
}

/**
 * mostra tela de cadastro de Funcionarios
 * Autor:
 * Data: 26/08/2017
 */
void mostrarCadastroFuncionario() {
    Funcionarios f;

    limparTela();
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");
    printf("|                                             CADASTRO DE FUNCIONARIOS                         |\n");
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");

    //Obten o Nome
    printf("| NOME: ");
    fgets(f.nome, sizeof (f.nome), stdin);
    int tamanho = strlen(f.nome);
    f.nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	

    printf("| SEXO (F/M): ");
    fgets(f.sexo, sizeof (f.sexo), stdin);
    tamanho = strlen(f.sexo);
    f.sexo[tamanho - 1] = '\0';

    printf("| DATA DE NASCIOMENTO (XX/XX/XXX): ");
    fgets(f.datanasci, sizeof (f.datanasci), stdin);
    tamanho = strlen(f.datanasci);
    f.datanasci[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	

    getchar();

    printf("| ENDEREÇO: ");
    fgets(f.endereco, sizeof (f.endereco), stdin);
    tamanho = strlen(f.endereco);
    f.endereco[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	

    printf("| CIDADE: ");
    fgets(f.cidade, sizeof (f.cidade), stdin);
    tamanho = strlen(f.cidade);
    f.cidade[tamanho - 1] = '\0';

    printf("| CEP: ");
    scanf("%d", &f.cep);
    getchar();

    printf("| TELEFONE(XX)XXXXX-XXXX: ");
    scanf("%d", &f.telefone);
    getchar();

    printf("| CPF:  ");
    scanf("%d", &f.cpf);
    getchar();

    printf("| RG: ");
    scanf("%d", &f.rg);
    getchar();

    printf("| PROFISSÃO: ");
    fgets(f.profissao, sizeof (f.profissao), stdin);
    tamanho = strlen(f.profissao);
    f.profissao[tamanho - 1] = '\0';

    printf("| PIS/PASEP: ");
    scanf("%d", &f.pispasep);
    getchar();

    printf("|-------------------------------------------------------------------------------------------------------------------|\n");

    printf("Deseja realmente cadastrar esse funcionario? (S/N) ");
    char resposta = getchar();
    getchar();

    if (resposta == 'S' || resposta == 's') {
        inserirFuncionario(f);
    } else {
        mostrarListagemFuncionarios();
    }
}


/**
 * Insere um novo funcionario
 * Autor: Bruno Qualhato
 * Data: 26/08/2017
 */
//Inicializa a variável de conexão com o MySQL

void inserirFuncionario(Funcionarios f) {
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[500];

        snprintf(sql, 500, "INSERT INTO funcionarios(nome,sexo,datanascimento,endereco,cidade,cep, telefone,cpf,rg,profissao,pispasep) values('%s','%s','%s','%s','%s','%d','%d','%d','%d','%s','%d')"
                , f.nome, f.sexo, f.datanasci, f.endereco, f.cidade, f.cep, f.telefone, f.cpf, f.rg, f.profissao, f.pispasep);


        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão

            printf("Funcionario fadastrado com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

void alterarFuncionario(Funcionarios f) {
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "update funcionario set nome = '%s' where id = %d", f.nome, f.id);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão

            printf("País alterado com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

/**
 * Exclui um  Funcionario
f* Autor:  
 * Data: /08/2017
 */
void ExclusaoFuncionario(int codigo) {
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "delete from funcionario where id = %d", codigo);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão

            printf("Funcionario excluído com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }

}

Funcionarios* selecionarFuncionario(int codigo) {
    //Cria a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Efetua a conexão
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        char sql[500];
        snprintf(sql, 500, "select id, nome from funcionarios where id = %d", codigo);

        //Executa o comando de consulta
        if (mysql_query(&mysql, sql) == 0) {
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            int id;
            char *nome;
            if ((linha = mysql_fetch_row(resultado))) {
                //Obtém cada coluna na órdem
                id = atoi(linha[0]);

                //Libera os resultado e fecha a conexão
                mysql_free_result(resultado);
                mysql_close(&mysql);

                Funcionarios funcionarios;

                Funcionarios *f = &funcionarios;
                strncpy(f->nome, linha[1], 100);
                f->id = id;

                //Imprime cada linha
                return f;
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

void mostrarAlteracaoFuncionario() {
    int codigo;
    printf("Digite o código do Funcionarios que deseja alterar: ");
    scanf("%d", &codigo);
    getchar();

    Funcionarios *f = selecionarFuncionario(codigo);

    limparTela();
    printf("|--------------------------------------------------------------------|\n");
    printf("| CADASTRO DE FUNCIONARIOS                                                 |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("| Id: %d\n", f->id);
    printf("| Nome: %s\n", f->nome);
    printf("|--------------------------------------------------------------------|\n");

    printf("Digite o novo nome do Funcionario: ");
    char nome[100];
    fgets(nome, sizeof (nome), stdin);
    int tamanho = strlen(nome);
    nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->nome, nome, 100);
    printf("|--------------------------------------------------------------------|\n");

    printf("Deseja realmente salvar as alterações? (S/N) ");
    char resposta = getchar();
    getchar();

    if (resposta == 'S' || resposta == 's') {
        alterarFuncionario(*f);
    }

    getchar();
}

void mostrarExclusaoFuncionario() {
    int codigo;
    printf("Digite o código do funcionario que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    ExclusaoFuncionario(codigo);
    getchar();
}
