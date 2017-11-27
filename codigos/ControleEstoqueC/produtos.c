#include <stdlib.h>
#include <stdio.h>
#include  "produtos.h"

/**
 * Mostra os produtos cadastrados e um MENU de opções para produtos
 */
void mostraMenuProdutos() {

    int opcao;
    do {
        mostraProdutos();

        printf("\nO que deseja fazer?\n");
        printf("1) Cadastrar um novo produto\n");
        printf("2) Alterar um produto\n");
        printf("3) Excluir\n");
        printf("4) Voltar ao menu principal\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: mostrarCadastroProduto();
                break;
            case 2: mostraAlteracaoProduto();
                break;
            case 3: mostraExclusaoProduto();
                break;
        }
    } while (opcao != 4);
}

/**
 * mostra a tela de cadastro de produtos.
 */
void mostrarCadastroProduto() {
    Produto p;

    limparTela();
    mostraLinhaMenu();
    printf("|                                          \t\t\tCADASTRO DE PRODUTO\t\t                                                       |\n");
    mostraLinhaMenu();

    printf(" NOME: ");
    leString(p.nome, 100);

    printf(" FORNECEDOR: ");
    leString(p.fornecedor, 100);

    printf(" PREÇO DE COMPRA: R$ ");
    scanf("%f", &p.precoCompra);
    getchar();

    printf(" PREÇO DE VENDA: R$ ");
    scanf("%f", &p.precoVenda);
    getchar();

    printf(" DESCRIÇÃO: ");
    leString(p.descricao, 100);

    printf(" QUANTIDADE EM ESTOQUE: ");
    scanf("%d", &p.qtdEmEstoque);
    getchar();
    mostraLinhaMenu();

    printf("Deseja realmente criar o produto? (S/N) ");
    char resposta = getchar();
    getchar();

    if (resposta == 'S' || resposta == 's') {
        insereProduto(p);
    }
}

/**
 * Insere um novo produto
 */
void insereProduto(Produto p) {
    MYSQL mysql;
    mysql_init(&mysql);

    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        char sql[500];
        snprintf(sql, 500, "INSERT INTO produtos(nome,fornecedor,precoCompra,precoVenda,descricao,qtdEmEstoque) values('%s','%s',%f,%f,'%s',%d)"
                , p.nome, p.fornecedor, p.precoCompra, p.precoVenda, p.descricao, p.qtdEmEstoque);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão
            printf("Produto cadastrado com sucesso\n");
        } else {
            printf("%s\n", mysql_error(&mysql));
            getchar();
        }
    } else {
        printf("FALHA AO CONECTAR AO BANCO DE DADOS: %s \n<ENTER>", mysql_error(&mysql));
        getchar();
    }
}

/**
 * Mostra o quadro de produtos cadastrados
 */
void mostraProdutos() {
    limparTela();

    MYSQL mysql;
    mysql_init(&mysql);
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {

        //Executa o comando de consulta
        if (mysql_query(&mysql, "SELECT id, nome, fornecedor, precoCompra, precoVenda, descricao, qtdEmEstoque, dataCadastro, dataModificacao FROM produtos ORDER BY nome") == 0) {

            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;

            mostraCabecalhoMenu();
            while ((linha = mysql_fetch_row(resultado))) {

                //Obtém cada coluna na órdem
                int id = atoi(linha[0]), qtdEmEstoque = atoi(linha[6]), i, j;
                char *nome = linha[1], *fornecedor = linha[2], *descricao = linha[5], *dataCadastro = linha[7], *dataModificacao = linha[8];

                float precoCompra = atof(linha[3]), precoVenda = atof(linha[4]);

                //Imprime cada linha
                printf("| %2d | %-22s | %-16s|   R$%-10.2f|   R$%-10.2f| %-25s|     %-5d  | %-7s | %-7s |\n",
                        id, nome, fornecedor, precoCompra, precoVenda, descricao, qtdEmEstoque, dataCadastro, dataModificacao);
            }
            mostraLinhaMenu();

            mysql_free_result(resultado);
            mysql_close(&mysql);
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("FALHA AO CONECTAR AO BANCO DE DADOS: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
}

/**
 * Mostra um produto,pelo ID
 */
void mostraProduto(int id) { //por id
    limparTela();
    mostraCabecalhoMenu();

    MYSQL mysql;
    mysql_init(&mysql);
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Executa o comando de consulta
        char sql[500];
        snprintf(sql, 500, "SELECT * FROM produtos WHERE id=%d", id);
        if (mysql_query(&mysql, sql) == 0) {

            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            while ((linha = mysql_fetch_row(resultado))) {

                //Obtém cada coluna na ordem
                int id = atoi(linha[0]), qtdEmEstoque = atoi(linha[6]), i, j;
                char *nome = linha[1], *fornecedor = linha[2], *descricao = linha[5], *dataCadastro = linha[7], *dataModificacao = linha[8];
                float precoCompra = atof(linha[3]), precoVenda = atof(linha[4]);

                //Imprime cada linha
                printf("| %2d | %-22s | %-16s|   R$%-10.2f|   R$%-10.2f| %-25s|     %-5d  | %-7s | %-7s |\n",
                        id, nome, fornecedor, precoCompra, precoVenda, descricao, qtdEmEstoque, dataCadastro, dataModificacao);
            }
            mostraLinhaMenu();

            //Libera os resultado e fecha a conexão
            mysql_free_result(resultado);
            mysql_close(&mysql);
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
            getchar();
        }
    } else {
        printf("FALHA AO CONECTAR AO BANCO DE DADOS: %s <ENTER> \n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
        getchar();
    }
}

/**
 * Altera um produto, recebe id, campo, novo conteúdo do campo e o tipo
 */
void alteraProduto(int id, char campo[], char string[], char tipoDoCampo) {
    Produto p;
    MYSQL mysql;
    mysql_init(&mysql);
    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {

        //Cria o comando SQL para envio
        char sql[500];

        if (tipoDoCampo == 's')snprintf(sql, 500, "UPDATE produtos SET %s = '%s', dataModificacao = NOW() WHERE id=%d", campo, string, id);
        else snprintf(sql, 500, "UPDATE produtos SET %s = %s, dataModificacao = NOW() WHERE id=%d", campo, string, id);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão
            printf("\n[Produto alterado com sucesso!]");
            printf("\nPRESSIONE <ENTER>\n");
            getchar();
        } else {
            printf("%s\n", mysql_error(&mysql));
            getchar();
        }
    } else {
        printf("Falha na conexão: %s\n", mysql_error(&mysql));
        getchar();
    }


}

/**
 * Seleciona e altera campos de um produto.
 */
void mostraAlteracaoProduto() {
    int opcao, id = 0;
    mostraProdutos();

    printf("\nDigite o [ID] do produto : ");
    scanf("%d", &id);
    do {

        while (!checaSeExiste(id, "produtos")) {//obriga o usuário a digitar um id válido
            limparTela();
            mostraProdutos();
            printf("\n [PRODUTO INEXISTENTE]\nDigite o [ID] Novamente! : ");
            getchar();
            scanf("%d", &id);
        }

        mostraProduto(id);
        printf("\nQUAL CAMPO DESEJA ALTERAR?\n "
                "\n[1] NOME"
                "\n[2] FORNECEDOR"
                "\n[3] PREÇO DE COMPRA"
                "\n[4] PREÇO DE VENDA"
                "\n[5] DESCRIÇÃO"
                "\n[6] QTD EM ESTOQUE"
                "\n[0] [VOLTAR] ");
        scanf("%d", &opcao);

        switch (opcao) {
                char novo[100];
            case 1:
                printf("\nDigite o novo [NOME] do produto: ");
                getchar();
                leString(novo, 100);
                alteraProduto(id, "nome", novo, 's');
                break;

            case 2:
                printf("\nDigite o novo [FORNECEDOR] do produto: ");
                getchar();
                leString(novo, 100);
                alteraProduto(id, "fornecedor", novo, 's');
                break;

            case 3:
                printf("\nDigite o novo [PREÇO DE COMPRA] do produto: ");
                getchar();
                leString(novo, 100);
                alteraProduto(id, "precoCompra", novo, 'f');
                break;

            case 4:
                printf("\nDigite o novo [PREÇO DE VENDA] do produto: ");
                getchar();
                leString(novo, 100);
                alteraProduto(id, "precoVenda", novo, 'f');
                break;

            case 5:
                printf("\nDigite a nova [DESCRIÇÃO] do produto: ");
                getchar();
                leString(novo, 100);
                alteraProduto(id, "descricao", novo, 's');
                break;

            case 6:
                printf("\nDigite a nova [QUANTIDADE EM ESTOQUE] do produto: ");
                getchar();
                leString(novo, 100);
                ;
                alteraProduto(id, "qtdEmEstoque", novo, 'd');
                break;

            default: break;
        }
    } while (opcao != 0);
}

//retorna a quantidade de produtos com esse id.
int checaSeExiste(int id, char *tabela) {

    MYSQL mysql;
    mysql_init(&mysql);

    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        char sql[500];
        snprintf(sql, 500, "SELECT count(*) id FROM %s WHERE id=%d", tabela, id);

        if (mysql_query(&mysql, sql) == 0) {
            MYSQL_RES *resultado = mysql_store_result(&mysql);
            MYSQL_ROW linha;
            linha = mysql_fetch_row(resultado);
            id = atoi(linha[0]); //agora id recebe a quantidade de produtos 
            mysql_close(&mysql); //Encerra a conexão
        } else {
            printf("%s\n", mysql_error(&mysql));
        }
    } else {
        printf("Falha na conexão: %s\n", mysql_error(&mysql));
    }

    return id;
}

/**
 * inicia processo de exclusão
 */
void mostraExclusaoProduto() {//mostra opção de exclusão
    mostraProdutos();

    Produto p;
    printf("DIGITE O ID DESEJADO: ");
    scanf("%d", &p.id);
    while (!checaSeExiste(p.id, "produtos")) {//obriga o usuário a digitar um id válido
        limparTela();
        mostraProdutos();
        getchar();
        printf("\n [PRODUTO INEXISTENTE]\nDigite o [ID] Novamente! : ");
        scanf("%d", &p.id);
    }

    mostraProduto(p.id);
    char opcao;
    printf("\nDESEJA REALMENTE EXCLUIR O PRODUTO? <s/n>");
    getchar();
    scanf("%c", &opcao);

    if (opcao == 's' || opcao == 'S') {
        excluiProduto(p.id);
    }
}

//Deleta um produto pelo ID
void excluiProduto(int id) {

    MYSQL mysql;
    mysql_init(&mysql);

    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        char sql[500];
        snprintf(sql, 500, "DELETE FROM produtos WHERE id=%d", id);

        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão
            limparTela();
            printf("\nPRODUTO EXCLUÍDO COM SUCESSO!\n    [ENTER]");
            getchar();
            getchar();
        } else {
            printf("%s\n", mysql_error(&mysql));
        }
    } else {
        printf("Falha na conexão: %s\n", mysql_error(&mysql));
    }
}


//layout

void mostraCabecalhoMenu() {
    limparTela();
    mostraLinhaMenu();
    printf("|                                                                 PRODUTOS                                                                                          |\n");
    mostraLinhaMenu();
    printf("| ID |         NOME           |    FORNECEDOR   | PREÇO/COMPRA  |  PREÇO/VENDA  |          DESCRIÇÃO       | EM ESTOQUE |    DATA DE CADASTRO | DATA DE MODIFICAÇÃO |\n");
    mostraLinhaMenu();
}

void mostraLinhaMenu() {
    printf("|-------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
}