#ifndef UTEIS_H
#define UTEIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void recuar_string(char* str, int indice);

char** tokenize(char* line);

void free_tokens(char** tokens);

double duas_casas_decimais(double value);

#endif