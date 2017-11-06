/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "funcionarios.h"
#include <stdio.h>
#include <stdlib.h>

void mostrarListagemFuncionarios() {
    int opcao;

    do {
        limparTela();
        printf("|------------------------------------------------------------------------------------------------------------|\n");
        printf("|                                          LISTAGEM DE FUNCIONARIOS                                          |\n");
        printf("|------------------------------------------------------------------------------------------------------------|\n");
        printf("|  ID  |  NOME  | SEXO | DATA DE NASCIMENTO | ENDEREÇO |CIDADE| CEP |TELEFONE| CPF |RG |PROFISSAO| PIS/PASEP |\n");
        printf("|------------------------------------------------------------------------------------------------------------|\n");
        MYSQL mysql;
        mysql_init(&mysql);

        if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
            //Executa o comando de consulta
            if (mysql_query(&mysql, "SELECT  idFuncionario, NomeFuncionario, SexoFuncionario, DataNascimentoFuncionario,EnderecoFuncionario, cidadeFuncionario, cepFuncionario,telefoneFuncionario, cpfFuncionario,rgFuncionario,profissaoFuncionario, pisPasepFuncionario from funcionarios") == 0) {
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

                    //atoi = converter para "string" para int
                    //atof = converter para 'string' para double


                    //Imprime cada linha
                    printf("|  %d  | %s |  %s  |    %-8s      |  %s  |  %s |%d | %d  | %d  | %d| %s |     %d     |\n",
                            id, nome, sexo, datanascimento, endereco, cidade, cep, telefone, cpf, rg, profissao, pispasep);

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

        printf("|------------------------------------------------------------------------------------------------------------|\n");
        printf("\nO que deseja fazer?\n");
        printf("1) Cadastrar um novo Funcionario\n");
        printf("2) Alterar um Funcionario\n");
        printf("3) Excluir um Funcionario\n");
        printf("4) Voltar ao menu principal\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: mostrarCadastroFuncionario();
                break;
            case 2: mostrarAlteracaoFuncionario();
                break;
            case 3: mostrarExclusaoFuncionario();
                break;

        }
    } while (opcao != 4);
}

void mostrarCadastroFuncionario() {
    Funcionarios f;

    limparTela();
    printf("|---------------------------------------------------------------|\n");
    printf("|              CADASTRO DE FUNCIONARIOS                         |\n");
    printf("|---------------------------------------------------------------|\n");


    printf("| NOME: ");
    fgets(f.nome, sizeof (f.nome), stdin);
    int tamanho = strlen(f.nome);
    f.nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	


    printf("| SEXO (F/M): ");
    fgets(f.sexo, sizeof (f.sexo), stdin);
    tamanho = strlen(f.sexo);
    f.sexo[tamanho - 1] = '\0';

    printf("| DATA DE NASCIOMENTO (XX/XX/XXX): ");
    fgets(f.datanascimento, sizeof (f.datanascimento), stdin);
    tamanho = strlen(f.datanascimento);
    f.datanascimento[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	

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


    printf("|--------------------------------------------------------------|\n");

    printf("Deseja realmente cadastrar esse funcionario? (S/N) ");
    char resposta = getchar();
    getchar();


    if (resposta == 'S' || resposta == 's') {
        inserirFuncionario(f);
    } else {
        mostrarListagemFuncionarios();
    }
}

void inserirFuncionario(Funcionarios f) {
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[2000];


        snprintf(sql, 2000, "INSERT INTO funcionarios(NomeFuncionario, SexoFuncionario, DataNascimentoFuncionario,EnderecoFuncionario, cidadeFuncionario, cepFuncionario,telefoneFuncionario, cpfFuncionario, rgFuncionario, profissaoFuncionario, pisPasepFuncionario) values('%s','%s','%s','%s','%s','%d','%d','%d','%d','%s','%d')"
                , f.nome, f.sexo, f.datanascimento, f.endereco, f.cidade, f.cep, f.telefone, f.cpf, f.rg, f.profissao, f.pispasep);


        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão

            printf("Funcionario cadastrado com sucesso\n"); //Exibe mensagem de sucesso
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
        snprintf(sql, 500, "update funcionarios set pisPasepFuncionario = '%d',profissaoFuncionario = '%s',rgFuncionario = '%d',cpfFuncionario = '%d',telefoneFuncionario = '%d',cepFuncionario = '%d',cidadeFuncionario = '%s',EnderecoFuncionario = '%s',DataNascimentoFuncionario = '%s', SexoFuncionario = '%s', NomeFuncionario = '%s' where idFuncionario = %d",
                f.pispasep, f.profissao, f.rg, f.cpf, f.telefone, f.cep, f.cidade, f.endereco, f.datanascimento, f.sexo, f.nome, f.id);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão

            printf("funcionario alterado com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

void ExclusaoFuncionario(int codigo) {
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "delete from funcionarios where idFuncionario = %d", codigo);

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
        snprintf(sql, 500, "select idFuncionario, NomeFuncionario,SexoFuncionario,DataNascimentoFuncionario,EnderecoFuncionario,cidadeFuncionario,cepFuncionario,telefoneFuncionario,cpfFuncionario,rgFuncionario,profissaoFuncionario,pisPasepFuncionario from funcionarios where idFuncionario = %d", codigo);



        //Executa o comando de consulta
        if (mysql_query(&mysql, sql) == 0) {
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            int id;
            int cep;
            int telefone;
            int cpf;
            int rg;
            int pispasep;
            if ((linha = mysql_fetch_row(resultado))) {
                //Obtém cada coluna na órdem
                id = atoi(linha[0]);
                cep = atoi(linha[6]);
                telefone = atoi(linha[7]);
                cpf = atoi(linha[8]);
                rg = atoi(linha[9]);
                pispasep = atoi(linha[11]);



                //Libera os resultado e fecha a conexão
                mysql_free_result(resultado);
                mysql_close(&mysql);

                Funcionarios funcionarios;

                Funcionarios *f = &funcionarios;
                strncpy(f->nome, linha[1], 100);
                strncpy(f->sexo, linha[2], 100);
                strncpy(f->datanascimento, linha[3], 100);
                strncpy(f->endereco, linha[4], 100);
                strncpy(f->cidade, linha[5], 100);
                strncpy(f->profissao, linha[10], 100);
                f->id = id;
                f->cep = cep;
                f->telefone = telefone;
                f->cpf = cpf;
                f->rg = rg;
                f->pispasep = pispasep;


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
    int opcao;
    printf("Digite o código do Funcionarios que deseja alterar: ");
    scanf("%d", &codigo);
    getchar();

    Funcionarios *f = selecionarFuncionario(codigo);

    limparTela();

    printf("|--------------------------------------------------------------------|\n");
    printf("|                    EDIÇÃO DE FUNCIONARIOS                          |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("| Id: %d\n", f->id);
    printf("| Nome: %s\n", f->nome);
    printf("| Sexo: %s\n", f->sexo);
    printf("| Data de Nascimento:  %s\n", f->datanascimento);
    printf("| Endereço:  %s\n", f->endereco);
    printf("| Cidade :  %s\n", f->cidade);
    printf("| Cep:  %d\n", f->cep);
    printf("| Telefone:  %d\n", f->telefone);
    printf("| Cpf:  %d\n", f->cpf);
    printf("| rg:  %d\n", f->rg);
    printf("| Profissão:  %s\n", f->profissao);
    printf("| PisPasep:  %d\n", f->pispasep);

    limparTela();
    printf("1) Para alterar o nome do funcionario\n");
    printf("2) Para alterar o Sexo do funcionario\n");
    printf("3) Para alterar a Data de Nascimento do funcionario\n");
    printf("4) Para alterar o Endereço do funcionario\n");
    printf("5) Para alterar a Cidade do funcionario\n");
    printf("6) Para alterar o Cep do funcionario\n");
    printf("7) Para alterar o Telefone do funcionario\n");
    printf("8) Para alterar o CPF do funcionario\n");
    printf("9) Para alterar o RG do funcionario\n");
    printf("10) Para alterar a Profissão do funcionario\n");
    printf("11) Para alterar o PisPasep do funcionario\n");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("|--------------------------------------------------------------------|\n");
            printf("Digite o novo nome do Funcionario: ");
            char nome[100];
            fgets(nome, sizeof (nome), stdin);
            int tamanho = strlen(nome);
            nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
            strncpy(f->nome, nome, 100);
            printf("|--------------------------------------------------------------------|\n");
            break;

        case 2:
            printf("Digite o novo sexo do Funcionario: ");
            char sexo[100];
            fgets(sexo, sizeof (sexo), stdin);
            tamanho = strlen(sexo);
            sexo[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
            strncpy(f->sexo, sexo, 100);
            printf("|--------------------------------------------------------------------|\n");

            break;

        case 3:

            printf("Digite a nova Data de Nascimento do Funcionario: ");
            char datanascimento[100];
            fgets(datanascimento, sizeof (datanascimento), stdin);
            tamanho = strlen(datanascimento);
            datanascimento[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
            strncpy(f->datanascimento, datanascimento, 100);
            printf("|--------------------------------------------------------------------|\n");
            break;
        case 4:
            printf("Digite novo Endereço do Funcionario: ");
            char endereco[100];
            fgets(endereco, sizeof (endereco), stdin);
            tamanho = strlen(endereco);
            endereco[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
            strncpy(f->endereco, endereco, 100);
            printf("|--------------------------------------------------------------------|\n");
            break;
        case 5:
            printf("Digite a nova Cidade do Funcionario: ");
            char cidade[100];
            fgets(cidade, sizeof (cidade), stdin);
            tamanho = strlen(cidade);
            cidade[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
            strncpy(f->cidade, cidade, 100);
            printf("|--------------------------------------------------------------------|\n");
            break;
        case 6:
            printf("| Digite o novo CEP:  ");
            scanf("%d", &f->cep);
            getchar();
            printf("|--------------------------------------------------------------------|\n");

            break;
        case 7:
            printf("| Digite o novo Telefone:  ");
            scanf("%d", &f->telefone);
            getchar();
            printf("|--------------------------------------------------------------------|\n");

            break;
        case 8:
            printf("| Digite o novo CPF:  ");
            scanf("%d", &f->cpf);
            getchar();
            printf("|--------------------------------------------------------------------|\n");

            break;
        case 9:

            printf("| Digite o novo RG:  ");
            scanf("%d", &f->rg);
            getchar();
            printf("|--------------------------------------------------------------------|\n");



            break;
        case 10:


            printf("Digite a nova Profissão do Funcionario: ");
            char profissao[100];
            fgets(profissao, sizeof (profissao), stdin);
            tamanho = strlen(profissao);
            profissao[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
            strncpy(f->profissao, profissao, 100);
            printf("|--------------------------------------------------------------------|\n");

            break;
        case 11:

            printf("| Digite o novo PisPasep:  ");
            scanf("%d", &f->pispasep);
            getchar();
            printf("|--------------------------------------------------------------------|\n");

            break;

    }

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
