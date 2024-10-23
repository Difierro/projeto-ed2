#ifndef ENTREGAS_H
#define ENTREGAS_H
#include "..\include\entregas.h"

#define MAX_SIZE 100

struct infoEntregas{
    int codigo;
    Carrinho *carrinho;
};

struct minHeap{
    int tamanho;
    InfoEntregas entrega[MAX_SIZE];
};

void inicializarHeap(MinHeap *heap){
    heap->tamanho = 0;
    memset(heap->entrega, 0, 800);
}

int pai(int i){
    return (i - 1) / 2;
}

int esquerda(int i){
    return (2 * i) + 1;
}

int direita(int i){
    return (2 * i) + 2;
}

void troca(InfoEntregas *a, InfoEntregas *b){
    InfoEntregas temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap *heap, int i){
    int menor = i;
    int e = esquerda(i);
    int d = direita(i);

    if (e < heap->tamanho && heap->entrega[e].codigo < heap->entrega[menor].codigo){
        menor = e;
    }
    if (d < heap->tamanho && heap->entrega[d].codigo < heap->entrega[menor].codigo){
        menor = d;
    }
    if (menor != i){
        troca(&heap->entrega[i], &heap->entrega[menor]);
        heapify(heap, menor);
    }
}

void insereHeap(MinHeap *heap, InfoEntregas entrega){
    if (heap->tamanho == MAX_SIZE){
        printf("\033[1;31mHeap cheio!\033[0m\n");
        return;
    }
    int i = heap->tamanho;
    heap->entrega[i] = entrega;
    heap->tamanho++;
    while (i && heap->entrega[pai(i)].codigo > heap->entrega[i].codigo){
        troca(&heap->entrega[i], &heap->entrega[pai(i)]);
        i = pai(i);
    }
}

InfoEntregas extraiMin(MinHeap *heap){
    if (heap->tamanho <= 0){
        printf("\033[1;31mHeap vazio!\033[0m\n");
        InfoEntregas vazio;
        vazio.codigo = -1;
        return vazio;
    }
    if (heap->tamanho == 1){
        heap->tamanho--;
        return heap->entrega[0];
    }
    InfoEntregas entrega = heap->entrega[0];
    heap->entrega[0] = heap->entrega[heap->tamanho - 1];
    heap->tamanho--;
    heapify(heap, 0);
    return entrega;
}

void imprimeHeap(MinHeap *heap){
    for (int i = 0; i < heap->tamanho; i++){
        printf("Codigo: %d\n", heap->entrega[i].codigo);
        printf("Carrinho:\n");
        Medicamento *temp = heap->entrega[i].carrinho->medicamento;
        while (temp != NULL){
            printf("Nome: %s\n", temp->nome);
            printf("Preco: %.2f\n", temp->preco);
            printf("Estoque: %d\n", temp->estoque);
            temp = temp->next;
        }
    }
}

void imprimeMinHeap(InfoEntregas entrega){
    printf("Codigo: %d\n", entrega.codigo);
    printf("Carrinho:\n");
    Medicamento *temp = entrega.carrinho->medicamento;
    while (temp != NULL){
        printf("Nome: %s\n", temp->nome);
        printf("Preco: %.2f\n", temp->preco);
        printf("Estoque: %d\n", temp->estoque);
        temp = temp->next;
    }
}

Carrinho * criaNoCarrinho(Medicamento * medicamento, int quantidade){
    Carrinho * novo = (Carrinho*) malloc(sizeof(Carrinho));
    novo->medicamento = (Medicamento*) malloc(sizeof(Medicamento));
    strcpy(novo->medicamento->nome, medicamento->nome);
    novo->medicamento->preco = medicamento->preco;
    novo->medicamento->estoque = quantidade;
    novo->precototal = ((float)quantidade * medicamento->preco);
    novo->medicamento->next = NULL;
    return novo;
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
        root->precototal -= ((float)temp->estoque * (float)temp->preco);
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