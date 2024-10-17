#ifndef CLIENTES_H
#define CLIENTES_H
#include "..\include\clientes.h"
struct clientes{
    Infocliente *cliente;
    Clientes *esq;
    Clientes *dir;
    int alturaC;
};

struct infocliente{
    char nome[50];
    char cpf[20];
    char telefone[20];
    Carrinho *carrinho;
};

struct carrinho{
    float precototal;
    Medicamento *medicamento;
};

int maxC(int a, int b){
    return (a > b) ? a : b;
}

int alturaC(Clientes *node){
    if(node == NULL) return 0;
    return node->alturaC;
}

int fatorBalancoC(Clientes *node){
    if(node == NULL) return 0;
    return (alturaC(node->esq) - alturaC(node->dir));
}

Clientes *menorNoCliente(Clientes *root){
    Clientes *current = root;
    while(current->esq != NULL){
        current = current->esq;
    }
    return current;
}

Clientes *rotacaoDirC(Clientes *root){
    Clientes * t1 = root->esq;
    Clientes * t2 = t1->dir;
    t1->dir = root;
    root->esq = t2;

    root->alturaC =  1 + maxC(alturaC(root->esq), alturaC(root->dir));
    t1->alturaC =  1 + maxC(alturaC(t1->esq), alturaC(t1->dir));

    return t1;
}

Clientes *rotacaoEsqC(Clientes *root){
    Clientes *t1 = root->dir;
    Clientes *t2 = t1->esq;
    t1->esq = root;
    root->dir = t2;

    root->alturaC =  1 + maxC(alturaC(root->esq), alturaC(root->dir));
    t1->alturaC =  1 + maxC(alturaC(t1->esq), alturaC(t1->dir));

    return t1;
}

Clientes *criaNoCliente(Clientes *root, char *nome, char * cpf, char * telefone){
    root = (Clientes*) malloc(sizeof(Clientes));
    root->cliente = (Infocliente*) malloc(sizeof(Infocliente));
    strcpy(root->cliente->nome, nome);
    strcpy(root->cliente->cpf, cpf);
    strcpy(root->cliente->telefone, telefone);
    root->cliente->carrinho = NULL;
    root->esq = NULL;
    root->dir = NULL;
    root->alturaC = 1;

    return root;
}

Clientes *insereNoCliente(Clientes *root, char *nome, char *cpf, char *telefone){
    if(root == NULL){
        return criaNoCliente(root, nome, cpf, telefone);
    }
    if(strcmp(cpf, root->cliente->cpf) < 0){
        root->esq = insereNoCliente(root->esq, nome, cpf, telefone);
    }else if(strcmp(cpf, root->cliente->cpf) > 0){
        root->dir = insereNoCliente(root->dir, nome, cpf, telefone);
    }else{
        printf("\033[1;31mCliente ja cadastrado.\033[0m\n");
        return root;
    }
    root->alturaC = 1 + maxC(alturaC(root->esq), alturaC(root->dir));
    int fator = fatorBalancoC(root);

    if(fator > 1 && strcmp(cpf, root->esq->cliente->cpf) < 0){
        return rotacaoDirC(root);
    }
    if(fator < -1 && strcmp(cpf, root->dir->cliente->cpf) > 0){
        return rotacaoEsqC(root);
    }
    if(fator > 1 && strcmp(cpf, root->esq->cliente->cpf) > 0){
        root->esq = rotacaoEsqC(root->esq);
        return rotacaoDirC(root);
    }
    if(fator < -1 && strcmp(cpf, root->dir->cliente->cpf) < 0){
        root->dir = rotacaoDirC(root->dir);
        return rotacaoEsqC(root);
    }
    return root;
}

Clientes *cadastroClientes(Clientes *root, char *nome, char *cpf, char *telefone){
    root = insereNoCliente(root, nome, cpf, telefone);
    return root;
}

void reescreverarquivoClientes(Clientes *root, FILE *data){
    if(root == NULL){
        return;
    }
    reescreverarquivoClientes(root->esq, data);
    fprintf(data, "%s;%s;%s;\n", root->cliente->nome, root->cliente->cpf, root->cliente->telefone);
    reescreverarquivoClientes(root->dir, data);
}

Clientes *inicializarBaseDadosClientes(Clientes *root){
    //FILE *data = fopen("../data/clientes.txt", "r");
    FILE *data = fopen("../../data/clientes.txt", "r");

    char linha[100], nome[50], cpf[20], telefone[20];
    while(fgets(linha, 100, data) != NULL){
        sscanf(linha, "%[^;];%[^;];%[^;]", nome, cpf, telefone);
        root = insereNoCliente(root, nome, cpf, telefone);
    }
    fclose(data);
    return root;
}

Clientes *buscaCliente(Clientes *root, char *cpf){
    if(root == NULL){
        return root;
    }
    if(strcmp(cpf, root->cliente->cpf) < 0){
        return buscaCliente(root->esq, cpf);
    }else if(strcmp(cpf, root->cliente->cpf) > 0){
        return buscaCliente(root->dir, cpf);
    }else{
        return root;
    }
}

Clientes *removerCliente(Clientes *root, char *cpf){
    if(root == NULL){
        return root;
    }
    if(strcmp(cpf, root->cliente->cpf) < 0){
        root->esq = removerCliente(root->esq, cpf);
    }else if(strcmp(cpf, root->cliente->cpf) > 0){
        root->dir = removerCliente(root->dir, cpf);
    }else{
        if(root->esq == NULL || root->dir == NULL){
            Clientes *temp = root->esq ? root->esq : root->dir;

            if(temp == NULL){
                temp = root;
                root = NULL;
            }else{
                *root = *temp;
            }
            free(temp);
        }else{
            Clientes *temp = menorNoCliente(root->dir);

            strcpy(root->cliente->nome, temp->cliente->nome);
            strcpy(root->cliente->cpf, temp->cliente->cpf);
            strcpy(root->cliente->telefone, temp->cliente->telefone);
            root->dir = removerCliente(root->dir, temp->cliente->cpf);
        }
    }
    if(root == NULL){
        return root;
    }
    root->alturaC = 1 + maxC(alturaC(root->esq), alturaC(root->dir));
    int fator = fatorBalancoC(root);

    if(fator > 1 && fatorBalancoC(root->esq) >= 0){
        return rotacaoDirC(root);
    }
    if(fator > 1 && fatorBalancoC(root->esq) < 0){
        root->esq = rotacaoEsqC(root->esq);
        return rotacaoDirC(root);
    }
    if(fator < -1 && fatorBalancoC(root->dir) <= 0){
        return rotacaoEsqC(root);
    }
    if(fator < -1 && fatorBalancoC(root->dir) > 0){
        root->dir = rotacaoDirC(root->dir);
        return rotacaoEsqC(root);
    }
    
    return root;
}

Carrinho * criaNoCarrinho(Medicamento * medicamento, int quantidade){
    Carrinho * novo = (Carrinho*) malloc(sizeof(Carrinho));

    strcpy(novo->medicamento->nome, medicamento->nome);
    novo->medicamento->preco = medicamento->preco;
    novo->medicamento->estoque = quantidade;
    novo->precototal += quantidade * medicamento->preco;

    return novo;
}

Carrinho * insereNoCarrinho(Carrinho * root, Medicamento * medicamento, int quantidade){
    if(root == NULL){
        return criaNoCarrinho(medicamento, quantidade);
    }

    if(strcmp(medicamento->nome, root->medicamento->nome) == 0){
        root->medicamento->estoque += quantidade;
        root->precototal += quantidade * medicamento->preco;
        return root;
    }

    Medicamento * temp = root->medicamento;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = criaNo(medicamento->nome, medicamento->preco, quantidade);
    root->precototal += quantidade * medicamento->preco;
    return root;
}

Carrinho * removerCarrinho(Carrinho * root, Medicamento * medicamento){
    if(root == NULL){
        printf("\033[1;31mCarrinho vazio.\033[0m\n");
        sleep(1);
        return root;
    }

    Medicamento * temp = root->medicamento;
    Medicamento * ant = NULL;
    while(temp->next != NULL && strcmp(temp->nome, medicamento->nome) != 0){
        ant = temp;
        temp = temp->next;
    }

    if(temp->next == NULL && strcmp(temp->nome, medicamento->nome) != 0){
        printf("\033[1;31mMedicamento nao encontrado no carrinho.\033[0m\n");
        sleep(1);
        return root;
    }

    if(strcmp(temp->nome, medicamento->nome) == 0){
        root->precototal -= temp->estoque * temp->preco;
        if(ant == NULL){
            root->medicamento = temp->next;
            free(temp);
            return root;
        }
        ant->next = temp->next;
        free(temp);
        return root;
    }
    return root;
}
#endif