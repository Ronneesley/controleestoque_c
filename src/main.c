/*Cadastro de clientes

 Academicos: Bruno Geovane
             Gilson Soares
             Juliana Maciel
             Leonardo Cordeiro
             Marco Aurelio
             Ruan Miller
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    //Declaracao de variaveis
    char nome[100];
    char sexo;
    int data_ano;
    int data_mes;
    int data_dia;
    char endereco[200];
    char cidade[50];
    char cep[10];
    char telefone[15];
    char cpf[14];
    char rg[10];
    char profissao[50];

    do {
        printf("####################################\n");
        printf("#       Cadastro de clientes       #\n");
        printf("####################################\n\n");

        printf("Informe o nome completo para cadastro: ");
        scanf("%s", nome); getchar();

        if(nome != " "){

            printf("Informe o sexo [M]asculino ou [F]eminino? ");
            scanf("%c", &sexo);
            if(sexo == 'M' && sexo == 'm' && sexo == 'F' && sexo == 'f'){
                scanf("%c", &sexo);
            } else {
                while (sexo != 'M' && sexo != 'm' && sexo != 'F' && sexo != 'f') {
                    printf("Informe uma letra valida correspondente ao sexo\n");
                    printf("Qual o sexo [M]asculino ou [F]eminino? ");
                    scanf("%c", &sexo);
                }
            }

            printf("Informe o ano de nascimento [aaaa]: ");
            scanf("%d", &data_ano);

            printf("Informe o mes de nascimento [mm]: ");
            scanf("%d", &data_mes);
            if (data_mes <= 12 && data_mes >= 1){
                scanf("%d", &data_mes);
            } else {
                while (data_mes > 12 || data_mes < 1){
                    printf("Informe um mes valido!\n");
                    printf("Informe o mes de nascimento [mm]: ");
                    scanf("%d", &data_mes);
                }
            }

            printf("Informe o dia de nascimento [dd]: ");
            scanf("%d", &data_dia);
            if (data_dia >= 1 && data_dia <= 31){
                scanf("%d", &data_dia);
            } else {
                while (data_dia < 1 || data_dia > 31){
                    printf("Informe um dia valido!\n");
                    printf("Informe o dia de nascimento [dd]: ");
                    scanf("%d", &data_dia);
                }
            }

            printf("Informe o endereco de residencia: ");
            scanf("%s", endereco); getchar();

            printf("Informe a cidade: ");
            scanf("%s", cidade); getchar();

            printf("Informe o CEP: ");
            scanf("%s", cep); getchar();

            printf("Informe um telefone de contato [DD9XXXXXXXX]: ");
            scanf("%s", telefone); getchar();

            printf("Informe o seu CPF: ");
            scanf("%s", cpf); getchar();

            printf("Informe o seu RG: ");
            scanf("%s", rg); getchar();

            printf("Informe a sua profissao: ");
            scanf("%s", profissao); getchar();
        }
    } while (nome != " ");

    system ("PAUSE");
    return 0;
}

