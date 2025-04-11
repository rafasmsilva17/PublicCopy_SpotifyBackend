#include <stdlib.h>
#include <stdio.h>
#include "artist.h"
#include "artist.h"
#include "uteis.h"
#include <glib.h>

struct artist{

    gchar artist_id[9];
    gchar* name;
    gchar recipe_per_stream[5];
    gchar** id_constituent;
    gchar* country;
    gchar type[11];
};


gchar* get_artist_id(Artist* artist) {
    return strdup(artist->artist_id);
}

gchar* get_artist_name(Artist* artist) {
    return strdup(artist->name);
}

gchar* get_artist_recipe_per_stream(Artist* artist) {
    return strdup(artist->recipe_per_stream);
}

char** get_artist_id_constituent(Artist* artist, int* size) {
    return get_from_artist_array(artist, size);
}

gchar* get_artist_country(Artist* artist) {
    return strdup(artist->country);
}

gchar* get_artist_type(Artist* artist) {
    return strdup(artist->type);
}



//Cria uma nova estrutura de Artist
Artist* create_artist()
{
    Artist* new = malloc(sizeof(Artist));
    new->name = NULL;
    new->country = NULL;
    new->id_constituent = NULL;
    return new;
}

char** get_from_artist_array(Artist* artist, int* size)
{
    int r = 0;
    if (artist->id_constituent == NULL) return 0;
    while (artist->id_constituent[r] != NULL) r++; // Conta o número de elementos

    char** m = malloc(sizeof(char*) * (r + 1)); 
    for (int i = 0; i < r; i++)
    {
        m[i] = strdup(artist->id_constituent[i]);
    }
    m[r] = NULL; 
    *size = r; 
    
    return m;
}



//Liberta a memória alocada para uma estrutura de Artist
void free_artist(Artist* artist) {
    if (artist != NULL) {
        g_free(artist->name);
        g_free(artist->country);      
        char** tokens = artist->id_constituent;
        if (tokens != NULL) {
            for (size_t i = 0; tokens[i] != NULL; ++i) {
                g_free(tokens[i]);  // Libera cada string alocada
                tokens[i]=NULL;
            }
            free(tokens);  // Libera o array de ponteiros
            tokens = NULL;
        }
        g_free(artist);
    }
}

//Organiza os dados de um artista e insere na tabela hash
Artist* organizeArtist (char** line)
{
    Artist* artist = create_artist();
    strcpy(artist->artist_id, line[0]);
    artist->name = strdup(line[1]);
    strcpy(artist->recipe_per_stream, line[3]);
    artist->id_constituent = tokenize(line[4]);
    artist->country = strdup(line[5]);
    strcpy(artist->type, line[6]);
    return artist;
}