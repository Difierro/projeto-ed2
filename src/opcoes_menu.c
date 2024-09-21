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

Medicamento * buscar_medicamento(Medicamento * root){
    char nome[100];
    printf("Informe o nome do medicamento: ");
    scanf(" %[^\n]s", nome);
    strcpy(nome,formatarNome(nome));
    Medicamento * temp = buscaMedicamento(root, nome);
    if (temp == NULL){
        return root;
    }
    int op;
    int op2;
    do{
        menumedicamento();
        op = lerOpcao();
        if (op == -1){
            printf("---------------------------------------\n");
            continue;
        }
        switch (op){
            case 1:
                do{
                    printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
                    printf("1 - Editar nome\n");
                    printf("1 - Editar preco\n");
                    printf("1 - Editar estoque\n");
                    printf("0 - Voltar\n");
                    printf("---------------------------------------\n");
                    op2 = lerOpcao();
                    if (op2 == -1){
                        printf("---------------------------------------\n");
                        continue;
                    }
                    switch (op2){
                        case 1:
                            printf("Informe o novo nome: ");
                            scanf(" %[^\n]s", nome);
                            if (!validaNome(nome)){
                                return root;
                            }
                            strcpy(temp->info.nome,formatarNome(nome));
                            break;
                        case 2:
                            printf("Informe o novo preco: ");
                            scanf("%f", &temp->info.preco);
                            break;
                        case 3:
                            printf("Informe o novo estoque: ");
                            scanf("%d", &temp->info.estoque);
                            break;
                        case 0:
                            printf("\033[1;34mSaindo do menu de edicao.\033[0m\n");
                            break;
                        default:
                            printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
                            break;
                    }
                }while(op2 != 0);
                break;
            case 2:
                root = removerMedicamento(root, nome);
                break;
            case 0:
                printf("\033[1;34mVoltando ao menu principal.\033[0m\n");
                break;
            default:
                printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
                break;
        }
    }while(op != 0);
    return root;
}