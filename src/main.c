#include "..\include\medicamentos.h"

int main()
{
    Medicamento *raiz = NULL;
    int op;
    raiz = inicializarBaseDados(raiz);
    char nome[100];
    float preco;
    int estoque;

    printf("\n---------------------------------------\n");
    printf("\033[1;34mSeja Bem vindo a Farmatech\033[0m\n");
    printf("---------------------------------------\n");
    do
    {
        printf("\033[1;34m---- Menu de opcoes ----\033[0m\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Cadastrar de medicamento\n");
        printf("3 - Cadastro de receita\n");
        printf("4 - Buscar cliente\n");
        printf("5 - Buscar medicamento\n");
        printf("6 - Imprimir informacoes do cliente\n");
        printf("0 - Sair\n");
        printf("---------------------------------------\n");
        op = lerOpcao();

        if (op == -1)
        {
            printf("---------------------------------------\n");
            continue;
        }

        switch (op)
        {
        case 1:

            break;
        case 2:

            printf("Informe o nome do medicamento: ");
            scanf(" %[^\n]s", nome);

            if (!validaNome(nome))
            {
                break;
            }
            printf("Informe o preco: ");
            scanf("%f", &preco);

            printf("Informe o estoque: ");
            if ((scanf(" %d", &estoque)) != 1)
            {
                printf("\033[1;31mPermitido apenas numeros.\033[0m\n");
                while (getchar() != '\n')
                    ;
            }

            raiz = cadastroMedicamento(raiz, nome, preco, estoque);
            printf("\033[1;34mMedicamento cadastrado com sucesso!\033[0m\n");

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

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
