#include "..\include\opcoes_menu.h"

Clientes *cadastrar_cliente(Clientes *root){
    char nome[100], cpf[20], telefone[20];
    printf("Informe o nome do cliente: ");
    scanf(" %[^\n]s", nome);
    limpa_buffer();
    if(!validaNome(nome)){
        return root;
    }
    strcpy(nome, formatarNome(nome));

    printf("Informe o CPF(APENAS NUMEROS): ");
    printf("Exemplo: 12345678901\n");
    scanf(" %[^\n]s", cpf);
    limpa_buffer();
    if(!validaCPF(cpf)){
        return root;
    }
    strcpy(cpf, formatarCPF(cpf));

    printf("Informe o telefone(APENAS NUMEROS): ");
    printf("Exemplo: 81999998888\n");
    scanf(" %[^\n]s", telefone);
    limpa_buffer();
    if(!validaTelefone(telefone)){
        return root;
    }
    strcpy(telefone, formatarTelefone(telefone));

    if(buscaCliente(root, cpf) != NULL){
        printf("\033[1;31mCliente ja cadastrado.\033[0m\n");
        pressiona_enter();
        return root;
    }
    printf("\033[1;32mCliente cadastrado com sucesso!\033[0m\n");
    pressiona_enter();
    return cadastroClientes(root, nome, cpf, telefone);
}

void cadastrar_medicamento(Medicamento *hashTable[]){
    char nome[100];
    float preco;
    int estoque;

    printf("Informe o nome do medicamento: ");
    scanf(" %[^\n]s", nome);
    limpa_buffer();

    if(!validaNome(nome)){
        return;
    }
    strcpy(nome, formatarNome(nome));

    printf("Informe o preco: ");
    scanf("%f", &preco);
    limpa_buffer();

    if(preco < 0){
        printf("\033[1;31mPreco nao pode ser negativo.\033[0m\n");
        pressiona_enter();
        return;
    }

    printf("Informe o estoque: ");
    if((scanf(" %d", &estoque)) != 1){
        printf("\033[1;31mPermitido apenas numeros.\033[0m\n");
        pressiona_enter();
        return;
    }
    
    if(estoque < 0){
        printf("\033[1;31mEstoque nao pode ser negativo.\033[0m\n");
        pressiona_enter();
        return;
    }
    
    if(buscaMedicamento(hashTable, nome) == 1){
        printf("\033[1;31mMedicamento ja cadastrado.\033[0m\n");
        pressiona_enter();
        return;
    }
    else{
        printf("\033[1;32mMedicamento cadastrado com sucesso!\033[0m\n");
        pressiona_enter();
        cadastroMedicamento(hashTable, nome, preco, estoque);
        return;
    }
}

Clientes *buscar_cliente(Clientes *root){
    char cpf[20];
    printf("Informe o CPF do cliente: ");
    scanf(" %[^\n]s", cpf);
    limpa_buffer();
    strcpy(cpf, formatarCPF(cpf));
    Clientes *temp = buscaCliente(root, cpf);
    if(temp == NULL){
        printf("\033[1;31mCliente nao encontrado.\033[0m\n");
        pressiona_enter();
        return root;
    }
    int op, op2;
    do{
        limpa_tela();
        printf("\033[1;32mCliente encontrado.\033[0m\n");
        printf("Nome: %s\n", temp->cliente->nome);
        printf("CPF: %s\n", temp->cliente->cpf);
        printf("Telefone: %s\n", temp->cliente->telefone);
        menucliente();
        op = lerOpcao();
        limpa_buffer();
        if(op == -1){
            printf("---------------------------------------\n");
            continue;
        }
        switch(op){
        case 1:
            do{
                limpa_tela();
                printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
                printf("1 - Editar nome\n");
                printf("2 - Editar CPF\n");
                printf("3 - Editar telefone\n");
                printf("0 - Voltar\n");
                printf("---------------------------------------\n");
                op2 = lerOpcao();
                limpa_buffer();
                if(op2 == -1){
                    printf("---------------------------------------\n");
                    continue;
                }
                switch(op2){
                case 1:
                    printf("Informe o novo nome: ");
                    scanf(" %[^\n]s", temp->cliente->nome);
                    limpa_buffer();
                    if(!validaNome(temp->cliente->nome)){
                        return root;
                    }
                    strcpy(temp->cliente->nome, formatarNome(temp->cliente->nome));
                    op2 = 0;
                    printf("\033[1;32mNome alterado com sucesso!\033[0m\n");
                    break;
                case 2:
                    printf("Informe o novo CPF: ");
                    scanf(" %[^\n]s", temp->cliente->cpf);
                    limpa_buffer();
                    if(!validaCPF(temp->cliente->cpf)){
                        return root;
                    }
                    strcpy(temp->cliente->cpf, formatarCPF(temp->cliente->cpf));
                    op2 = 0;
                    printf("\033[1;32mCPF alterado com sucesso!\033[0m\n");
                    break;
                case 3:
                    printf("Informe o novo telefone: ");
                    scanf(" %[^\n]s", temp->cliente->telefone);
                    limpa_buffer();
                    if(!validaTelefone(temp->cliente->telefone)){
                        return root;
                    }
                    strcpy(temp->cliente->telefone, formatarTelefone(temp->cliente->telefone));
                    op2 = 0;
                    printf("\033[1;32mTelefone alterado com sucesso!\033[0m\n");
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
            root = removerCliente(root, cpf);
            printf("\033[1;34mCliente removido com sucesso!\033[0m\n");
            pressiona_enter();
            op = 0;
            break;
        case 0:
            printf("\033[1;34mVoltando ao menu principal.\033[0m\n");
            sleep(1);
            break;
        default:
            printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
            sleep(1);
            break;
        }
    }while(op != 0);
    return root;
}

void buscar_medicamento(Medicamento *hashTable[]){
    char nome[100];
    printf("Informe o nome do medicamento: ");
    scanf(" %[^\n]s", nome);
    limpa_buffer();
    strcpy(nome, formatarNome(nome));
    
    if(buscaMedicamento(hashTable, nome) == 0){
        printf("\033[1;31mMedicamento nao encontrado.\033[0m\n");
        pressiona_enter();
        return;
    }
    int hash = calchash(nome);
    Medicamento *temp = hashTable[hash];
    while (temp != NULL && strcmp(temp->nome, nome) != 0){
        temp = temp->next;
    }
    int op, op2, estoque;
    float preco;
    do{
        limpa_tela();
        printf("\033[1;32mMedicamento encontrado.\033[0m\n");
        printf("Nome: %s\n", temp->nome);
        printf("Preco: %.2f\n", temp->preco);
        printf("Estoque: %d\n", temp->estoque);

        menumedicamento();
        op = lerOpcao();
        limpa_buffer();
        if(op == -1){
            printf("---------------------------------------\n");
            continue;
        }
        switch(op){
        case 1:
            do{
                printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
                printf("1 - Editar nome\n");
                printf("2 - Editar preco\n");
                printf("3 - Editar estoque\n");
                printf("0 - Voltar\n");
                printf("---------------------------------------\n");
                op2 = lerOpcao();
                limpa_buffer();
                if (op2 == -1){
                    printf("---------------------------------------\n");
                    continue;
                }
                switch(op2){
                case 1:
                    printf("Informe o novo nome: ");
                    scanf(" %[^\n]s", nome);
                    limpa_buffer();
                    if(!validaNome(nome)){
                        return;
                    }
                    strcpy(temp->nome, formatarNome(nome));
                    break;
                case 2:
                    printf("Informe o novo preco: ");
                    if((scanf("%f", &preco)) != 1){
                        printf("\033[1;31mPermitido apenas numeros.\033[0m\n");
                        pressiona_enter();
                        return;
                    }
                    temp->preco = preco;
                    limpa_buffer();
                    break;
                case 3:
                    printf("Informe o novo estoque: ");
                    if((scanf("%d", &estoque)) != 1){
                        printf("\033[1;31mPermitido apenas numeros.\033[0m\n");
                        pressiona_enter();
                        return;
                    }
                    temp->estoque = estoque;
                    break;
                case 0:
                    printf("\033[1;34mSaindo do menu de edicao.\033[0m\n");
                    sleep(1);
                    break;
                default:
                    printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
                    sleep(1);
                    break;
                }
            }while (op2 != 0);
            break;
        case 2:
            removerMedicamento(hashTable, nome);
            printf("\033[1;34mMedicamento removido com sucesso!\033[0m\n");
            pressiona_enter();
            return;
            break;
        case 0:
            printf("\033[1;34mVoltando ao menu principal.\033[0m\n");
            sleep(1);
            break;
        default:
            printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
            sleep(1);
            break;
        }
    }while (op != 0);
    return;
}

Clientes *vendas(Clientes *root, Medicamento *hashTable[], MinHeap *heap, int entregas){
    char cpf[20], nome[100];
    int quantidade, hash, op, op2;
    printf("Informe o CPF do cliente: ");
    scanf(" %[^\n]s", cpf);
    limpa_buffer();
    strcpy(cpf, formatarCPF(cpf));
    Clientes *tempCli = buscaCliente(root, cpf);
    if(tempCli == NULL){
        printf("\033[1;31mCliente nao encontrado.\033[0m\n");
        pressiona_enter();
        return root;
    }
    do{
        menuvendas();
        op = lerOpcao();
        limpa_buffer();
        if(op == -1){
            printf("---------------------------------------\n");
            continue;
        }
        switch(op){
            case 1:
                do{
                    printf("Informe o nome do medicamento: ");
                    scanf(" %[^\n]s", nome);
                    limpa_buffer();
                    strcpy(nome, formatarNome(nome));
                    if(buscaMedicamento(hashTable, nome) == 0){
                        printf("\033[1;31mMedicamento nao encontrado.\033[0m\n");
                        pressiona_enter();
                        return root;
                    }
                    hash = calchash(nome);
                    Medicamento *tempMed = hashTable[hash];
                    while(tempMed != NULL && strcmp(tempMed->nome, nome) != 0){
                        tempMed = tempMed->next;
                    }
                    printf("Informe a quantidade desejada: ");
                    if((scanf(" %d", &quantidade)) != 1){
                        printf("\033[1;31mPermitido apenas numeros.\033[0m\n");
                        pressiona_enter();
                        return root;
                    }
                    if(quantidade > tempMed->estoque){
                        printf("\033[1;31mQuantidade indisponivel em estoque.\033[0m\n");
                        pressiona_enter();
                        return root;
                    }
                    tempMed->estoque -= quantidade;
                    tempCli->cliente->carrinho = insereNoCarrinho(tempCli->cliente->carrinho, tempMed, quantidade);
                    printf("\033[1;32mVenda realizada com sucesso!\033[0m\n");
                    pressiona_enter();
                    printf("Deseja adicionar mais medicamentos ao carrinho? (1 - Sim / 0 - Nao): ");
                    if((scanf(" %d", &op2)) != 1){
                        printf("\033[1;31mPermitido apenas numeros.\033[0m\n");
                        pressiona_enter();
                        return root;
                    }
                }while(op2 != 0);
                break;
            case 2:
                printf("Informe o nome do medicamento: ");
                scanf(" %[^\n]s", nome);
                limpa_buffer();
                strcpy(nome, formatarNome(nome));
                if(buscaMedicamento(hashTable, nome) == 0){
                    printf("\033[1;31mMedicamento nao encontrado.\033[0m\n");
                    pressiona_enter();
                    return root;
                }
                hash = calchash(nome);
                Medicamento *tempMed = hashTable[hash];
                while(tempMed != NULL && strcmp(tempMed->nome, nome) != 0){
                    tempMed = tempMed->next;
                }
                tempCli->cliente->carrinho = removerCarrinho(tempCli->cliente->carrinho, tempMed);
                printf("\033[1;32mMedicamento removido do carrinho com sucesso!\033[0m\n");
                pressiona_enter();
                break;
            case 3:
                if(tempCli->cliente->carrinho == NULL){
                    printf("\033[1;31mCarrinho vazio.\033[0m\n");
                    pressiona_enter();
                    return root;
                }
                InfoEntregas tempEntrega;
                tempEntrega.codigo = entregas;
                tempEntrega.carrinho = *(tempCli->cliente->carrinho);
                insereHeap(heap, tempEntrega);
                printf("\033[1;32mFinalizando venda.\033[0m\n");
                sleep(1);
                return root;
                break;
            case 0:
                printf("\033[1;34mVoltando ao menu principal.\033[0m\n");
                sleep(1);
                break;
            default:
                printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
                sleep(1);
                break;
        }
        
    }while(op != 0);
    return root;
}

void entregas(MinHeap *heap){
    if(heap->tamanho == 0){
        printf("\033[1;31mNenhuma entrega pendente.\033[0m\n");
        pressiona_enter();
        return;
    }
    int op;
    do{
        menuentrega();
        op = lerOpcao();
        limpa_buffer();
        if(op == -1){
            printf("---------------------------------------\n");
            continue;
        }
        switch(op){
            case 1:
                printf("\033[1;32mEntrega realizada com sucesso!\033[0m\n");
                InfoEntregas temp = extraiMin(heap);
                imprimeMinHeap(temp);
                pressiona_enter();
                break;
            case 2:
                printf("\033[1;32mProxima entrega:\033[0m\n");
                imprimeMinHeap(heap->entrega[0]);
                pressiona_enter();
                break;
            case 3:
                printf("\033[1;32mTodas as entregas:\033[0m\n");
                imprimeHeap(heap);
                pressiona_enter();
                break;
            case 0:
                printf("\033[1;34mVoltando ao menu principal.\033[0m\n");
                sleep(1);
                break;
            default:
                printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
                sleep(1);
                break;
        }
    }while(op != 0);
    return;
}