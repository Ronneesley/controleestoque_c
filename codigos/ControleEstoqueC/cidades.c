#include "cidades.h"
/*
 *Arquivo que contém a implementação de todo o CRUD de cidades.
 * Autores: Daniel, Matheus, Patricia, Vitor
 */

/*
 * Lista todos as cidades cadastradas no banco de dados.
 */
void mostrarListagemCidades(){
    int opcao;
    
    do {
        limparTela();

        printf("|-----------------------------------------------------------------------------------------|\n");
        printf("|                                   LISTAGEM DE CIDADES                                   |\n");
        printf("|-----------------------------------------------------------------------------------------|\n");
        printf("| ID         | NOME                             | ID ESTADO    | UF                       |\n");
        printf("|-----------------------------------------------------------------------------------------|\n");
        
        MYSQL mysql;
        mysql_init(&mysql);
        
        if(mysql_real_connect(&mysql,SERVIDOR_BD,USUARIO_BD,SENHA_BD,NOME_BD,PORTA_BD,NULL,0)){
            if(!mysql_query(&mysql,"SELECT idCidade, nomeCidade, cidades.idEstado,estados.uf from cidades, estados where estados.idEstado = cidades.idEstado order by estados.uf,cidades.nomeCidade")){
                MYSQL_RES *resultado = mysql_store_result(&mysql);
                MYSQL_ROW linha;
                while((linha = mysql_fetch_row(resultado))){
                    
                    int id = atoi(linha[0]), idEstado = atoi(linha[2]);
                    char *nome = linha[1];
                    char *uf = linha[3];
                   
                    printf("|%-12d|%-34s|%-14d|%-26s|\n", id, nome, idEstado,uf);
                    printf("|-----------------------------------------------------------------------------------------|\n");
                }
            }else{
                printf("erro: %s",mysql_error(&mysql));
            }
        }else{
            printf("Falha ao conectar ao banco de dados: %s",mysql_error(&mysql));
        }
        
        

        printf("O que deseja fazer?\n");
        printf("1) Cadastrar uma nova Cidade\n");
        printf("2) Alterar uma Cidade\n");
        printf("3) Excluir uma Cidade\n");
        printf("4) Voltar ao menu principal.\n");
       

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1: 
                mostrarCadastroCidade();
                break;
            case 2: 
                mostrarAlteracaoCidade();
                break;
            case 3: 
                mostrarExclusaoCidade();
                break;
            default:
                printf("Opção invalida!\n");
        }
    }while (opcao != 4);
   
 }

/*
 *Mostra a tela de cadastro da cidade
 * 
 */
void mostrarCadastroCidade() {
    Cidade c;
    limparTela();
    printf("|--------------------------------------------------------------------|\n");
    printf("| CADASTRO DE CIDADES                                                |\n");
    printf("|--------------------------------------------------------------------|\n");
    
    printf("| NOME: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    int tamanho = strlen(c.nome); c.nome[tamanho - 1] = '\0'; 
    printf("|--------------------------------------------------------------------|\n");
    
    mostrarListaEstados(0);
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
    limparTela();
}

/*
 *Insere a cidade no banco de dados.
 */
void inserirCidade(Cidade c) {
    MYSQL mysql;
    mysql_init(&mysql);
    
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        char sql[500];
        snprintf(sql, 500, "insert into cidades(nomeCidade, idEstado) values('%s', %d);", c.nome, c.idEstado);
        
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
/*
 *
 */

void ExclusaoCidade(int codigo) {
    //Inicializa a variável de conexão com o MySQL
    MYSQL mysql;
    mysql_init(&mysql);

    //Conecta no banco de dados
    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)) {
        //Cria o comando SQL para envio
        char sql[500];
        snprintf(sql, 500, "delete from cidades where idCidade = %d", codigo);
        

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
/*
 * Lista de estados para auxiliar no cadastro de cidades
 */
void mostrarListaEstados(int segundaChamada){

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
                printf("|-------------------------------------------------------------------------------------------------------------------|\n");
            }

            mysql_free_result(resultado);
            mysql_close(&mysql);
            
           if(!segundaChamada){ 
                printf("O estado da cidade já está cadastrado?(S/N): ");
                setbuf(stdin, NULL);//Limpa o buffer do teclado.
                char resposta = getchar();getchar();
                if(resposta == 'N' || resposta == 'n'){
                    mostrarCadastroEstado();
                    mostrarListaEstados(1);
                }
            }
        } else {
            printf("%s\n", mysql_error(&mysql));
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
void alterarCidade(Cidade c){
   
    MYSQL mysql;
    mysql_init(&mysql);

    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        char sql[500];
        snprintf(sql, 500, "update cidades set nomeCidade = '%s',idEstado = %d where idCidade = %d", c.nome,c.idEstado ,c.id);
        if (mysql_query(&mysql, sql) == 0){
            mysql_close(&mysql);

            printf("Cidade alterada com sucesso\n");
        } else {
            printf("%s\n", mysql_error(&mysql));
        }
    } else {
        printf("Falha ao conectar-se com o banco de dados: %s\n", mysql_error(&mysql));
    }
    
}

Cidade* selecionarCidade(int id){

    MYSQL mysql;
    mysql_init(&mysql);

    if (mysql_real_connect(&mysql, SERVIDOR_BD, USUARIO_BD, SENHA_BD, NOME_BD, PORTA_BD, NULL, 0)){
        char sql[500];
        snprintf(sql, 500, "select idCidade, nomeCidade,idEstado from cidades where idCidade = %d", id);

        if (mysql_query(&mysql, sql) == 0){

            MYSQL_RES *resultado = mysql_store_result(&mysql);

            MYSQL_ROW linha;
            int id; 
            int idEstado;
            char *nome;
            if ( (linha = mysql_fetch_row(resultado)) ){
                id = atoi(linha[0]);
                idEstado = atoi(linha[2]);
                
                mysql_free_result(resultado);
                mysql_close(&mysql);

                Cidade *c = (Cidade*) malloc(sizeof(Cidade));
                strncpy(c->nome, linha[1], 100);
                c->idEstado = idEstado;
                c->id = id;

                return c;
            } else {

                mysql_free_result(resultado);
                mysql_close(&mysql);

                return NULL;
            }
        } else {
            printf("%s\n", mysql_error(&mysql));
        }
    } else {
        printf("Falha ao conectar-se com o banco de dados: %s\n", mysql_error(&mysql));
    }
    getchar();
}

void mostrarAlteracaoCidade(){
    int id;
    printf("Digite o ID da cidade que deseja alterar: ");
    scanf("%d", &id); getchar();

    Cidade *c = selecionarCidade(id);

    limparTela();
    printf("|--------------------------------------------------------------------|\n");
    printf("| CADASTRO DE CIDADES                                                |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("| Id: %d\n", c->id);
    printf("| Nome: %s\n", c->nome);
    printf("| id do Estado:%d\n",c->idEstado);
    printf("|--------------------------------------------------------------------|\n");
    
    printf("Digite o novo nome da cidade: ");
    char nome[100];
    
    int idEstado;
    fgets(nome, sizeof(nome), stdin);
    int tamanho = strlen(nome); nome[tamanho - 1] = '\0';
    strncpy(c->nome, nome,100);
    mostrarListaEstados(0);
    printf("Digite o id do estado:");
    scanf("%d",&c->idEstado);
    
    

    printf("|--------------------------------------------------------------------|\n");
    getchar();
    printf("Deseja realmente salvar as alterações? (S/N) ");
    char resposta = getchar(); getchar();
    if (resposta == 'S' || resposta == 's'){
        alterarCidade(*c);
    }
    free(c);
    getchar();
}

