
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
    #include <winbase.h>
#elif __APPLE__
    #include <unistd.h>
#elif __linux__
    #include <unistd.h>
#endif

void intro();

void menuprincipal();

void menucliente();

void menuclienteeditar();

void menumedicamento();

void menumedicamentoeditar();

void menuvendas();

void menuentrega();

int lerOpcao();

int validaNome(char *nome);

int validaCPF(char *cpf);

int validaTelefone(char *telefone);

char *formatarNome(char *nome);

char *formatarCPF(char *cpf);

char *formatarTelefone(char *telefone);

void limpa_tela();

void pressiona_enter();

void limpa_buffer();

void sleep(int tempo);
