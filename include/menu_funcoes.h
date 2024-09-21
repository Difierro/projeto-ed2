#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
#elif __APPLE__
    #include <unistd.h>
#elif __linux__
    #include <unistd.h>
#endif

void intro();

void menu();

int lerOpcao();

int validaNome(char *nome);

void limpa_tela();

void pressiona_enter();

void sleep(int tempo);