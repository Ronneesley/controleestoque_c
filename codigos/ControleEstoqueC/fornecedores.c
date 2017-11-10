#include"fornecedores.h"


// Menu Principal do Cadastro de Fornecedores
void MenuFornecedores(){
    
    int opcao;
    
    do{
                
        limparTela();
        printf("|--------------------------------------------------------------------|\n");
        printf("|\t\t\tO que deseja fazer?\t\t\t     |\n");
        printf("|--------------------------------------------------------------------|\n");
        printf("\n");
        printf("1) Consultar o Cadastro Fornecedores\n");
        printf("2) Cadastrar um novo país\n");
        printf("3) Alterar um país\n");
        printf("4) Excluir um país\n");
        printf("5) Voltar ao menu principal\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &opcao); getchar();

        switch (opcao){
            case 1: ConsultaFornecedores(); break;
                       
        }
    } while (opcao != 5);
    
    
    }


void ConsultaFornecedores(){
    
          
    limparTela();
    printf("|--------------------------------------------------------------------|\n");
    printf("| CADASTRO DE FORNECEDORES                                           |\n");
    printf("|--------------------------------------------------------------------|\n");
                    
    
    



}

