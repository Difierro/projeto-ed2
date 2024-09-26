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

Medicamento *cadastrar_medicamento(Medicamento *root){
    char nome[100];
    float preco;
    int estoque;

    printf("Informe o nome do medicamento: ");
    scanf(" %[^\n]s", nome);
    limpa_buffer();

    if(!validaNome(nome)){
        return root;
    }
    strcpy(nome, formatarNome(nome));

    printf("Informe o preco: ");
    scanf("%f", &preco);
    limpa_buffer();

    printf("Informe o estoque: ");
    if((scanf(" %d", &estoque)) != 1){
        printf("\033[1;31mPermitido apenas numeros.\033[0m\n");
        pressiona_enter();
        return root;
    }
    
    if(estoque < 0){
        printf("\033[1;31mEstoque nao pode ser negativo.\033[0m\n");
        pressiona_enter();
        return root;
    }
    if(preco < 0){
        printf("\033[1;31mPreco nao pode ser negativo.\033[0m\n");
        pressiona_enter();
        return root;
    }
    if(buscaMedicamento(root, nome) != NULL){
        printf("\033[1;31mMedicamento ja cadastrado.\033[0m\n");
        pressiona_enter();
        return root;
    }
    else{
        printf("\033[1;32mMedicamento cadastrado com sucesso!\033[0m\n");
        pressiona_enter();
        return cadastroMedicamento(root, nome, preco, estoque);
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
    int op;
    int op2;
    do{
        limpa_tela();
        printf("\033[1;32mCliente encontrado.\033[0m\n");
        printf("Nome: %s\n", temp->cliente->nome);
        printf("CPF: %s\n", temp->cliente->cpf);
        printf("Telefone: %s\n", temp->cliente->telefone);
        menucliente();
        op = lerOpcao();
        limpa_buffer();
        if (op == -1)
        {
            printf("---------------------------------------\n");
            continue;
        }
        switch (op)
        {
        case 1:
            do
            {
                limpa_tela();
                printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
                printf("1 - Editar nome\n");
                printf("2 - Editar CPF\n");
                printf("3 - Editar telefone\n");
                printf("0 - Voltar\n");
                printf("---------------------------------------\n");
                op2 = lerOpcao();
                limpa_buffer();
                if (op2 == -1)
                {
                    printf("---------------------------------------\n");
                    continue;
                }
                switch (op2)
                {
                case 1:
                    printf("Informe o novo nome: ");
                    scanf(" %[^\n]s", temp->cliente->nome);
                    limpa_buffer();
                    if (!validaNome(temp->cliente->nome))
                    {
                        return root;
                    }
                    strcpy(temp->cliente->nome, formatarNome(temp->cliente->nome));
                    op2 = 0;
                    break;
                case 2:
                    printf("Informe o novo CPF: ");
                    scanf(" %[^\n]s", temp->cliente->cpf);
                    limpa_buffer();
                    if (!validaCPF(temp->cliente->cpf))
                    {
                        return root;
                    }
                    strcpy(temp->cliente->cpf, formatarCPF(temp->cliente->cpf));
                    op2 = 0;
                    break;
                case 3:
                    printf("Informe o novo telefone: ");
                    scanf(" %[^\n]s", temp->cliente->telefone);
                    limpa_buffer();
                    if (!validaTelefone(temp->cliente->telefone))
                    {
                        return root;
                    }
                    strcpy(temp->cliente->telefone, formatarTelefone(temp->cliente->telefone));
                    op2 = 0;
                    break;
                case 0:
                    printf("\033[1;34mSaindo do menu de edicao.\033[0m\n");
                    break;
                default:
                    printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
                    break;
                }
            } while (op2 != 0);
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
    } while (op != 0);
    //FILE *data = fopen("../data/clientes.txt", "w");
    FILE * data = fopen("..\\..\\data\\clientes.txt", "w");
    if (data == NULL)
    {
        printf("Erro ao abrir o arquivo");
        pressiona_enter();
        return root;
    }
    
    reescreverarquivoClientes(root, data);
    fclose(data);
    return root;
}

Medicamento *buscar_medicamento(Medicamento *root)
{
    char nome[100];
    printf("Informe o nome do medicamento: ");
    scanf(" %[^\n]s", nome);
    limpa_buffer();
    strcpy(nome, formatarNome(nome));
    Medicamento *temp = buscaMedicamento(root, nome);
    if (temp == NULL)
    {
        printf("\033[1;31mMedicamento nao encontrado.\033[0m\n");
        pressiona_enter();
        return root;
    }
    int op;
    int op2;
    do
    {
        limpa_tela();
        printf("\033[1;32mMedicamento encontrado.\033[0m\n");
        printf("Nome: %s\n", temp->info.nome);
        printf("Preco: %.2f\n", temp->info.preco);
        printf("Estoque: %d\n", temp->info.estoque);
        menumedicamento();
        op = lerOpcao();
        limpa_buffer();
        if (op == -1)
        {
            printf("---------------------------------------\n");
            continue;
        }
        switch (op)
        {
        case 1:
            do
            {
                printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
                printf("1 - Editar nome\n");
                printf("2 - Editar preco\n");
                printf("3 - Editar estoque\n");
                printf("0 - Voltar\n");
                printf("---------------------------------------\n");
                op2 = lerOpcao();
                limpa_buffer();
                if (op2 == -1)
                {
                    printf("---------------------------------------\n");
                    continue;
                }
                switch (op2)
                {
                case 1:
                    printf("Informe o novo nome: ");
                    scanf(" %[^\n]s", nome);
                    limpa_buffer();
                    if (!validaNome(nome))
                    {
                        return root;
                    }
                    strcpy(temp->info.nome, formatarNome(nome));
                    break;
                case 2:
                    printf("Informe o novo preco: ");
                    scanf("%f", &temp->info.preco);
                    limpa_buffer();
                    break;
                case 3:
                    printf("Informe o novo estoque: ");
                    scanf("%d", &temp->info.estoque);
                    limpa_buffer();
                    break;
                case 0:
                    printf("\033[1;34mSaindo do menu de edicao.\033[0m\n");
                    break;
                default:
                    printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
                    break;
                }
            } while (op2 != 0);
            break;
        case 2:
            root = removerMedicamento(root, nome);
            printf("\033[1;34mMedicamento removido com sucesso!\033[0m\n");
            pressiona_enter();
            return root;
            break;
        case 0:
            printf("\033[1;34mVoltando ao menu principal.\033[0m\n");
            break;
        default:
            printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
            break;
        }
    } while (op != 0);
    FILE *data = fopen("..\\..\\data\\medicamentos.txt", "w");
    if (data == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return root;
    }
    reecreverarquivoMedicamento(root, data);
    return root;
}