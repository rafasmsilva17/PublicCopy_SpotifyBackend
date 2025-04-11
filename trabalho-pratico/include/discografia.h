#ifndef DISCOGRAFIA
#define DISCOGRAFIA

typedef struct artist_disc Artist_disc;

// Retorna o ID de um disco de artista
char *get_artist_id_disc(Artist_disc *target);

// Retorna o tempo total de um disco de artista
int get_artist_total_time_disc(Artist_disc *target);

// Cria uma nova estrutura de Artist_disc
Artist_disc *create_disc(char *id, int time);

// Adiciona um tempo extra ao tempo total de um disco de artista
void soma_tempo_disc(Artist_disc *target, int time);

#endif