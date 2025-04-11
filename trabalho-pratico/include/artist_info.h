#ifndef ARTIST_INFO
#define ARTIST_INFO

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "music_manager.h"
#include "artist_manager.h"

typedef struct artist_info Artist_info;

typedef struct a_inc A_inc;

Artist_info *create_artist_info_struct(char *id, char *musica);

void free_artistinfo_struct(Artist_info *artinf);

double get_rate_num(Artist_info* r1);

int get_artist_num_albuns_struct(Artist_info *r );

void set_add_receita(Artist_info* r2, double num, int size);

void add_num_albuns_insert(Artist_info* art, char* musica);

char* get_a_i_id(Artist_info* r);

int insert_albuns(GHashTable *albuns, char *id);

double get_artist_receita_struct(Artist_info *r);

void free_album_info(gpointer key, gpointer value, gpointer user_data);

void free_artist_info(gpointer key, gpointer value, gpointer user_data);


#endif