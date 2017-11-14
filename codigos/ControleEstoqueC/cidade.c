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

