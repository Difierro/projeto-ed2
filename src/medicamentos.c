#ifndef MEDICAMENTOS_H
#define MEDICAMENTOS_H
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

int maxi(int a, int b){
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

Medicamento * menorNoMed(Medicamento * root){
    Medicamento * atual = root;
    while (atual->esq != NULL){
        atual = atual->esq;
    }
    return atual;
}

Medicamento * rotacaoDir(Medicamento * root){
    Medicamento * t1 = root->esq;
    Medicamento * t2 = t1->dir;

    t1->dir = root;
    root->esq = t2;

    root->altura =  1 + maxi(altura(root->esq), altura(root->dir));
    t1->altura =  1 + maxi(altura(t1->esq), altura(t1->dir));

    return t1;
}

Medicamento * rotacaoEsq(Medicamento * root){
    Medicamento * t1 = root->dir;
    Medicamento * t2 = t1->esq;

    t1->esq = root;
    root->dir = t2;

    root->altura =  1 + maxi(altura(root->esq), altura(root->dir));
    t1->altura =  1 + maxi(altura(t1->esq), altura(t1->dir));

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
        printf("\033[1;31mProduto ja cadastrado.\033[0m\n");
        return root;
    }

    root->altura = 1 + maxi(altura(root->esq), altura(root->dir));

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

    FILE * data = fopen("..\\..\\data\\medicamentos.txt", "a");
    if (data == NULL) {
        printf("Erro ao abrir o arquivo");
        return root;
    }
    fprintf(data, "%s\t%.2f\t%d\n", nome, preco, estoque);

    fclose(data);
    
    return root;
}

Medicamento * inicializarBaseDadosMedicamento(Medicamento * root){
    FILE* data = fopen("..\\..\\data\\medicamentos.txt", "r");
    if (data == NULL) {
        printf("Erro ao abrir o arquivo medicamentos.txt\n");
        return root;
    }

    char nome[100];
    float preco;
    int estoque;

    while(fscanf(data, "%[^\t]\t%f\t%d\n", nome, &preco, &estoque) == 3){
        root = insereNo(root, nome, preco, estoque);
    }

    fclose(data);

    return root;
}

Medicamento * buscaMedicamento(Medicamento * root, char * nome){
    if (root == NULL){
        return root;
    }

    if(strcmp(nome, root->info.nome) < 0){
        return buscaMedicamento(root->esq, nome);
    }else if(strcmp(nome, root->info.nome) > 0){
        return buscaMedicamento(root->dir, nome);
    }else{
        return root;
    }
}

Medicamento * editarMedicamento(Medicamento * root, char * nome){
    if(strcmp(nome, root->info.nome) < 0){
        return editarMedicamento(root->esq, nome);
    }else if(strcmp(nome, root->info.nome) > 0){
        return editarMedicamento(root->dir, nome);
    }else{
        int op;
        do{
            menumedicamento();
            op = lerOpcao();
            if (op == -1){
                printf("---------------------------------------\n");
                continue;
            }
            switch (op){
            case 1:
                printf("Informe o novo nome: ");
                scanf(" %[^\n]s", nome);
                if (!validaNome(nome)){
                    return root;
                }
                strcpy(nome,formatarNome(nome));
                break;
            case 2:
                printf("Informe o novo preco: ");
                scanf("%f", &root->info.preco);
                break;
            case 3:
                printf("Informe o novo estoque: ");
                scanf("%d", &root->info.estoque);
                break;
            case 0:
                printf("\033[1;34mVoltando ao menu principal.\033[0m\n");
                break;
            default:
                printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
                break;
            }
        } while (op != 0);
        return root;
    }
}

Medicamento * removerMedicamento(Medicamento * root, char * nome){
    if (root == NULL){
        printf("\033[1;31mMedicamento nao encontrado.\033[0m\n");
        return root;
    }

    if(strcmp(nome, root->info.nome) < 0){
        root->esq = removerMedicamento(root->esq, nome);
    }else if(strcmp(nome, root->info.nome) > 0){
        root->dir = removerMedicamento(root->dir, nome);
    }else{
        if (root->esq == NULL || root->dir == NULL){
            Medicamento * temp = root->esq ? root->esq : root->dir;
            if (temp == NULL){
                temp = root;
                root = NULL;
            }else{
                *root = *temp;
            }
            free(temp);
        }else{
            Medicamento * temp = menorNoMed(root->dir);
            strcpy(root->info.nome, temp->info.nome);
            root->info.preco = temp->info.preco;
            root->info.estoque = temp->info.estoque;
            root->dir = removerMedicamento(root->dir, temp->info.nome);
        }
    }

    if (root == NULL){
        return root;
    }

    root->altura = 1 + maxi(altura(root->esq), altura(root->dir));

    int fb = fatorBalanco(root);

    if(fb > 1 && fatorBalanco(root->esq) >= 0){
        return rotacaoDir(root);
    }

    if(fb > 1 && fatorBalanco(root->esq) < 0){
        root->esq = rotacaoEsq(root->esq);
        return rotacaoDir(root);
    }

    if(fb < -1 && fatorBalanco(root->dir) <= 0){
        return rotacaoEsq(root);
    }

    if(fb < -1 && fatorBalanco(root->dir) > 0){
        root->dir = rotacaoDir(root->dir);
        return rotacaoEsq(root);
    }

    return root;
}

#endif