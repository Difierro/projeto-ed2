#include "..\src\medicamentos.c"
#include "..\src\menu_funcoes.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct clientes Clientes;

typedef struct infocliente Infocliente;

typedef struct carrinho Carrinho;

int maxC(int a, int b);

int alturaC(Clientes * node);

int fatorBalancoC(Clientes * node);

Clientes * menorNoCliente(Clientes * root);

Clientes * rotacaoDirC(Clientes * root);

Clientes * rotacaoEsqC(Clientes * root);

Clientes * criaNoCliente(Clientes * root, char * nome, char * cpf, char * telefone);

Clientes * insereNoCliente(Clientes * root, char * nome, char * cpf, char * telefone);

Clientes * cadastroClientes(Clientes * root, char * nome, char * cpf, char * telefone);

void reescreverarquivoClientes(Clientes * root, FILE * data);

Clientes * inicializarBaseDadosClientes(Clientes * root);

Clientes * buscaCliente(Clientes * root, char * cpf);

Clientes * removerCliente(Clientes * root, char * cpf);
