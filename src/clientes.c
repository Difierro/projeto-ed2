#include "..\include\clientes.h"

struct dadoscliente{
    char nome[100];
    char cpf[14];
    char endereco[100];
    char telefone[11];
};

struct cliente{
    Dadoscliente dados;
    Cliente * dir;
    Cliente * esq;
    int altura;
};

int max(int a, int b){
    return (a > b) ? a : b;
}

int altura(Cliente * node){
    if(node == NULL) return 0;
    return node->altura;
}

int fatorBalanco(Cliente * node){
    if (node == NULL) return 0;
    return (altura(node->esq) - altura(node->dir));
}

Cliente * rotacaoDir(Cliente * root){
    Cliente * t1 = root->esq;
    Cliente * t2 = t1->dir;

    t1->dir = root;
    root->esq = t2;

    root->altura =  1 + max(altura(root->esq), altura(root->dir));
    t1->altura =  1 + max(altura(t1->esq), altura(t1->dir));

    return t1;
}

Cliente * rotacaoEsq(Cliente * root){
    Cliente * t1 = root->dir;
    Cliente * t2 = t1->esq;

    t1->esq = root;
    root->dir = t2;

    root->altura =  1 + max(altura(root->esq), altura(root->dir));
    t1->altura =  1 + max(altura(t1->esq), altura(t1->dir));

    return t1;
}

Cliente * criaNo(Cliente * root, char * nome, char * cpf, char * endereco, char * telefone){
    root = (Cliente*) malloc(sizeof(Cliente));
    strcpy(root->dados.nome, nome);
    strcpy(root->dados.cpf, cpf);
    strcpy(root->dados.endereco, endereco);
    strcpy(root->dados.telefone, telefone);
    root->dir = NULL;
    root->esq = NULL;
    root->altura = 1;

    return root;
}

Cliente * insereNo(Cliente * root, char * nome, char * cpf, char * endereco, char * telefone){
    if (root == NULL){
        root = criaNo(root, nome, cpf, endereco, telefone);
        return root;
    }

    if (strcmp(nome, root->dados.nome) < 0){
        root->esq = insereNo(root->esq, nome, cpf, endereco, telefone);
    } else if (strcmp(nome, root->dados.nome) > 0){
        root->dir = insereNo(root->dir, nome, cpf, endereco, telefone);
    } else {
        printf("\033[1;31mCliente ja cadastrado.\033[0m\n");
        pressiona_enter();
        return root;
    }

    root->altura = 1 + max(altura(root->esq), altura(root->dir));

    int fb = fatorBalanco(root);

    if (fb > 1 && strcmp(nome, root->esq->dados.nome) < 0){
        return rotacaoDir(root);
    }

    if (fb < -1 && strcmp(nome, root->dir->dados.nome) > 0){
        return rotacaoEsq(root);
    }

    if (fb > 1 && strcmp(nome, root->esq->dados.nome) > 0){
        root->esq = rotacaoEsq(root->esq);
        return rotacaoDir(root);
    }

    if (fb < -1 && strcmp(nome, root->dir->dados.nome) < 0){
        root->dir = rotacaoDir(root->dir);
        return rotacaoEsq(root);
    }

    return root;
}

Cliente * cadastroCliente(Cliente * root, char * nome, char * cpf, char * endereco, char * telefone){
    root = insereNo(root, nome, cpf, endereco, telefone);

    FILE * data = fopen("data/clientes.txt", "a");
    if (data == NULL) {
        printf("Erro ao abrir o arquivo");
        return root;
    }
    fprintf(data, "%s;%s;%s;%s\n", nome, cpf, endereco, telefone);

    fclose(data);
    
    return root;

}

Cliente * inicializarBaseDados(Cliente * root){
    FILE * data = fopen("data/clientes.txt", "r");
    if (data == NULL) {
        printf("Erro ao abrir o arquivo");
        return root;
    }

    char nome[100];
    char cpf[14];
    char endereco[100];
    char telefone[11];

    while (fscanf(data, "%[^;];%[^;];%[^;];%[^\n]\n", nome, cpf, endereco, telefone) != EOF){
        root = insereNo(root, nome, cpf, endereco, telefone);
    }

    fclose(data);

    return root;
}