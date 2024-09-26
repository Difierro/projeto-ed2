#include "..\src\medicamentos.c"
#include "..\src\clientes.c"


#ifndef MENU_FUNCOES_C
#define MENU_FUNCOES_C
#include "..\src\menu_funcoes.c"
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Clientes * cadastrar_cliente(Clientes * root);

Medicamento * cadastrar_medicamento(Medicamento * root);

Clientes * buscar_cliente(Clientes * root);

Medicamento * buscar_medicamento(Medicamento * root);

