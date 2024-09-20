#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct dadoscliente Dadoscliente;

typedef struct cliente Cliente;

int max(int a, int b);

int altura(Cliente * node);

int fatorBalanco(Cliente * node);

Cliente * rotacaoDir(Cliente * root);

Cliente * rotacaoEsq(Cliente * root);

Cliente * criaNo(Cliente * root, char * nome, char * cpf, char * endereco, char * telefone);

Cliente * insereNo(Cliente * root, char * nome, char * cpf, char * endereco, char * telefone);

Cliente * cadastroCliente(Cliente * root, char * nome, char * cpf, char * endereco, char * telefone);

Cliente * inicializarBaseDados(Cliente * root);