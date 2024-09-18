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

Medicamento * inicializarBaseDados(Medicamento * root){
    FILE* data = fopen("data/medicamentos.txt", "r");
    if (data == NULL) {
        printf("Erro ao abrir o arquivo");
        return root;
    }
    int caractere;
    int qtdMed = 0;

    while ((caractere = fgetc(data)) != EOF) {
        if (caractere == '\n') {
            qtdMed++;
        }
    }

    rewind(data);
    int i = 0;
    while (i < qtdMed) {
        Info temp;
        if (fscanf(data, "%[^\t]\t%f\t%d\n", temp.nome, &temp.preco, &temp.estoque) == 3) {
            root = insereNo(root, temp.nome, temp.preco, temp.estoque);
        } else {
            fprintf(stderr, "Erro ao ler os dados do medicamento na linha %d\n", i + 1);
        }
        i++;
    }
    fclose(data);

    return root;
}


int lerOpcao() {
    char opcao[10];
    int i;

    printf("\033[1;34mDigite a opcao desejada:\033[0m\n");
    scanf("%s", opcao);

    for (i = 0; opcao[i] != '\0'; i++) {
        if (!isdigit(opcao[i])) {
            printf("\033[1;31mOpcao invalida. Informe um numero correspondente com as opcoes do menu.\033[0m\n");
            return -1;
        }
    }

    int escolha = atoi(opcao);
    if (escolha < 0 || escolha > 6) { 
        printf("\033[1;31mOpcao invalida! Por favor, escolha uma opcao valida.\033[0m\n");
        return -1; 
    }

    return escolha;
}


int validaNome(char *nome){
    int i; 
    int espacamento = 1;

    for (i = 0; nome[i]; i++){

        if (!isalpha(nome[i]) && nome[i] != ' '){
            printf("\033[1;31mO nome deve conter apenas letras.\033[0m\n"); 
            return 0; 
        }

        if (espacamento && !isupper(nome[i])) {
            printf("\033[1;31mA primeira letra do nome deve ser maiuscula, tente novamente.\033[0m\n"); 
            return 0; 
        }

        if (nome[i] == ' '){
            espacamento = 1; 
        }
        else{
            espacamento = 0; 
        }
    }
    return 1; 
}