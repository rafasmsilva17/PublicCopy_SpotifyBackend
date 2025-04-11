#ifndef DISCOGRAFIA_MANAGER
#define DISCOGRAFIA_MANAGER

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "discografia.h"

void init_artist_disc_table();

GList *get_discografias();

// Função comparadora para ordenar discos de artistas com base no tempo total de forma decrescente
int compare_discographies(gconstpointer a, gconstpointer b);

void free_disc(Artist_disc *disc);

void free_disc_hash_table();

void organize_discografia();

#endif