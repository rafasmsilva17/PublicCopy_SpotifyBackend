#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <historico_manager.h>


typedef struct historico{
    gchar user_id[9];
    gchar music_id[9];
    gchar timestamp[20];
    gchar duration[9];
}Historico;


Historico* create_historico()
{
    Historico* new = malloc(sizeof(Historico));
    return new;
}


Historico* organizehistorico(char** line) 
{
    Historico* historico = create_historico();
    strcpy(historico->user_id, line[1]);
    strcpy(historico->music_id, line[2]);
    strcpy(historico->timestamp,line[3]);
    strcpy(historico->duration,line[4]);
    return historico;
}

void free_historico(Historico* historico) {
    if (historico != NULL) {
        g_free(historico);
    }
}

char* get_from_history(Historico* hist, char x)
{
    switch (x) {
        case 'u':
        return strdup(hist->user_id);
        case 'm':
        return strdup(hist->music_id);
        case 't':
        return strdup(hist->timestamp);
        case 'd':
        return strdup(hist->duration);
        default:
        return NULL;
    }
}
