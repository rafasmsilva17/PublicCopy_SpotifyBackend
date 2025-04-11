#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

typedef struct historico Historico;


Historico* create_historico();

Historico* organizehistorico(char** line);

void free_historico(Historico* historico);

char* get_from_history(Historico* historico, char campo);

#endif