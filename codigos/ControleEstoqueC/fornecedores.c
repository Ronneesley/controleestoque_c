#include"fornecedores.h"

//Borda Padrão dos Menus
void BordaPadrao(){
    printf("|--------------------------------------------------------------------|\n");
}

//Pausar uma Funcao
void pause(){
    system("pause");
}

// Menu Principal do Cadastro de Fornecedores.
void MenuFornecedores(){
    
    int opcao;
    
    do{
                
        limparTela();
        BordaPadrao();
        printf("|\t\t\tO que deseja fazer?\t\t\t     |\n");
        BordaPadrao();
        printf("\n");
        printf("1) Consultar Fornecedores\n");
        printf("2) Cadastrar um Novo Fornecedor\n");
        printf("3) Alterar um Fornecedor\n");
        printf("4) Excluir um Fornecedor\n");
        printf("5) Voltar ao menu principal\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao); getchar();

        switch (opcao){
            case 1: ConsultaFornecedores(); break;
                       
        }
    } while (opcao != 5);
    
    
    }


void ConsultaFornecedores(){
    
    limparTela();
    BordaPadrao();
    printf("| LISTAGEM DE FORNECEDORES                                           |\n");
    BordaPadrao();
    BordaPadrao();

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

printf("Pressione qualquer tecla para voltar ao Menu Anterior:");
pause();


}

