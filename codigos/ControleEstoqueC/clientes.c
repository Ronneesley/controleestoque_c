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

//Funções para validação de dados
int validarSexo(char sexo){
    return sexo != 'M' && sexo != 'm' && sexo != 'F' && sexo != 'f';
}

int validarMes(int data_mes){
    return data_mes > 12 || data_mes < 1;
}

int validarDia(int data_dia){
    return data_dia < 1 || data_dia > 31;
}

void mostrarCadastroClientes() {
    //Declaracao de variaveis
    struct data {
        int data_ano;
        int data_mes;
        int data_dia;
    };
    struct data dataNascimento;

    struct dados {
        char nome[100];
        char sexo;
        char endereco[200];
        char cidade[50];
        char cep[10];
        char telefone[15];
        char cpf[14];
        char rg[10];
        char profissao[50];
    };
    struct dados cadastroCliente;

    do {
        printf("####################################\n");
        printf("#       Cadastro de clientes       #\n");
        printf("####################################\n\n");

        printf("Informe o nome completo para cadastro: ");
        scanf("%s", cadastroCliente.nome); getchar();

        if(cadastroCliente.nome != ""){

            do {
                printf("Informe o sexo [M]asculino ou [F]eminino? ");
            	scanf("%c", &cadastroCliente.sexo);

            	if (validarSexo(cadastroCliente.sexo)){
	            	printf("Informe uma letra valida correspondente ao sexo\n");
            	}
            } while (validarSexo(cadastroCliente.sexo));

            printf("Informe o ano de nascimento [aaaa]: ");
            scanf("%d", &dataNascimento.data_ano);

            do {
                printf("Informe o mes de nascimento [mm]: ");
                scanf("%d", &dataNascimento.data_mes);

                if (validarMes(dataNascimento.data_mes)){
                    printf("Informe um mes valido!\n");
                }
            } while (validarMes(dataNascimento.data_mes));

            do {
                printf("Informe o dia de nascimento [dd]: ");
                scanf("%d", &dataNascimento.data_dia);
                if (validarDia(dataNascimento.data_dia)){
                    printf("Informe um dia valido!\n");
                }
            } while (validarDia(dataNascimento.data_dia));

            printf("Informe o endereco de residencia: ");
            scanf("%s", cadastroCliente.endereco); getchar();

            printf("Informe a cidade: ");
            scanf("%s", cadastroCliente.cidade); getchar();

            printf("Informe o CEP: ");
            scanf("%s", cadastroCliente.cep); getchar();

            printf("Informe um telefone de contato [DD9XXXXXXXX]: ");
            scanf("%s", cadastroCliente.telefone); getchar();

            printf("Informe o seu CPF: ");
            scanf("%s", cadastroCliente.cpf); getchar();

            printf("Informe o seu RG: ");
            scanf("%s", cadastroCliente.rg); getchar();

            printf("Informe a sua profissao: ");
            scanf("%s", cadastroCliente.profissao); getchar();
        }
    } while (cadastroCliente.nome != "");

    system ("PAUSE");
}
