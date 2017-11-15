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
        printf("2) Cadastrar um Fornecedor\n");
        printf("3) Alterar um Fornecedor\n");
        printf("4) Excluir um Fornecedor\n");
        printf("5) Voltar ao menu principal\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao); getchar();

        switch (opcao){
            case 1: ConsultaFornecedores(); break;
            case 2: CadastrarFornecedor(); break;
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
    printf("||\t\tCONSULTA FORNECEDORES POR ORDEM DE NOME\t\t      ||\n");
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
    
     int opcao2;
    
    do{
        limparTela();
        BordaPadrao();
        printf("||\t\t\tMENU EXCLUSÃO\t\t\t\t      ||\n");
        BordaPadrao(); 
        printf("\n");
        printf("1) Consultar Fornecedores\n");
        printf("2) Excluir Fornecedores\n");
        printf("3) Para Voltar ao Menu Anterior");
        printf("\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao2); getchar();
        
        switch (opcao2){
            case 1: ConsultaExclusao(); break;
            case 2: ExcluirFornecedor();break;          
        }
            
    }while (opcao2 !=3);
    
}
    
    
    
    void ConsultaExclusao(){
    
            limparTela();
            BordaPadrao();
            printf("||\t\tCONSULTA FORNECEDORES\t\t\t\t      ||\n");
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
    
    void ExcluirFornecedor(){
        
        int codigo;
        printf("Digite o código do Fornecedor que deseja excluir: ");
        scanf("%d", &codigo);
        getchar();

        DeletarFornecedor(codigo);
        getchar();    
      
    }
    
    void DeletarFornecedor(int codigo){
        
        //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "delete from fornecedores where idFornecedor = %d", codigo);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão

            printf("Fornecedor excluído com sucesso\n\n"); //Exibe mensagem de sucesso
            printf("Pressione a Tecla <ENTER> para continuar");
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
    
      
}
    
    
void CadastrarFornecedor() {
    Fornecedores f;

    limparTela();
    BordaPadrao();
    printf("| CADASTRO DE FORNECEDORES                                            |\n");
    BordaPadrao();

    printf("NOME FORNECEDORES: ");
    fgets(f.nomeFornecedor, sizeof(f.nomeFornecedor), stdin);
    int tamanho = strlen(f.nomeFornecedor); f.nomeFornecedor[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	
    BordaPadrao();

    printf("Deseja realmente cadastrar o fornecedor? (S/N) ");
    char resposta = getchar(); getchar();

    if (resposta == 'S' || resposta == 's'){
        inserirFornecedores(f);
    }
}

void inserirFornecedores(Fornecedores f){
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "insert into fornecedores(nomeFornecedor) values('%s')", f.nomeFornecedor);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão

            printf("Fornecedor cadastrado com sucesso\n\n"); //Exibe mensagem de sucesso
            printf("Pressione a tecla <ENTER> para continuar");
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
        
    }
    getchar();
}
    


