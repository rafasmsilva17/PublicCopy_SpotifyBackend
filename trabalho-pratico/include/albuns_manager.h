#ifndef ALBUM_MANAGER_H
#define ALBUM_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <albuns.h>

void init_hashtable_album();

void organizeAlb(char** line);

void free_album_entry(gpointer key, gpointer value, gpointer historico_data);


void free_album_hash_table();

int album_exists (char *id);

#endif