#include "..\include\medicamentos.h"

struct info{
    char nome[100];
    float preco;
    int estoque;
};

struct medicamento{
    Info info;
    Medicamento * dir;
    Medicamento * esq;
    int altura;
};

int max(int a, int b){
    return (a > b) ? a : b;
}

int altura(Medicamento * node){
    if(node == NULL) return 0;
    return node->altura;
}

int fatorBalanco(Medicamento * node){
    if (node == NULL) return 0;
    return (altura(node->esq) - altura(node->dir));
}

Medicamento * rotacaoDir(Medicamento * root){
    Medicamento * t1 = root->esq;
    Medicamento * t2 = t1->dir;

    t1->dir = root;
    root->esq = t2;

    root->altura =  1 + max(altura(root->esq), altura(root->dir));
    t1->altura =  1 + max(altura(t1->esq), altura(t1->dir));

    return t1;
}

Medicamento * rotacaoEsq(Medicamento * root){
    Medicamento * t1 = root->dir;
    Medicamento * t2 = t1->esq;

    t1->esq = root;
    root->dir = t2;

    root->altura =  1 + max(altura(root->esq), altura(root->dir));
    t1->altura =  1 + max(altura(t1->esq), altura(t1->dir));

    return t1;
}

Medicamento * criaNo(Medicamento * root, char * nome, float preco, int estoque){
    root = (Medicamento*) malloc(sizeof(Medicamento));
    strcpy(root->info.nome, nome);
    root->info.preco = preco;
    root->info.estoque = estoque;
    root->altura = 1;
    root->dir = NULL;
    root->esq = NULL;
    return root;
}

Medicamento * insereNo(Medicamento * root, char * nome, float preco, int estoque){
    if (root == NULL){
        root = criaNo(root, nome, preco, estoque);
        return root;
    }

    if(strcmp(nome, root->info.nome) < 0){
        root->esq = insereNo(root->esq, nome, preco, estoque);
    }else if(strcmp(nome, root->info.nome) > 0){
        root->dir = insereNo(root->dir, nome, preco, estoque);
    }else{
        printf("produto ja cadastrado");
        return root;
    }

    root->altura = 1 + max(altura(root->esq), altura(root->dir));

    int fb = fatorBalanco(root);

    if(fb > 1 && strcmp(nome, root->esq->info.nome) < 0){
        return rotacaoDir(root);
    }

    if(fb < -1 && strcmp(nome, root->dir->info.nome) > 0){
        return rotacaoEsq(root);
    }

    if(fb > 1 && strcmp(nome, root->esq->info.nome) > 0){
        root->esq = rotacaoEsq(root->esq);
        return rotacaoDir(root);
    }

    if(fb < -1 && strcmp(nome, root->dir->info.nome) < 0){
        root->dir = rotacaoDir(root->dir);
        return rotacaoEsq(root);
    }
    
    return root;
}

Medicamento * cadastroMedicamento(Medicamento * root, char * nome, float preco, int estoque){
    root = insereNo(root, nome, preco, estoque);

    FILE * data = fopen("data/medicamentos.txt", "a");
    if (data == NULL) {
        printf("Erro ao abrir o arquivo");
        return root;
    }
    fprintf(data, "%s\t%.2f\t%d\n", nome, preco, estoque);

    fclose(data);
    
    return root;
}
