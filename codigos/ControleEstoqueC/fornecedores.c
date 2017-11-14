#include"fornecedores.h"

//Borda Padrão dos Menus
void BordaPadrao(){
    printf("||====================================================================||\n");
}


// Menu Principal do Cadastro de Fornecedores.
void MenuFornecedores(){
    
    int opcao;
    
    do{
                                
        limparTela();
        BordaPadrao();
        printf("||\t\t\tO QUE DESEJA FAZER?\t\t\t      ||\n");
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
            case 4: MenuExclusao(); break;
                       
        }
    } while (opcao != 5);
    
    
    }

// Sub Menu para consultar os Fornecedores
void ConsultaFornecedores(){    
    
    int opcao2;
    
    do{
        limparTela();
        BordaPadrao();
        printf("||\t\t\tCONSULTAR FORNECEDORES\t\t\t      ||\n");
        BordaPadrao(); 
        printf("\n");
        printf("1) Por Nome\n");
        printf("2) Por ID\n");
        printf("3) Para Voltar ao Menu Anterior");
        printf("\n");
        printf("\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao2); getchar();
        
        switch (opcao2){
            case 1: consultaNome(); break;
            case 2: consultaId();break;          
        }
            
    }while (opcao2 !=3);
    
    
}

// Consulta os Forncedores por ordem de Nome
void consultaNome(){
    
    limparTela();
    BordaPadrao();
    printf("||\t\tCONSULTA FORNECEDORES POR ORDEM DE NOME\t\t\t||\n");
    BordaPadrao();
    BordaPadrao();

    //Cria a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Efetua a conexão
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        
        //Executa o comando de consulta
        if (mysql_query(&mysql, "select idFornecedor, nomeFornecedor from fornecedores order by nomeFornecedor") == 0){
            
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            
            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            while ( (linha = mysql_fetch_row(resultado)) ){
                
                //Obtém cada coluna na órdem
                int id = atoi(linha[0]);
                char *nome = linha[1];

                //Imprime cada linha
                printf("|| %10d | %-53s ||\n", id, nome);
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
    
    BordaPadrao();
    printf("\n");
    printf("Pressione <ENTER> para voltar ao Menu Anterior:");
    getchar();

}

//Consulta os fornecedores por ordem de ID
void consultaId(){
    
    limparTela();
    BordaPadrao();
    printf("||\t\tCONSULTA FORNECEDORES POR ORDEM DE ID\t\t      ||\n");
    BordaPadrao();
    BordaPadrao();

    //Cria a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Efetua a conexão
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        
        //Executa o comando de consulta
        if (mysql_query(&mysql, "select idFornecedor, nomeFornecedor from fornecedores order by idFornecedor") == 0){
            
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            while ( (linha = mysql_fetch_row(resultado)) ){
                
                //Obtém cada coluna na órdem
                int id = atoi(linha[0]);
                char *nome = linha[1];

                //Imprime cada linha
                printf("|| %10d | %-53s ||\n", id, nome);
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
    
    BordaPadrao();
    printf("\n");
    printf("Pressione <ENTER> para voltar ao Menu Anterior:");
    getchar();


}

// Mostra o menu de opções de exclusão

void MenuExclusao(){
    int codigo;
    printf("Digite o código do país que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    excluirPais(codigo);
    getchar();
}

