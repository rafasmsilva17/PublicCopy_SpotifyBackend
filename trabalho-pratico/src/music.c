#include <stdlib.h>
#include <stdio.h>
#include "music.h"
#include <glib.h>
#include "data_manager.h"
#include "uteis.h"



typedef struct music{

    char* music_id;
    char* title;
    char** artist_id;
    char* album_id;
    char* duration;
    char* genre;
    char* year;
} Music;


//Liberta a memória alocada para uma estrutura de música
void free_music_struct(Music* music) {
    
    if (music == NULL) return;

    if (music->music_id) free(music->music_id);
    if (music->title) free(music->title);

    if (music->artist_id != NULL) {
        for (int i = 0; music->artist_id[i] != NULL; i++) {
            free(music->artist_id[i]);
        }
        free(music->artist_id);
    }

    if (music->duration) free(music->duration);
    if (music->genre) free(music->genre);
    if (music->album_id) free(music->album_id);
    if (music->year) free(music->year);

    free(music);
}


char* getGenre_struct(char* id,Music* music){
    
    if(music == NULL) return NULL;
    char* genre = strdup(music->genre);
    return genre;
}


//Retorna o gênero de uma música
char* get_genre(Music*target)
{
    return strdup(target->genre);
}


//Calcula o tempo total de duração de uma música em segundos
int get_music_time_struct(char* target,Music* music)
{
    int horas,minutos,segundos;
    int time= 0;
    sscanf(music->duration,"%2d:%2d:%2d", &horas, &minutos, &segundos);
    time = (horas * 3600) + (minutos * 60) + segundos;
    return time;
}

//Retorna os IDs dos artistas de uma música
char** get_music_artist_struct(char* target,Music* music)
{
    if (music == NULL || music->artist_id == NULL) {
        return NULL; // Return NULL if no match
    }

    int count = 0;
    while (music->artist_id[count] != NULL) {
        count++;
    }

    char** result = malloc((count + 1) * sizeof(char*));
    for (int i = 0; i < count; i++) {
        result[i] = strdup(music->artist_id[i]); 
    }
    result[count] = NULL;

    return result;
}

char* get_album_name_struct(char* target,Music* music){
    
    return strdup(music->album_id);
}

//Cria uma nova estrutura de música
Music* create_music()
{
    Music* new = malloc(sizeof(Music));
    new->music_id = NULL;
    new->title = NULL;
    new->artist_id = NULL;
    new->album_id = NULL;
    new->duration = NULL;
    new->genre = NULL;
    new->year = NULL;
    return new;
}


//Organiza os dados de uma música e insere na tabela hash
Music* organizeMusic_struct(char** line){
    
    Music* music = create_music();
    music->music_id = strdup(line[0]);
    music->title = strdup(line[1]);
    music->artist_id = tokenize(line[2]);
    music->album_id = strdup(line[3]);
    music->duration = strdup(line[4]);
    music->genre = strdup(line[5]);
    music->year = strdup(line[6]);

    return music;

}