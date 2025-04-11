#ifndef STATS_H
#define STATS_H

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "estatisticas.h"
#include "music.h"
#include "user.h"
#include "user_manager.h"
#include <time.h>


//q3

void init_genrelikesT_table();

typedef struct genreInfo GenreInfo;

typedef struct idadeInfo  Idadeinfo;

void free_Idadeinfo (Idadeinfo* idadeinfo);

void free_gl_hash_table() ;

Idadeinfo*  info_from_age(int age);

char* genre_from_Info(int i,int age);

int numLikes_from_Info(int i, int age);



GenreInfo* initGI(char* genre) ;

Idadeinfo* init_info(int age, char* genre) ;

//Organiza os dados de gênero e incrementa os likes ou cria um novo registro
void organizeGenre(char* genre, int age);

void organizaGenreLikes();

//q6 

typedef struct music_hist_stat Music_hist_stat;

typedef struct user_history User_history;

int calc_dur(char* dur);

int year_ts (char* ts);

void init_years_array(int* array);

void init_user_hist_table ();

void free_user_hist_hash_table();

void organize_hist_aux(char* user_id, char* musicid, char* time_stamp, int duration);

void organize_user_hist ();

char* list_time_from_user(char* user_id,int year);

int num_time_list_from_user(char* use_id, int year);

int hora_mais_ouvida (char* user_id,int year);

int hour_ts (char* ts);

char* artista_mais_ouvido(char* user_id, int year);

char* genero_mais_ouvido(char* user_id, int year);

char* data_com_mais_musicas_ouvidas(char* user_id, int year);

char* album_mais_ouvido(char* user_id, int year);

typedef struct artistDuration ArtistDuration;

char** get_x_most_listened_artists(char* user_id, int year, int x, int* result_count);

int compare_artist_duration(gconstpointer a, gconstpointer b) ;

void free_artist_duration(ArtistDuration* ad);


int get_duration_listened_by_artist(char* user_id, int year, char* artist_name) ;

int get_number_of_songs_listened_by_artist(char* user_id, int year, char* artist_name) ;

void format_duration(int seconds, char *formatted_time);

//-------------------------Q5-------------------------


#define NUM_GENEROS 10

// Nome dos gêneros
extern char* GENEROS[];

extern GHashTable* user_index_map;
extern GHashTable* genre_index_map;

// Inicialização e destruição
void init_genre_index_map();
void create_user_genre_matrix();
void free_user_genre_matrix();

// Acesso aos dados
int** get_matriz_classificacao();
char** get_ids_utilizadores();
int get_num_users();
int get_num_generos();

void print_10_elements();

#endif
