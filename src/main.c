/*
#include "..\include\medicamentos.h"
#include "..\include\menu_funcoes.h"
#include "..\include\clientes.h"
*/
#include "medicamentos.c"
#include "menu_funcoes.c"
#include "clientes.c"
#include "opcoes_menu.c"

int main(){
    Medicamento *arvoremed = NULL;
    arvoremed = inicializarBaseDadosMedicamento(arvoremed);
    Clientes *arvorecli = NULL;
    arvorecli = inicializarBaseDadosClientes(arvorecli);
    int op;
    sleep(2);
    intro();
    do{
        menuprincipal();
        
        op = lerOpcao();
        limpa_buffer();
        if (op == -1){
            printf("---------------------------------------\n");
            continue;
        }

        switch (op){
        case 1:
            arvorecli = cadastrar_cliente(arvorecli);
            break;
        case 2:
            limpa_tela();
            arvoremed = cadastrar_medicamento(arvoremed);
            break;
        case 3:
            limpa_tela();
            arvorecli = buscar_cliente(arvorecli);
            break;
        case 4:
            limpa_tela();
            arvoremed = buscar_medicamento(arvoremed);
            break;
        case 0:
            printf("\033[1;34mSaindo do sistema. Volte sempre!\033[0m\n");

            break;
        default:
            printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
            break;
        }
    } while (op != 0);
    
    return 0;
}
