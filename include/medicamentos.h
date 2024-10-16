
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct medicamento Medicamento;

int calchash(char *nome);

Medicamento *criaNo(char *nome, float preco, int estoque);

void cadastroMedicamento(Medicamento *hashTable[], char *nome, float preco, int estoque);

int buscaMedicamento(Medicamento *hashTable[], char *nome);

void removerMedicamento(Medicamento *hashTable[], char *nome);

void reescreverarquivo(Medicamento *hashTable[], FILE *data);

void inicializarBaseDadosMedicamentos(Medicamento *hashTable[]);