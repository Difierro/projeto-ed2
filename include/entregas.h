#include "..\src\medicamentos.c"
#include "..\src\clientes.c"

#include <stdio.h>
#include <stdlib.h>

typedef struct infoEntregas InfoEntregas;

typedef struct minHeap MinHeap;

void inicializarHeap(MinHeap *heap);

int pai(int i);

int esquerda(int i);

int direita(int i);

void troca(InfoEntregas *a, InfoEntregas *b);

void heapify(MinHeap *heap, int i);

void insereHeap(MinHeap *heap, InfoEntregas entrega);

InfoEntregas extraiMin(MinHeap *heap);

void imprimeHeap(MinHeap *heap);

void imprimeMinHeap(InfoEntregas entrega);

Carrinho *criaNoCarrinho(Medicamento *medicamento, int quantidade);

Carrinho *removerCarrinho(Carrinho *root, Medicamento *medicamento);