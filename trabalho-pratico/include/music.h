#ifndef MUSIC_H
#define MUSIC_H

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "data_manager.h"
#include "uteis.h"

typedef struct music Music;

char* get_album_name_struct(char* target,Music* music);

//Liberta a memória alocada para uma estrutura de música
void free_music_struct(Music* music);

//Liberta a memória de cada valor na tabela hash de músicas.
void free_music_hash_table();

//Retorna o gênero de uma música
char* get_genre(Music*target);

char* getGenre_struct(char* id,Music* music);

//Calcula o tempo total de duração de uma música em segundos
int get_music_time_struct(char* target,Music* music);

//Retorna os IDs dos artistas de uma música
char** get_music_artist_struct(char* target,Music* music);

//Cria uma nova estrutura de música
Music* create_music();

Music* getMusic (char* id,Music* music);

//Divide uma linha de texto em múltiplos IDs de artistas
char** tokenizeAID (char* line);

//Liberta a memória alocada para uma estrutura de música
void free_music(Music* music);

//Organiza os dados de uma música e insere na tabela hash
Music* organizeMusic_struct(char** line);


#endif