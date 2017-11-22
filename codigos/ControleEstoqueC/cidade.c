#include <mysql/mysql.h>

#include "cidade.h"
void mostrarListagemCidades(){
    cidade cidade;
    MYSQL mysql;
    mysql_init(&mysql);
    if(mysql_real_connect(&mysql,SERVIDOR_BD,USUARIO_BD,SENHA_BD,NOME_BD,PORTA_BD,NULL,0)){
        if(!mysql_query(&mysql,"SELECT idCidade,nomeCidade,uf,cidades.idEstado from cidades,estados where estados.idEstado = cidades.idEstado")){
            MYSQL_RES *resultado = mysql_store_result(&mysql);
            MYSQL_ROW linha;
            while((linha = mysql_fetch_row(resultado))){
                cidade.id = atoi(linha[0]);
                strcpy(cidade.nome,linha[1]);
                strcpy(cidade.uf,linha[2]);
                cidade.idEstado = atoi(linha[3]);
                printf("|%-10d|%-100s|%-2s|\n",cidade.id,cidade.nome,cidade.uf);
            }
        }else{
            printf("erro: %s",mysql_error(&mysql));
        }
    }else{
        printf("Falha ao conectar ao banco de dados: %s",mysql_error(&mysql));
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

