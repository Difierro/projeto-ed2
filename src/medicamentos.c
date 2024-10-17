#ifndef MEDICAMENTOS_H
#define MEDICAMENTOS_H
#include "..\include\medicamentos.h"
#define MAX_HASH 257

struct medicamento{
    char nome[100];  
    float preco;
    int estoque;
    Medicamento *next;
};

int calchash(char *nome){
    int i, hash = 0;
    for (i = 0; nome[i] != '\0'; i++){
        hash += nome[i];
    }
    return hash % MAX_HASH;
}

Medicamento *criaNo(char *nome, float preco, int estoque){
    Medicamento *novo = (Medicamento *)malloc(sizeof(Medicamento));
    strcpy(novo->nome, nome);
    novo->preco = preco;
    novo->estoque = estoque;
    novo->next = NULL;
    return novo;
}

void cadastroMedicamento(Medicamento *hashTable[], char *nome, float preco, int estoque){
    int index = calchash(nome);
    Medicamento *novo = criaNo(nome, preco, estoque);
    if (hashTable[index] == NULL){
        hashTable[index] = novo;
    } else {
        Medicamento *aux = hashTable[index];
        while (aux->next != NULL){
            aux = aux->next;
        }
        aux->next = novo;
    }
}

int buscaMedicamento(Medicamento *hashTable[], char *nome){
    int index = calchash(nome);
    Medicamento *aux = hashTable[index];
    while (aux != NULL){
        if (strcmp(aux->nome, nome) == 0){
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

void removerMedicamento(Medicamento *hashTable[], char *nome){
    int index = calchash(nome);
    Medicamento *aux = hashTable[index];
    Medicamento *ant = NULL;
    while (aux != NULL && strcmp(aux->nome, nome) != 0){
        ant = aux;
        aux = aux->next;
    }
    if (aux == NULL){
        printf("\033[1;31mMedicamento nao encontrado!\033[0m\n");
        return;
    }
    if (ant == NULL){
        hashTable[index] = aux->next;
    } else {
        ant->next = aux->next;
    }
    free(aux);
}

void reescreverarquivo(Medicamento *hashTable[], FILE *data){
    for (int i = 0; i < MAX_HASH; i++){
        Medicamento *aux = hashTable[i];
        while (aux != NULL){
            fprintf(data, "%s;%.2f;%d\n", aux->nome, aux->preco, aux->estoque);
            aux = aux->next;
        }
    }
}

void inicializarBaseDadosMedicamentos(Medicamento *hashTable[], FILE *data){
    char nome[50], linha[100];
    float preco;
    int estoque;
    while(fgets(linha, 100, data) != NULL){
        sscanf(linha, "%[^;];%f;%d", nome, &preco, &estoque);
        cadastroMedicamento(hashTable, nome, preco, estoque);
    }
    
    fclose(data);
}

#endif