/*#include "..\include\medicamentos.h"
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

    intro();
    do{
        menuprincipal();
        op = lerOpcao();

        if (op == -1){
            printf("---------------------------------------\n");
            continue;
        }

        switch (op){
        case 1:
            arvorecli = cadastrar_cliente(arvorecli);
            printf("\033[1;34mCliente cadastrado com sucesso!\033[0m\n");
            pressiona_enter();
            break;
        case 2:
            arvoremed = cadastrar_medicamento(arvoremed);
            printf("\033[1;34mMedicamento cadastrado com sucesso!\033[0m\n");
            pressiona_enter();
            break;
        case 3:

            break;
        case 4:

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
