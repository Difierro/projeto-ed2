#include <stdio.h>
#include <stdlib.h>
#include "medicamentos.c"
#include "menu_funcoes.c"
#include "clientes.c"
#include "opcoes_menu.c"
#include "entregas.c"

#define DATA_CLI ".\\data\\clientes.txt"
#define DATA_MED ".\\data\\medicamentos.txt"

int main(){
    Medicamento *hashMed[MAX_HASH] = {NULL};
    FILE *dataMed = fopen(DATA_MED, "r");
    if (dataMed == NULL){
        printf("\033[1;31mErro ao abrir arquivo de medicamentos!\033[0m\n");
        return 0;
    }
    inicializarBaseDadosMedicamentos(hashMed, dataMed);
    fclose(dataMed);

    Clientes *arvorecli = NULL;
    FILE *dataCli = fopen(DATA_CLI, "r");
    if (dataCli == NULL){
        printf("\033[1;31mErro ao abrir arquivo de clientes!\033[0m\n");
        return 0;
    }
    arvorecli = inicializarBaseDadosClientes(arvorecli, dataCli);
    fclose(dataCli);
    MinHeap heap;
    inicializarHeap(&heap);
    int nunEntregas = 0;
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
            cadastrar_medicamento(hashMed);
            break;
        case 3:
            limpa_tela();
            arvorecli = buscar_cliente(arvorecli);
            break;
        case 4:
            limpa_tela();
            buscar_medicamento(hashMed);
            break;
        case 5:
            limpa_tela();
            arvorecli = vendas(arvorecli, hashMed, &heap, nunEntregas);
            break;
        case 6:
            limpa_tela();
            entregas(&heap);
            break;
        case 0:
            printf("\033[1;34mSaindo do sistema. Volte sempre!\033[0m\n");
            break;
        default:
            printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
            break;
        }
    }while (op != 0);
    dataCli = fopen(DATA_CLI, "w");
    if(dataCli == NULL){
        printf("\033[1;31mErro ao abrir arquivo de clientes!\033[0m\n");
        return 0;
    }
    reescreverarquivoClientes(arvorecli, dataCli);
    fclose(dataCli);
    dataMed = fopen(DATA_MED, "w");
    if(dataMed == NULL){
        printf("\033[1;31mErro ao abrir arquivo de medicamentos!\033[0m\n");
        return 0;
    }
    reescreverarquivo((Medicamento **)hashMed, dataMed);
    fclose(dataMed);
    return 0;
}