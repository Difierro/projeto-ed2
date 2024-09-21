
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/menu_funcoes.c"

typedef struct info Info;

typedef struct medicamento Medicamento;

int maxi(int a, int b);

int altura(Medicamento *node);

int fatorBalanco(Medicamento *node);

Medicamento *rotacaoDir(Medicamento *root);

Medicamento *rotacaoEsq(Medicamento *root);

Medicamento *criaNo(Medicamento *root, char *nome, float preco, int estoque);

Medicamento *insereNo(Medicamento *root, char *nome, float preco, int estoque);

Medicamento * cadastroMedicamento(Medicamento * root, char * nome, float preco, int estoque);

Medicamento * inicializarBaseDadosMedicamento(Medicamento * root);

