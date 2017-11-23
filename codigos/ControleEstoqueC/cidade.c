#include "cidade.h"

void mostrarListagemCidades(){
    int opcao;
    
    do {
        limparTela();

        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        printf("| LISTAGEM DE CIDADES                                                                                               |\n");
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        printf("| ID         | NOME                             | CEP                     | ID ESTADOS                              |\n");
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        
        MYSQL mysql;
        mysql_init(&mysql);
        
        if(mysql_real_connect(&mysql,SERVIDOR_BD,USUARIO_BD,SENHA_BD,NOME_BD,PORTA_BD,NULL,0)){
            if(!mysql_query(&mysql,"SELECT id, nome, cep, cidades.idEstado from cidades, estados where estados.idEstado = cidades.idEstado")){
                MYSQL_RES *resultado = mysql_store_result(&mysql);
                MYSQL_ROW linha;
                while((linha = mysql_fetch_row(resultado))){
                    
                    int id = atoi(linha[0]), idEstado = atoi(linha[3]);
                    char *nome = linha[1], *cep = linha[2];
                   
                    printf("|%-12d|%-34s|%-1s|%-0d|\n", id, nome, cep, idEstado);
                }
            }else{
                printf("erro: %s",mysql_error(&mysql));
            }
        }else{
            printf("Falha ao conectar ao banco de dados: %s",mysql_error(&mysql));
        }
        
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");

        printf("O que deseja fazer?\n");
        printf("1) Cadastrar uma nova Cidade\n");
        printf("2) Alterar uma Cidade\n");
        printf("3) Excluir uma Cidade\n");
        printf("4) Listar Estados\n");
        printf("5) Voltar ao menu principal\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1: 
                mostrarCadastroCidade();
                break;
            case 2: 
                //mostrarAlteracaoCidade();
                break;
            case 3: 
                mostrarExclusaoCidade();
                break;
            case 4:
                //mostrarListagemEstado_Cadastro();
                break;
        }
    }while (opcao != 5);
   
 }
    
void mostrarCadastroCidade() {
    cidade c;
    limparTela();
    printf("|--------------------------------------------------------------------|\n");
    printf("| CADASTRO DE CIDADES                                                |\n");
    printf("|--------------------------------------------------------------------|\n");
    
    printf("| NOME: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    int tamanho = strlen(c.nome); c.nome[tamanho - 1] = '\0'; 
    printf("|--------------------------------------------------------------------|\n");
    
   printf("| CEP: ");
    fgets(c.cep, sizeof (c.cep), stdin);
    int tamanhoCEP = strlen(c.cep);
    c.cep[tamanhoCEP] = '\0'; //Retira o \n do final da string e coloca \0
    
    printf("| ID ESTADO: ");
    scanf("%d", &c.idEstado);
    getchar();
    printf("|--------------------------------------------------------------------|\n");

    printf("Deseja realmente criar a cidade? (S/N) ");
    char resposta = getchar();
    getchar();
    
    if (resposta == 'S' || resposta == 's') {
        inserirCidade(c);
    }
}

void inserirCidade(cidade c) {
    MYSQL mysql;
    mysql_init(&mysql);
    
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        char sql[500];
        snprintf(sql, 500, "insert into cidades(nome, cep, idEstado) values('%s', '%s', %d);", c.nome, c.cep, c.idEstado);
        
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql);
            
            printf("Cidade cadastrada com sucesso\n");
        } else {
            printf("%s\n", mysql_error(&mysql));
        }
    }else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql));
    }
}


void ExclusaoCidade(int codigo) {
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "delete from cidade where idCidade = %d", codigo);
        

        //Envia o comando e analisa a resposta
        if (mysql_query(&mysql, sql) == 0) {
            mysql_close(&mysql); //Encerra a conexão

            printf("cidade excluída com sucesso\n"); //Exibe mensagem de sucesso
        } else {
            printf("%s\n", mysql_error(&mysql)); //Exibe a mensagem de erro
        }
    } else {
        printf("Falha ao conectar no banco de dados: %s\n", mysql_error(&mysql)); //Exibe a mensagem de erro ao conectar 
    }

}


void mostrarExclusaoCidade() {
    int codigo;
    printf("Digite o código da cidade que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    ExclusaoCidade(codigo);
    getchar();
}

