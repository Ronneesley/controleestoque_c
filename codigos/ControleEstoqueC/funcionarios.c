
#include "funcionarios.h"

void mostrarListagemFuncionarios() {
    int opcao;

    do {
        limparTela();
        printf("|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        printf("|                                                             LISTAGEM DE FUNCIONARIOS                                                                    |\n");
        printf("|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        printf("|  ID  |NOME            | SEXO |DATA DE NASCIMENTO |ENDEREÇO   |CIDADE |CEP      | TELEFONE       | CPF         |RG         | PROFISSAO      | PIS/PASEP  |\n");
        printf("|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        MYSQL mysql;
        mysql_init(&mysql);

        if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
            //Executa o comando de consulta

            if (mysql_query(&mysql, "SELECT  id, nome, sexo, dataNascimento, endereco, cidade, cep,telefone, cpf,rg,profissao, pisPasep from funcionarios") == 0) {

                //Obtém o resultado
                MYSQL_RES *resultado = mysql_store_result(&mysql);

                //Cria uma variável para guardar a linha
                MYSQL_ROW linha;
                while ((linha = mysql_fetch_row(resultado))) {
                    //Obtém cada coluna na órdem
                    int  id = atoi(linha[0]);
                    char *nome = linha[1];
                    char *sexo = linha[2];
                    char *datanascimento = linha[3];
                    char *endereco = linha[4];
                    char *cidade = linha[5];
                    char *cep = linha[6];
                    char *telefone = linha[7];
                    char *cpf = linha[8];
                    char *rg = linha[9];
                    char *profissao = linha[10];
                    char *pispasep = linha[11];

                    //atoi = converter para "string" para int
                    //atof = converter para 'string' para double

                    //Imprime cada linha

                    printf("|  %d   | %-10s |%-4s  |%-19s|%-10s|%-7s|%-8s | %-13s  | %-10s  | %-10s| %-14s |%-12s|\n",
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

        printf("|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        printf("|O que deseja fazer?\n");
        printf("|1) Cadastrar um novo Funcionario\n");
        printf("|2) Alterar um Funcionario\n");
        printf("|3) Excluir um Funcionario\n");
        printf("|4) Voltar ao menu principal\n\n");
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


    printf("| INFORME O NOME DO FUNCIONARIO: ");
    fgets(f.nome, sizeof (f.nome), stdin);
    int tamanho = strlen(f.nome);
    f.nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	


    printf("| INFORME O SEXO (F/M): ");
    fgets(f.sexo, sizeof (f.sexo), stdin);
    tamanho = strlen(f.sexo);
    f.sexo[tamanho - 1] = '\0';


    printf("| INFORME A  DATA DE NASCIMENTO (XX/XX/XXXX): ");
    fgets(f.datanascimento, sizeof (f.datanascimento), stdin);
    tamanho = strlen(f.datanascimento);
    f.datanascimento[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	


    printf("| INFORME O ENDEREÇO: ");
    fgets(f.endereco, sizeof (f.endereco), stdin);
    tamanho = strlen(f.endereco);
    f.endereco[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	


    printf("| INFORME A CIDADE: ");
    fgets(f.cidade, sizeof (f.cidade), stdin);
    tamanho = strlen(f.cidade);
    f.cidade[tamanho - 1] = '\0';


    printf("| INFORME O CEP XXXXX-XXX: ");
    fgets(f.cep, sizeof (f.cep), stdin);
    tamanho = strlen(f.cep);
    f.cep[tamanho - 1] = '\0';


    printf("| INFORME O TELEFONE (XX) XXXXX-XXXX: ");
    fgets(f.telefone, sizeof (f.telefone), stdin);
    tamanho = strlen(f.telefone);
    f.telefone[tamanho - 1] = '\0';


    printf("| INFORME O CPF : ");
    fgets(f.cpf, sizeof (f.cpf), stdin);
    tamanho = strlen(f.cpf);
    f.cpf[tamanho - 1] = '\0';


    printf("| INFORME O RG XXXXXXX: ");
    fgets(f.rg, sizeof (f.rg), stdin);
    tamanho = strlen(f.rg);
    f.rg[tamanho - 1] = '\0';



    printf("| INFORME A PROFISSÃO: ");
    fgets(f.profissao, sizeof (f.profissao), stdin);
    tamanho = strlen(f.profissao);
    f.profissao[tamanho - 1] = '\0';


    printf("| INFORME O PIS/PASEP: ");
    fgets(f.pispasep, sizeof (f.pispasep), stdin);
    tamanho = strlen(f.pispasep);
    f.pispasep[tamanho - 1] = '\0';
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

        snprintf(sql, 2000, "INSERT INTO funcionarios(nome, sexo, dataNascimento,endereco, cidade, cep,telefone, cpf, rg, profissao, pisPasep)"
                " values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"
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
        char sql[2000];
        snprintf(sql, 2000, "update funcionarios set pisPasep = '%s',profissao = '%s',rg = '%s',cpf = '%s',telefone = '%s',cep = '%s',cidade = '%s',endereco = '%s',dataNascimento = '%s', sexo = '%s', nome = '%s' where id = %d",
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
        snprintf(sql, 500, "delete from funcionarios where id = %d", codigo);

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
        char sql[2000];
        snprintf(sql, 2000, "select id, nome, sexo, dataNascimento, endereco, cidade, cep, telefone, cpf, rg, profissao, pisPasep from funcionarios where id = %d", codigo);

        //Executa o comando de consulta
        if (mysql_query(&mysql, sql) == 0) {
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);
            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;

            int id;

            if ((linha = mysql_fetch_row(resultado))) {
                //Obtém cada coluna na órdem
                id = atoi(linha[0]);

                //Libera os resultado e fecha a conexão
                mysql_free_result(resultado);
                mysql_close(&mysql);

                Funcionarios funcionarios;
                Funcionarios *f = &funcionarios;

                strncpy(f->sexo, linha[2], 100);
                strncpy(f->datanascimento, linha[3], 100);
                strncpy(f->endereco, linha[4], 100);
                strncpy(f->cidade, linha[5], 100);
                strncpy(f->cep, linha[6], 100);
                strncpy(f->telefone, linha[7], 100);
                strncpy(f->cpf, linha[8], 100);
                strncpy(f->rg, linha[9], 100);
                strncpy(f->profissao, linha[10], 100);
                strncpy(f->nome, linha[1], 100);
                strncpy(f->pispasep, linha[11], 100);
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
    printf("|                    EDIÇÃO DE FUNCIONARIOS                          |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("| Id: %d\n", f->id);
    printf("| Nome: %s\n", f->nome);
    printf("| Sexo: %s\n", f->sexo);
    printf("| Data de Nascimento:  %s\n", f->datanascimento);
    printf("| Endereço:  %s\n", f->endereco);
    printf("| Cidade :  %s\n", f->cidade);
    printf("| Cep:  %s\n", f->cep);
    printf("| Telefone:  %s\n", f->telefone);
    printf("| Cpf:  %s\n", f->cpf);
    printf("| rg:  %s\n", f->rg);
    printf("| Profissão:  %s\n", f->profissao);
    printf("| PisPasep:  %s\n", f->pispasep);
    printf("|-------------------------------------------------------------------|\n");


    printf("|--------------------------------------------------------------------|\n");
    printf("| Digite o novo nome do Funcionario: ");
    char nome[100];
    fgets(nome, sizeof (nome), stdin);
    int tamanho = strlen(nome);
    nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->nome, nome, 100);
    printf("|--------------------------------------------------------------------|\n");


    printf("| Digite o novo sexo do Funcionario: ");
    char sexo[100];
    fgets(sexo, sizeof (sexo), stdin);
    tamanho = strlen(sexo);
    sexo[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->sexo, sexo, 100);
    printf("|--------------------------------------------------------------------|\n");


    printf("| Digite a nova Data de Nascimento do Funcionario: ");
    char datanascimento[100];
    fgets(datanascimento, sizeof (datanascimento), stdin);
    tamanho = strlen(datanascimento);
    datanascimento[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->datanascimento, datanascimento, 100);
    printf("|--------------------------------------------------------------------|\n");


    printf("| Digite novo Endereço do Funcionario: ");
    char endereco[100];
    fgets(endereco, sizeof (endereco), stdin);
    tamanho = strlen(endereco);
    endereco[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->endereco, endereco, 100);
    printf("|--------------------------------------------------------------------|\n");


    printf("| Digite a nova Cidade do Funcionario: ");
    char cidade[100];
    fgets(cidade, sizeof (cidade), stdin);
    tamanho = strlen(cidade);
    cidade[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->cidade, cidade, 100);
    printf("|--------------------------------------------------------------------|\n");


    printf("| Digite o novo CEP: ");
    char cep[100];
    fgets(cep, sizeof (cep), stdin);
    tamanho = strlen(cep);
    cep[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->cep, cep, 100);
    printf("|--------------------------------------------------------------------|\n");



    printf("| Digite o novo Telefone:  ");
    char telefone[100];
    fgets(telefone, sizeof (telefone), stdin);
    tamanho = strlen(telefone);
    telefone[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->telefone, telefone, 100);
    printf("|--------------------------------------------------------------------|\n");


    printf("| Digite o novo CPF:  ");
    char cpf[100];
    fgets(cpf, sizeof (cpf), stdin);
    tamanho = strlen(cpf);
    cpf[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->cpf, cpf, 100);
    printf("|--------------------------------------------------------------------|\n");


    printf("| INFORME O RG XXXXXXX: ");
    char rg[100];
    fgets(rg, sizeof (rg), stdin);
    tamanho = strlen(rg);
    rg[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->rg, cidade, 100);
    printf("|--------------------------------------------------------------------|\n");



    printf("| Digite a nova Profissão do Funcionario: ");
    char profissao[100];
    fgets(profissao, sizeof (profissao), stdin);
    tamanho = strlen(profissao);
    profissao[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->profissao, profissao, 100);
    printf("|--------------------------------------------------------------------|\n");


    printf("| Digite o novo PIS/PASEP:  ");
    char pis[100];
    fgets(pis, sizeof (pis), stdin);
    tamanho = strlen(pis);
    cpf[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->cpf, pis, 100);
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
