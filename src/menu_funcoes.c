#include "..\include\menu_funcoes.h"

void intro(){
    limpa_tela();
    printf("\n---------------------------------------\n");
    printf("\033[1;34mSeja Bem vindo a Farmatech\033[0m\n");
    printf("---------------------------------------\n");
}

void menu(){
    limpa_tela();
    printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Cadastrar de medicamento\n");
    printf("3 - Cadastro de receita\n");
    printf("4 - Buscar cliente\n");
    printf("5 - Buscar medicamento\n");
    printf("6 - Imprimir informacoes do cliente\n");
    printf("0 - Sair\n");
    printf("---------------------------------------\n");
}

int lerOpcao() {
    char opcao[10];

    printf("\033[1;34mDigite a opcao desejada:\033[0m\n");
    scanf("%[^\n]", opcao);

    if (opcao[1] != '\0') {
        printf("\033[1;31mOpcao invalida. Informe um numero correspondente com as opcoes do menu.\033[0m\n");
        return -1;
    }

    if (!isdigit(opcao[0])) {
        printf("\033[1;31mOpcao invalida. Informe um numero correspondente com as opcoes do menu.\033[0m\n");
        return -1;
    }

    if (opcao[0] < '0' || opcao[0] > '6') {
        printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
        return -1;
    }
    return opcao[0] - '0';
}


int validaNome(char *nome){
    int espacamento = 1;

    if (strlen(nome) == 0){
        printf("\033[1;31mO nome nao pode ser vazio.\033[0m\n");
        pressiona_enter();
        return 0; 
    }

    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            printf("\033[1;31mO nome deve conter apenas letras.\033[0m\n");
            pressiona_enter();
            return 0;
        }
        if(nome[i] == ' '){
            if(espacamento == 1){
                printf("\033[1;31mO nome nao pode comecar com espaco.\033[0m\n");
                pressiona_enter();
                return 0;
            }
            else{
                espacamento = 1; 
            }
        }
        else{
            espacamento = 0; 
        }
    }
    return 1;
}

char *formatarnome(char *nome){
    int i;
    int index = 1;

    for (i = 0; nome[i] != '\0'; i++) {
        if (isalpha(nome[i])) {
            if (index) {
                nome[i] = toupper(nome[i]);
                index = 0; 
            } else {
                nome[i] = tolower(nome[i]);
            }
        } else {
            index = 1;
        }
    }
    return nome;
}

void limpa_tela(){
    #ifdef _WIN32
        system("cls");
    #elif __APPLE__
        system("clear");
    #elif __linux__
        system("clear");
    #endif
}

void pressiona_enter(){
    printf("\nPressione ENTER para continuar.");
    while (getchar() != '\n');
    getchar();
}

void sleep(int tempo){
    #ifdef _WIN32
        Sleep(tempo);
    #elif __APPLE__
        usleep(tempo * 1000);
    #elif __linux__
        usleep(tempo * 1000);
    #endif
}