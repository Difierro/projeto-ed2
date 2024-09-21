#include "..\include\opcoes_menu.h"

Clientes * cadastrar_cliente(Clientes * root){
    char nome[100], cpf[14], telefone[15];
    printf("Informe o nome do cliente: ");
    scanf(" %[^\n]s", nome);
    if (!validaNome(nome)){
        return root;
    }
    strcpy(nome,formatarNome(nome));



    printf("Informe o CPF(APENAS NUMEROS): ");
    printf("Exemplo: 12345678901\n");
    scanf(" %s", cpf);
    if (!validaCPF(cpf)){
        return root;
    }
    strcpy(cpf,formatarCPF(cpf));

    printf("Informe o telefone(APENAS NUMEROS): ");
    printf("Exemplo: 81999998888\n");
    scanf(" %s", telefone);
    if (!validaTelefone(telefone)){
        return root;
    }
    strcpy(telefone,formatarTelefone(telefone));

    return cadastroClientes(root, nome, cpf, telefone);
}

Medicamento * cadastrar_medicamento(Medicamento * root){
    char nome[100];
    float preco;
    int estoque;

    printf("Informe o nome do medicamento: ");
    scanf(" %[^\n]s", nome);

    if (!validaNome(nome)){
        return root;
    }
    strcpy(nome,formatarNome(nome));
    
    printf("Informe o preco: ");
    scanf("%f", &preco);

    printf("Informe o estoque: ");
    if ((scanf(" %d", &estoque)) != 1){
        printf("\033[1;31mPermitido apenas numeros.\033[0m\n");
        pressiona_enter();
        return root;
    }

    return cadastroMedicamento(root, nome, preco, estoque);
}

