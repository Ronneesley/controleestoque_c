/** 
 * File:   fornecedores.c
 * Author: Andreia, Ana Paula, Láila e Welliton
 *
 * Created on 31 de Outubro de 2017, 12:17
 */

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
        printf("2) Cadastrar Fornecedor\n");
        printf("3) Alterar Fornecedor\n");
        printf("4) Excluir Fornecedor\n");
        printf("5) Voltar ao Menu Principal\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao); getchar();

        switch (opcao){
            case 1: ConsultarFornecedores(); break;
            case 2: CadastrarFornecedor(); break;
            case 3: MenuAlteracao(); break;
            case 4: MenuExclusao(); break;
                       
        }
    } while (opcao != 5);
    
    
  }

// Sub Menu para consultar os Fornecedores
void ConsultarFornecedores(){    
    
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
            case 1: consultarNome(); break;
            case 2: consultarId();break;          
        }
            
    }while (opcao2 !=3);
    
    
}

// Consulta os Forncedores por ordem de Nome
void consultarNome(){
    
    limparTela();
    BordaPadrao();
    printf("||\t\tCONSULTA FORNECEDORES POR ORDEM DE NOME\t\t      ||\n");
    BordaPadrao();
    printf("||CÓDIGO | RAZÃO SOCIAL              | CNPJ                  ||\n");
    BordaPadrao();

    //Cria a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Efetua a conexão
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        
        //Executa o comando de consulta
        if (mysql_query(&mysql, "select idFornecedor, nomeFornecedor, CNPJ from fornecedores order by nomeFornecedor") == 0){
            
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);
            
            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            while ( (linha = mysql_fetch_row(resultado)) ){
                
                //Obtém cada coluna na órdem
                int id = atoi(linha[0]);
                char *nome = linha[1];
                ulong cnpj = atoll(linha[2]);

                //Imprime cada linha
                printf("|| %5d | %-25s | %-14llu ||\n", id, nome, cnpj);
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
void consultarId(){
    
    limparTela();
    BordaPadrao();
    printf("||\t\tCONSULTA FORNECEDORES POR ORDEM DE ID\t\t      ||\n");
    BordaPadrao();
    printf("||CÓDIGO | RAZÃO SOCIAL              | CNPJ                  ||\n");
    BordaPadrao();

    //Cria a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Efetua a conexão
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        
        //Executa o comando de consulta
        if (mysql_query(&mysql, "select idFornecedor, nomeFornecedor, CNPJ from fornecedores order by idFornecedor") == 0){
            
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            MYSQL_ROW linha;
            while ( (linha = mysql_fetch_row(resultado)) ){
                
                //Obtém cada coluna na órdem
                int id = atoi(linha[0]);
                char *nome = linha[1];
                ulong cnpj = atoll(linha[2]);

                //Imprime cada linha
                printf("|| %5d | %-25s | %-14llu ||\n", id, nome, cnpj);
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

// Função para cadastrar os Fornecedores
void CadastrarFornecedor() {
    
    Fornecedores f;

    limparTela();
    BordaPadrao();
    printf("| CADASTRO DE FORNECEDORES                                            |\n");
    BordaPadrao();

    printf("NOME DO FORNECEDOR: ");
    fgets(f.nomeFornecedor, sizeof(f.nomeFornecedor), stdin);
    int tamanho = strlen(f.nomeFornecedor); f.nomeFornecedor[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0	
    
    printf("\n");
    printf("CNPJ DO FORNECEDOR: ");
    scanf("%llu", &f.CNPJ);
    getchar(); 
    BordaPadrao();
   
    printf("Deseja realmente cadastrar o fornecedor? (S/N) ");
    char resposta = getchar(); getchar();

    if (resposta == 'S' || resposta == 's'){
        inserirFornecedores(f);
    }
 }


// Função para inserir um  Fornecedor no Banco de Dados
void inserirFornecedores(Fornecedores f){
           
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "insert into fornecedores(nomeFornecedor, CNPJ) values('%s', '%llu')", f.nomeFornecedor, f.CNPJ);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão
            
            printf("\n");
            printf("----- Fornecedor cadastrado com sucesso -----\n\n"); //Exibe mensagem de sucesso
            printf("Pressione a tecla <ENTER> para continuar");
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 

    }
    getchar();
}


// Mostra Sub Menu da opção de Ateração
void MenuAlteracao(){
    
    int opcao2;
    
    do{
        limparTela();
        BordaPadrao();
        printf("||\t\t\tMENU ALTERAÇÃO\t\t\t\t      ||\n");
        BordaPadrao(); 
        printf("\n");
        printf("1) Consultar Fornecedores\n");
        printf("2) Alterar Fornecedor\n");
        printf("3) Para Voltar ao Menu Anterior");
        printf("\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao2); getchar();

        switch (opcao2){
            case 1: ConsultarPadrao(); break;
            case 2: MostrarAlteracaoFornecedores();break;          
        }

    }while (opcao2 !=3);
    
}

// Função para Alterar um Fornecedor
void MostrarAlteracaoFornecedores(){
    
    int codigo;
    int codigoAlterar;
    limparTela();
    BordaPadrao();
    printf("||\t\t\tALTERARAÇÃO DE FORNECEDORES\t\t      ||\n");
    BordaPadrao();
    printf("\n");
    printf("Digite o código do Fornecedor que deseja alterar: ");
    scanf("%d", &codigo); getchar();
    
    // Consulta Apenas o Código que foi selecionado do Fornecedor
    Fornecedores *f = SelecionarFornecedores(codigo);

    limparTela();
    BordaPadrao();
    printf("||\t\t\tALTERARAÇÃO DE FORNECEDORES\t\t      ||\n");
    BordaPadrao();
    printf("|| Id: %d\n", f->id);
    printf("|| Nome: %s\n", f->nomeFornecedor);
    printf("|| CNPJ: %llu\n", f->CNPJ);
    BordaPadrao();
    printf("\n");
    
    // Escolha do campo a ser  alterado no cadastro de Fornecedores
    printf("Digite: 1)Para Alterar o Nome - 2)Para Alterar o CNPJ: ");
    scanf("%d", &codigoAlterar);getchar();
    printf("\n");
    
    // Alteração do campo Nome do Cadastro de Fornecedores
    if (codigoAlterar == 1){
    printf("Digite o novo nome do fornecedor: ");
    char nome[100];
    fgets(nome, sizeof(nome), stdin);
    int tamanho = strlen(nome); nome[tamanho - 1] = '\0'; //Retira o \n do final da string e coloca \0
    strncpy(f->nomeFornecedor, nome, 100);
    BordaPadrao();

    printf("Deseja realmente salvar as alterações? (S/N) ");
    char resposta = getchar(); getchar();

        if (resposta == 'S' || resposta == 's'){
            AlterarNomeFornecedores(*f);
        }
    }
    
    // Alteração do campo CNPJ do Cadastro de Fornecedores
    if (codigoAlterar == 2){
    printf("Digite o novo CNPJ do fornecedor: ");
    scanf("%llu", &f->CNPJ);
    BordaPadrao();
    printf("Deseja realmente salvar as alterações? (S/N) ");
    char resposta = getchar(); getchar();

        if (resposta == 'S' || resposta == 's'){
            AlterarCnpjFornecedores(*f);
        }
    }

}


// Mostra as informações do fornecedor a ser alterado antes de executar a alteração
Fornecedores* SelecionarFornecedores(int codigo){
   
    //Cria a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Efetua a conexão
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        char sql[500];
        snprintf(sql, 500, "select idFornecedor, nomeFornecedor, CNPJ from fornecedores where idFornecedor = %d", codigo);

        //Executa o comando de consulta
        if (mysql_query(&mysql, sql) == 0){
            //Obtém o resultado
            MYSQL_RES *resultado = mysql_store_result(&mysql);

            //Cria uma variável para guardar a linha
            
            MYSQL_ROW linha;
            int id; 
            char *nome;
            ulong cnpj;
            
            
            if ( (linha = mysql_fetch_row(resultado)) ){
                
                //Obtém cada coluna na órdem
                id = atoi(linha[0]);
                cnpj = atoll(linha[2]);

                //Libera os resultado e fecha a conexão
                mysql_free_result(resultado);
                mysql_close(&mysql);

                Fornecedores fornecedor;
                Fornecedores *f = &fornecedor;
                strncpy(f->nomeFornecedor, linha[1], 100);
                f->CNPJ = cnpj;
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

// Função para alterar o Nome do Fornecedor no Banco de Dados.
void AlterarNomeFornecedores(Fornecedores f){
    
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "update fornecedores set nomeFornecedor = '%s' where idFornecedor = %d", f.nomeFornecedor, f.id);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão
            
            printf("\n");
            printf("----- Fornecedor alterado com sucesso -----\n\n"); //Exibe mensagem de sucesso
            printf("Pressione a tecla <ENTER> para continuar");
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
    getchar();
}

// Função para alterar o Cnpj do Fornecedor no Banco de Dados.
void AlterarCnpjFornecedores(Fornecedores f){
    
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "update fornecedores set CNPJ = %llu where idFornecedor = %d", f.CNPJ, f.id);

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql); //Encerra a conexão
            
            printf("\n");
            printf("----- Fornecedor alterado com sucesso -----\n\n"); //Exibe mensagem de sucesso
            printf("Pressione a tecla <ENTER> para continuar");
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }
    getchar();
}

// Mostra Sub Menu da opção de exclusão
void MenuExclusao(){
    
    int opcao2;
    
    do{
        limparTela();
        BordaPadrao();
        printf("||\t\t\tMENU EXCLUSÃO\t\t\t\t      ||\n");
        BordaPadrao(); 
        printf("\n");
        printf("1) Consultar Fornecedores\n");
        printf("2) Excluir Fornecedor\n");
        printf("3) Para Voltar ao Menu Anterior");
        printf("\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao2); getchar();

        switch (opcao2){
            case 1: ConsultarPadrao(); break;
            case 2: ExcluirFornecedor();break;          
        }

    }while (opcao2 !=3);
    
}
    
 // Consulta Fornecedores dentro da Função Excluir e Alterar Fornecedores    
void ConsultarPadrao(){

    limparTela();
    BordaPadrao();
    printf("||\t\tCONSULTA FORNECEDORES\t\t\t\t      ||\n");
    BordaPadrao();
    printf("||CÓDIGO | RAZÃO SOCIAL\t\t\t\t\t\t      ||\n");
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

                //Obtém cada coluna na ordem
                int id = atoi(linha[0]);
                char *nome = linha[1];

                //Imprime cada linha
                printf("|| %5d | %-58s ||\n", id, nome);
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


// Função para Excluir os Fornecedores    
void ExcluirFornecedor(){

    int codigo;
    printf("Digite o código do Fornecedor que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    DeletarFornecedor(codigo);
    getchar();    

}
 
// Função que excluir o Fornecedor do Banco de Dados
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

            printf("\n");
            printf("----- Fornecedor excluído com sucesso -----\n\n"); //Exibe mensagem de sucesso
            printf("Pressione a Tecla <ENTER> para continuar");
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }

 }