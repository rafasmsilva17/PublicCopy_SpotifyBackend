#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "albuns.h"
#include "uteis.h"

struct album {
    gchar id[9];
    gchar* title;
    gchar** artists_id;
    gchar* year;
    gchar** producers;
};

// Função para criar um novo álbum
Album* create_album() {
    Album* new = malloc(sizeof(Album));
    new->title = NULL;
    new->artists_id = NULL;
    new->year = NULL;
    new->producers = NULL;
    return new;
}

// Função para organizar um álbum a partir de uma linha de dados
Album* organizeAlbum(char** line) {
    Album* album = create_album();
    strcpy(album->id, line[0]);
    album->title = strdup(line[1]);
    album->artists_id = tokenize(line[2]);
    album->year = strdup(line[3]);
    album->producers = tokenize(line[4]);
    return album;
}

// Função para liberar memória de um álbum
void free_album(Album* album) {
    if (album != NULL) {
        g_free(album->title);
        g_free(album->year);
        free_tokens(album->artists_id);
        free_tokens(album->producers);
        g_free(album);
    }
}

// Funções de acesso aos dados do álbum
const gchar* get_album_id(Album* album) {
    return album->id;
}

const gchar* get_album_title(Album* album) {
    return album->title;
}

const gchar* get_album_year(Album* album) {
    return album->year;
}
