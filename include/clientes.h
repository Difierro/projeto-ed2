
#ifndef MEDICAMENTOS_H
#define MEDICAMENTOS_H
#include "..\src\medicamentos.c"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct clientes Clientes;

typedef struct infocliente Infocliente;

typedef struct carrinho Carrinho;

int maxC(int a, int b);

int alturaC(Clientes * node);

int fatorBalancoC(Clientes * node);

Clientes * rotacaoDirC(Clientes * root);

Clientes * rotacaoEsqC(Clientes * root);

Clientes * criaNoCliente(Clientes * root, char * nome, char * cpf, char * telefone);

Clientes * insereNoCliente(Clientes * root, char * nome, char * cpf, char * telefone);

Clientes * cadastroClientes(Clientes * root, char * nome, char * cpf, char * telefone);

Clientes * inicializarBaseDadosClientes(Clientes * root);

