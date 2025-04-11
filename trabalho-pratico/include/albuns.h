#ifndef ALBUNS_H
#define ALBUNS_H

#include <glib.h>

// Ponteiro opaco para o tipo Album
typedef struct album Album;

// Funções de manipulação de álbuns
Album* create_album();
void free_album(Album* album);
Album* organizeAlbum(char** line);

// Funções de acesso aos dados do álbum (se necessário)
const gchar* get_album_id(Album* album);
const gchar* get_album_title(Album* album);
const gchar* get_album_year(Album* album);

#endif