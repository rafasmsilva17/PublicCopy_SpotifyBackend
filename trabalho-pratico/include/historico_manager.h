#ifndef HISTORICO_MANAGER_H
#define HISTORICO_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "historico.h"

void init_hashtable_historico();

void organizeHist(char** line);

void free_historico_entry(gpointer key, gpointer value, gpointer historico_data);

void free_historico_hash_table() ;

GList* getKeys_hist();

char* get_from_hist(char* id, char campo);

#endif