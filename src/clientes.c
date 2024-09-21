#include "..\include\clientes.h"

struct clientes{
    Infocliente *cliente;
    Clientes *esq;
    Clientes *dir;
    int alturaC;
};

struct infocliente{
    char nome[50];
    char cpf[12];
    char telefone[12];
    Carrinho *carrinho;
};

struct carrinho{
    float precototal;
    Info *info;
    Carrinho *prox;
};

int maxC(int a, int b){
    return (a > b) ? a : b;
}

int alturaC(Clientes * node){
    if(node == NULL) return 0;
    return node->alturaC;
}

int fatorBalancoC(Clientes * node){
    if (node == NULL) return 0;
    return (alturaC(node->esq) - alturaC(node->dir));
}

Clientes * rotacaoDirC(Clientes * root){
    Clientes * t1 = root->esq;
    Clientes * t2 = t1->dir;

    t1->dir = root;
    root->esq = t2;

    root->alturaC =  1 + maxC(alturaC(root->esq), alturaC(root->dir));
    t1->alturaC =  1 + maxC(alturaC(t1->esq), alturaC(t1->dir));

    return t1;
}

Clientes * rotacaoEsqC(Clientes * root){
    Clientes * t1 = root->dir;
    Clientes * t2 = t1->esq;

    t1->esq = root;
    root->dir = t2;

    root->alturaC =  1 + maxC(alturaC(root->esq), alturaC(root->dir));
    t1->alturaC =  1 + maxC(alturaC(t1->esq), alturaC(t1->dir));

    return t1;
}

Clientes * criaNoCliente(Clientes * root, char * nome, char * cpf, char * telefone){
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

Clientes * insereNoCliente(Clientes * root, char * nome, char * cpf, char * telefone){
    if(root == NULL){
        return criaNoCliente(root, nome, cpf, telefone);
    }

    if(strcmp(cpf, root->cliente->cpf) < 0){
        root->esq = insereNoCliente(root->esq, nome, cpf, telefone);
    }else if(strcmp(cpf, root->cliente->cpf) > 0){
        root->dir = insereNoCliente(root->dir, nome, cpf, telefone);
    }else{
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

Clientes * cadastroClientes(Clientes * root, char * nome, char * cpf, char * telefone){
    root = insereNoCliente(root, nome, cpf, telefone);

    FILE * data = fopen("data/clientes.txt", "a");
    if (data == NULL) {
        printf("Erro ao abrir o arquivo");
        return root;
    }
    fprintf(data, "%s;%s;%s\n", nome, cpf, telefone);

    fclose(data);
    
    return root;

}

Clientes * inicializarBaseDadosClientes(Clientes * root){
    FILE * data = fopen("data/clientes.txt", "r");
    if (data == NULL) {
        printf("Erro ao abrir o arquivo");
        return root;
    }

    char nome[50], cpf[12], telefone[12];
    while(fscanf(data, "%[^;];%[^;];%s\n", nome, cpf, telefone) != EOF){
        root = insereNoCliente(root, nome, cpf, telefone);
    }

    fclose(data);

    return root;
}