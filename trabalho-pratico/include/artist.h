#ifndef ARTIST_H
#define ARTIST_H

#include <stdlib.h>
#include <stdio.h>
#include "artist_manager.h"
#include "uteis.h"
#include <glib.h>

typedef struct artist Artist;


gchar* get_artist_id(Artist* artist);

gchar* get_artist_name(Artist* artist) ;

gchar* get_artist_recipe_per_stream(Artist* artist);

char** get_artist_id_constituent(Artist* artist, int* size);

gchar* get_artist_country(Artist* artist) ;

gchar* get_artist_type(Artist* artist);




char** get_from_artist_array(Artist* artist, int* size);


//Cria uma nova estrutura de Artist
Artist* create_artist();


//Divide uma linha de texto em múltiplos tokens, com base na vírgula
char** tokenizeIDc(char* line);



//Liberta a memória alocada para uma estrutura de Artist
void free_artist(Artist* artist);

//Organiza os dados de um artista e insere na tabela hash
Artist* organizeArtist (char** line);

#endif