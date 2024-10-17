#ifndef MENU_FUNCOES_H
#define MENU_FUNCOES_H
#include "..\include\menu_funcoes.h"

void intro(){
    limpa_tela();
    printf("\n---------------------------------------\n");
    printf("\033[1;34mSeja Bem vindo a Farmatech\033[0m\n");
    printf("---------------------------------------\n");
}

void menuprincipal(){
    limpa_tela();
    printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Cadastrar de medicamento\n");
    printf("3 - Buscar cliente\n");
    printf("4 - Buscar medicamento\n");
    printf("5 - Vendas\n");
    printf("6 - Entregas\n");
    printf("0 - Sair\n");
    printf("---------------------------------------\n");
}

void menucliente(){
    printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
    printf("1 - Editar cliente\n");
    printf("2 - Remover cliente\n");
    printf("0 - Voltar\n");
    printf("---------------------------------------\n");
}

void menuclienteeditar(){
    limpa_tela();
    printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
    printf("1 - Editar nome\n");
    printf("2 - Editar CPF\n");
    printf("3 - Editar telefone\n");
    printf("0 - Voltar\n");
    printf("---------------------------------------\n");
}

void menumedicamento(){
    printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
    printf("1 - Editar medicamento\n");
    printf("2 - Remover medicamento\n");
    printf("0 - Voltar\n");
    printf("---------------------------------------\n");
}

void menumedicamentoeditar(){
    limpa_tela();
    printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
    printf("1 - Editar nome\n");
    printf("2 - Editar preco\n");
    printf("3 - Editar estoque\n");
    printf("0 - Voltar\n");
    printf("---------------------------------------\n");
}

void menuvendas(){
    limpa_tela();
    printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
    printf("1 - Adicionar medicamento ao carrinho\n");
    printf("2 - Remover medicamento do carrinho\n");
    printf("3 - Finalizar venda\n");
    printf("0 - Voltar\n");
    printf("---------------------------------------\n");
}

void menuentrega(){
    limpa_tela();
    printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
    printf("1 - Realizar entrega\n");
    printf("2 - Visualizar proxima entrega\n");
    printf("3 - Visualizar todas entregas\n");
    printf("0 - Voltar\n");
    printf("---------------------------------------\n");
}

int lerOpcao() {
    char opcao[10];

    printf("\033[1;34mDigite a opcao desejada:\033[0m\n");
    scanf("%[^\n]", opcao);

    if (opcao[1] != '\0') {
        printf("\033[1;31mOpcao invalida. Informe um numero correspondente com as opcoes do menu.\033[0m\n");
        sleep(1);
        return -1;
    }

    if (!isdigit(opcao[0])) {
        printf("\033[1;31mOpcao invalida. Informe um numero correspondente com as opcoes do menu.\033[0m\n");
        sleep(1);
        return -1;
    }

    if (opcao[0] <= '0' || opcao[0] >= '6') {
        printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
        sleep(1);
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

int validaCPF(char *cpf){
    if (strlen(cpf) != 11){
        printf("\033[1;31mO CPF deve conter 11 digitos.\033[0m\n");
        pressiona_enter();
        return 0;
    }

    for (int i = 0; cpf[i] != '\0'; i++) {
        if (!isdigit(cpf[i])) {
            printf("\033[1;31mO CPF deve conter apenas numeros.\033[0m\n");
            pressiona_enter();
            return 0;
        }
    }
    return 1;
}

int validaTelefone(char *telefone){
    if (strlen(telefone) != 11){
        printf("\033[1;31mO telefone deve conter 11 digitos.\033[0m\n");
        pressiona_enter();
        return 0;
    }

    for (int i = 0; telefone[i] != '\0'; i++) {
        if (!isdigit(telefone[i])) {
            printf("\033[1;31mO telefone deve conter apenas numeros.\033[0m\n");
            pressiona_enter();
            return 0;
        }
    }
    return 1;
}

char *formatarNome(char *nome){
    int i;
    int index = 1;

    for (i = 0; nome[i] != '\0'; i++) {
        if (isalpha(nome[i])) {
            if (index) {
                nome[i] = (char)toupper(nome[i]);
                index = 0; 
            } else {
                nome[i] = (char)tolower(nome[i]);
            }
        } else {
            index = 1;
        }
    }
    return nome;
}

char *formatarCPF(char *cpf){
    char cpftemp[20];
    strcpy(cpftemp, cpf);

    cpf[0] = cpftemp[0];
    cpf[1] = cpftemp[1];
    cpf[2] = cpftemp[2];
    cpf[3] = '.';
    cpf[4] = cpftemp[3];
    cpf[5] = cpftemp[4];
    cpf[6] = cpftemp[5];
    cpf[7] = '.';
    cpf[8] = cpftemp[6];
    cpf[9] = cpftemp[7];
    cpf[10] = cpftemp[8];
    cpf[11] = '-';
    cpf[12] = cpftemp[9];
    cpf[13] = cpftemp[10];
    cpf[14] = '\0';
    return cpf;
}

char *formatarTelefone(char *telefone){
    char teltemp[15];
    strcpy(teltemp, telefone);

    telefone[0] = '(';
    telefone[1] = teltemp[0];
    telefone[2] = teltemp[1];
    telefone[3] = ')';
    telefone[4] = ' ';
    telefone[5] = teltemp[2];
    telefone[6] = teltemp[3];
    telefone[7] = teltemp[4];
    telefone[8] = teltemp[5];
    telefone[9] = teltemp[6];
    telefone[10] = '-';
    telefone[11] = teltemp[7];
    telefone[12] = teltemp[8];
    telefone[13] = teltemp[9];
    telefone[14] = teltemp[10];
    telefone[15] = '\0';
    return telefone;
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

void limpa_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void sleep(int tempo){
    #ifdef _WIN32
        Sleep((unsigned int)tempo * 1000);
    #elif __APPLE__
        usleep(tempo * 1000);
    #elif __linux__
        usleep(tempo * 1000);
    #endif
}

#endif