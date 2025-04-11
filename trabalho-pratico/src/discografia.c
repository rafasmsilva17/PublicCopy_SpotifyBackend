#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct artist_disc{
    char id[9];
    int total_time;
} Artist_disc;


//Retorna o ID de um disco de artista
char* get_artist_id_disc(Artist_disc* target)
{
    return target->id;
}

//Retorna o tempo total de um disco de artista
int  get_artist_total_time_disc(Artist_disc* target)
{
    return target->total_time;
}

//Cria uma nova estrutura de Artist_disc
Artist_disc* create_disc(char* id, int time)
{
    Artist_disc* new = malloc(sizeof(Artist_disc));
    strcpy(new->id, id);
    new->total_time = time;
    return new;
}

//Adiciona um tempo extra ao tempo total de um disco de artista
void soma_tempo_disc(Artist_disc* target, int time)
{
    target->total_time += time;
}
