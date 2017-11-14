#include <stdio.h>
#include "cidade.h"
#include "paises.h"
#include "estados.h"
#include "clientes.h"
#include "gerais.h"
#include "funcionarios.h"
#include "fornecedores.h"

/**
 * Mostra o menu principal do sistema
 * Autor: Ronneesley Moura Teles
 * Data: 15/08/2017
 */
void mostrarMenuPrincipal(){
    int opcao; //Opção a ser escolhida no menu

    do {
        limparTela();
        printf("|--------------------------------------------------------------------|\n");
        printf("| SISTEMA DE CONTROLE DE ESTOQUE                                     |\n");
        printf("|--------------------------------------------------------------------|\n");

        printf("1) Cadastro de países\n");
        printf("2) Cadastro de estados\n");
        printf("3) Cadastro de cidades\n");
        printf("4) Cadastro de clientes\n");
        printf("5) Cadastro de produtos\n");
        printf("6) Cadastro de fornecedores\n");
        printf("7) Cadastro de representantes\n");
        printf("8) Cadastro de funcionários\n");
        printf("9) Sair\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao); getchar();		

        switch (opcao){
            case 1: mostrarListagemPaises(); break;
            case 2: mostrarListagemEstados(); break;
            case 3: mostrarListagemCidades(); break;
            case 4: mostrarCadastroClientes(); break;
            case 6: MenuFornecedores(); break;
            case 8: mostrarListagemFuncionarios(); break;
            case 9: 
                printf("Até a próxima vez!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);
}

/**
 * Função principal do programa
 */
int main(){
    mostrarMenuPrincipal();

    return 0;
}
