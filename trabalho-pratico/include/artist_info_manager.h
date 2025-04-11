#ifndef ARTIST_INFO_MANAGER
#define ARTIST_INFO_MANAGER

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "artist_info.h"
#include "music_manager.h"
#include "artist_manager.h"


void init_info_ht();

void free_artistinfo_hash_table();

double get_artist_receita(char *id);

void calculate_band(char *id);

void create_artist_info(char *id, char *musica);

int get_artist_num_albuns(char *id);

void organize_artist_info();

void cleanup_artist_band_info();


#endif
