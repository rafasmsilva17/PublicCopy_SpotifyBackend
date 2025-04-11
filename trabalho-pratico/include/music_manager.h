#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "music.h"

void init_hashtable_music();

int music_exists(const char* song_id);

GList* get_keys_music_hash_table();

void free_music_hash_table() ;

char** get_music_artist(char* target);

int get_music_time(char* target);

char* getGenre(char* id);

char* get_album_name(char* target);

void organizeMusic(char** line);

#endif