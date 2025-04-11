#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "estatisticas.h"
#include "music_manager.h"
#include "user.h"
#include "user_manager.h"
#include "artist_manager.h"
#include <time.h>


//q3

GHashTable* genreLikes_table = NULL;

void init_genrelikesT_table(){
    genreLikes_table = g_hash_table_new(g_int_hash, g_int_equal);
}

typedef struct genreInfo{
    char genre[30];
    int num_likes;
} GenreInfo;

typedef struct idadeInfo{
    int age;
    GenreInfo genres[10];
} Idadeinfo;



void free_Idadeinfo (Idadeinfo* idadeinfo){
    if(idadeinfo) free(idadeinfo);
}

void free_gl_hash_table() {
    GList* keys = g_hash_table_get_keys(genreLikes_table);
    GList* iter = keys;
    while (iter != NULL) {
        char* key = (char*)iter->data;
        Idadeinfo* idade_info = g_hash_table_lookup(genreLikes_table, key);
        free(key);  
        free_Idadeinfo(idade_info);
        iter = iter->next;
    }
    g_list_free(keys);
    g_hash_table_destroy(genreLikes_table);
}


Idadeinfo*  info_from_age(int age){
    return (Idadeinfo*) g_hash_table_lookup(genreLikes_table,&age);
}



char* genre_from_Info(int i,int age){
    Idadeinfo* info = (Idadeinfo*) g_hash_table_lookup(genreLikes_table,&age);
    if(info != NULL){
        
        return info->genres[i].genre;
        
    }
    return NULL;
}

int numLikes_from_Info(int i, int age){
    Idadeinfo* info = (Idadeinfo*) g_hash_table_lookup(genreLikes_table,&age);
    if(info != NULL){
        return info->genres[i].num_likes;
    }
    return 0;
}



GenreInfo* initGI(char* genre) {
    GenreInfo* new_genre = malloc(sizeof(GenreInfo));
    if (!new_genre) {
        fprintf(stderr, "Memory allocation failed for GenreInfo.\n");
        exit(1);
    }
    strncpy(new_genre->genre, genre, sizeof(new_genre->genre) - 1);
    new_genre->genre[sizeof(new_genre->genre) - 1] = '\0'; 
    new_genre->num_likes = 0;
    return new_genre;
}

Idadeinfo* init_info(int age, char* genre) {
    Idadeinfo* new_info = malloc(sizeof(Idadeinfo));
    if (!new_info) {
        fprintf(stderr, "Memory allocation failed for Idadeinfo.\n");
        exit(1);
    }
    new_info->age = age;
    for (int i = 0; i < 10; i++) {
        if (i == 0) {
            
            strncpy(new_info->genres[i].genre, genre, sizeof(new_info->genres[i].genre) - 1);
            new_info->genres[i].genre[sizeof(new_info->genres[i].genre) - 1] = '\0';
            new_info->genres[i].num_likes = 1;
        } else {
            
            new_info->genres[i].genre[0] = '\0';
            new_info->genres[i].num_likes = 0;
        }
    }
    return new_info;
}

//Organiza os dados de gênero e incrementa os likes ou cria um novo registro
void organizeGenre(char* genre, int age) {
    // Look for the age group in the hash table
    Idadeinfo* age_info = (Idadeinfo*)g_hash_table_lookup(genreLikes_table, &age);
    
    if (age_info == NULL) {
        age_info = init_info(age, genre);
        int* age_key = g_memdup2(&age, sizeof(int));
        g_hash_table_insert(genreLikes_table, age_key, age_info);
    } else {
        

        for (int i = 0; i < 10; i++) {
            if (strcmp(age_info->genres[i].genre, genre) == 0) {
                age_info->genres[i].num_likes++;
                return;
            } else if (age_info->genres[i].genre[0] == '\0') {
                strncpy(age_info->genres[i].genre, genre, sizeof(age_info->genres[i].genre) - 1);
                age_info->genres[i].genre[sizeof(age_info->genres[i].genre) - 1] = '\0';
                age_info->genres[i].num_likes = 1;
                return;
            }
        }
        printf("No space to add new genre '%s' for age group %d\n", genre, age);
    }
}



void organizaGenreLikes() {
    GList* keys = get_keys_user_hash_table();
    if (keys == NULL) {
        printf("Tabela de users está vazia\n");
        return;
    }

    init_genrelikesT_table();

    for (GList* key_cop = keys; key_cop != NULL; key_cop = key_cop->next) {
        char* user_id = (char*)key_cop->data;

        char age_str[12]; 
        char* age_str_result = get_from_u(user_id, 'b', age_str);

        int age = atoi(age_str_result);
        if (age_str_result != age_str) {
            free(age_str_result); 
        }

        char** liked_musics = get_from_u_lm(user_id);
        if (liked_musics) {
            for (int i = 0; liked_musics[i] != NULL; i++) {
                char* genre = getGenre(liked_musics[i]);
                if (genre) {
                    organizeGenre(genre, age);
                    free(genre);
                }
            }
            free_user_likedMusics(liked_musics);
        }
    }

    g_list_free(keys); 
}

//q6

typedef struct music_hist_stat {
    char* music_id;
    char* genre;
    int num_ts;
    int num_listened_per_year [25];
    int duration_per_year [25];
    char** time_stamps;
} Music_hist_stat;

typedef struct user_history {
    char* user_id;
    Music_hist_stat* music_stats; 
    int num_music_stats;          
} User_history;

int calc_dur(char* dur){
    int hour,min,seg;
    sscanf(dur, "%2d:%2d:%2d", &hour, &min, &seg);
    return (hour*3600+min*60+seg);
}

int year_ts (char* ts){
    int year,month,day,hour,min,seg;
    sscanf(ts, "%4d-%2d-%2d %2d:%2d:%2d",&year,&month,&day,&hour,&min,&seg);
    return year;
}

void init_years_array(int* array){
    for (int i = 0; i < 25; i++){
        array[i] = 0;
    }
}

GHashTable* user_hist_table = NULL;

void init_user_hist_table (){
    user_hist_table = g_hash_table_new(g_str_hash, g_str_equal);
}

void free_user_hist_hash_table(){
    if (user_hist_table == NULL) return; 

    GList* keys = g_hash_table_get_keys(user_hist_table); 
    for (GList* iter = keys; iter != NULL; iter = iter->next) {
        char* user_id = (char*)iter->data; 
        User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);

        if (user_hist != NULL) {
            if (user_hist->music_stats != NULL) {
                for (int i = 0; i < user_hist->num_music_stats; i++) {
                    if (user_hist->music_stats[i].music_id != NULL)
                        g_free(user_hist->music_stats[i].music_id);
                    if (user_hist->music_stats[i].genre != NULL)
                        g_free(user_hist->music_stats[i].genre);
                    if (user_hist->music_stats[i].time_stamps != NULL) {
                        for (int j = 0; j < user_hist->music_stats[i].num_ts; j++) {
                            if (user_hist->music_stats[i].time_stamps[j] != NULL)
                                g_free(user_hist->music_stats[i].time_stamps[j]);
                        }
                        g_free(user_hist->music_stats[i].time_stamps);
                    }
                }
                g_free(user_hist->music_stats);  
            }

            if (user_hist->user_id != NULL)
                g_free(user_hist->user_id); 
            
            g_free(user_hist);  
        }

        g_free(user_id);  
    }

    g_list_free(keys);  
    g_hash_table_destroy(user_hist_table); 
    user_hist_table = NULL; 
}


void organize_hist_aux(char* user_id, char* musicid, char* time_stamp, int duration) {
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);
    
    if (user_hist == NULL) {
        user_hist = g_malloc(sizeof(User_history));
        user_hist->user_id = g_strdup(user_id);

        user_hist->music_stats = g_malloc(sizeof(Music_hist_stat));
        user_hist->num_music_stats = 1;
        
        user_hist->music_stats[0].music_id = g_strdup(musicid);
        user_hist->music_stats[0].genre = (getGenre(musicid));
        user_hist->music_stats[0].num_ts = 1;
        user_hist->music_stats[0].time_stamps = g_malloc(sizeof(char*));
        user_hist->music_stats[0].time_stamps[0] = g_strdup(time_stamp);
        int year = year_ts(time_stamp);
        init_years_array(user_hist->music_stats[0].num_listened_per_year);
        user_hist->music_stats[0].num_listened_per_year[year-2000] = 1;
        init_years_array(user_hist->music_stats[0].duration_per_year );
        user_hist->music_stats[0].duration_per_year[year-2000] = duration;
        g_hash_table_insert(user_hist_table, g_strdup(user_id), user_hist);

    } else {
        Music_hist_stat* music_stats = user_hist->music_stats;
        int num_music_stats = user_hist->num_music_stats;
        int i;

        for (i = 0; i < num_music_stats; i++) {
            if (strcmp(music_stats[i].music_id, musicid) == 0) {
                break;
            }
        }

        if (i == num_music_stats) {
            num_music_stats++;
            user_hist->music_stats = g_realloc(user_hist->music_stats, num_music_stats * sizeof(Music_hist_stat));
            music_stats = user_hist->music_stats;

            music_stats[i].music_id = g_strdup(musicid);
            music_stats[i].genre = (getGenre(musicid));
            music_stats[i].num_ts = 1;
            music_stats[i].time_stamps = g_malloc(sizeof(char*));
            music_stats[i].time_stamps[0] = g_strdup(time_stamp);
            int year = year_ts(time_stamp);
            music_stats[i].num_listened_per_year[year-2000] = 1;
            music_stats[i].duration_per_year[year-2000] = duration;
            user_hist->music_stats = music_stats;
            user_hist->num_music_stats = num_music_stats;
        } else {
            
            music_stats[i].num_ts++;
            music_stats[i].time_stamps = g_realloc(music_stats[i].time_stamps, music_stats[i].num_ts * sizeof(char*));
            music_stats[i].time_stamps[music_stats[i].num_ts - 1] = g_strdup(time_stamp);
            int year = year_ts(time_stamp);
            music_stats[i].num_listened_per_year[year-2000]++;
            music_stats[i].duration_per_year[year-2000] += duration;
            
        }
    }
}


void organize_user_hist() {
    if (user_hist_table == NULL) {
        init_user_hist_table(); 
    }
    
    GList* keys = getKeys_hist();
    if (keys == NULL) {
        return;
    }

    for (GList* key_cop = keys; key_cop != NULL; key_cop = key_cop->next) {
        char* hist_id = (char*)key_cop->data;
        char* user_id = get_from_hist(hist_id, 'u');
        char* music_id = get_from_hist(hist_id, 'm');
        char* dur = get_from_hist(hist_id, 'd');
        char* time_stamp = get_from_hist(hist_id, 't');
        int duration = calc_dur(dur);

        organize_hist_aux(user_id, music_id, time_stamp, duration);
        free(user_id);
        free(music_id);
        free(dur);
        free(time_stamp);
    }
    g_list_free(keys);
}


char* list_time_from_user(char* user_id, int year) {
    
    int sum = 0;
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);

    if (user_hist == NULL) {
        
        return NULL; 
    }

    int year_index = year - 2000;

    for (int i = 0; i < user_hist->num_music_stats; i++) {
        if (year_index >= 0 && year_index < 25) { 
            for(int j=0;j<user_hist->music_stats[i].num_ts;j++){
                if(year_ts(user_hist->music_stats[i].time_stamps[j]) == year) sum += user_hist->music_stats[i].duration_per_year[year_index];
            }
            
        }
    }
    
    int hour = sum/3600;
    int minute = (sum%3600)/60;
    int second = sum%60;
    char buffer[32]; 
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hour,minute,second);
    return g_strdup(buffer);
}

int num_time_list_from_user(char* use_id, int year){
    int sum = 0;
    User_history* user_hist = g_hash_table_lookup(user_hist_table, use_id);
    if (user_hist == NULL) {
        return 0; 
    }
    int year_index = year - 2000;
    for (int i = 0; i < user_hist->num_music_stats; i++)
    {
        if (year_index >= 0 && year_index < 25)
        {

            for(int j=0;j<user_hist->music_stats[i].num_ts;j++){
                if(year_ts(user_hist->music_stats[i].time_stamps[j]) == year) sum += user_hist->music_stats[i].num_listened_per_year[year_index];
            }
        }
    }
    return sum;
}

int hour_ts (char* ts){
    
    int year,month,day,hour,min,seg;
    sscanf(ts, "%4d/%2d/%2d %2d:%2d:%2d",&year,&month,&day,&hour,&min,&seg);
    return hour;
}

int hora_mais_ouvida(char* user_id, int year) {
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);
    if (user_hist == NULL) {
       
        return 0; 
    }

    int hours [24] = {0};
    int year_index = year - 2000;

    for (int i = 0; i < user_hist->num_music_stats; i++) {
        for (int j = 0; j < user_hist->music_stats[i].num_ts; j++) {
            if (year_index >= 0 && year_index < 25) {
                if(year_ts(user_hist->music_stats[i].time_stamps[j])==year){
                    int hour = hour_ts(user_hist->music_stats[i].time_stamps[j]);          
                    hours[hour]++;
                }
            }
        }
    }
    int max = -1;
    for(int i=0;i<24;i++){
        if(hours[i]>max){
            max = i;
        }
    }
    return max;
}

char* artista_mais_ouvido(char* user_id, int year) {
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);
    if (user_hist == NULL) {
        return NULL;
    }

    GHashTable* artist_duration_table = g_hash_table_new(g_str_hash, g_str_equal);
    int year_index = year - 2000;

    for (int i = 0; i < user_hist->num_music_stats; i++) {
        if (year_index >= 0 && year_index < 25) {
            for(int j=0;j<user_hist->music_stats[i].num_ts;j++){
                if(year_ts(user_hist->music_stats[i].time_stamps[j]) == year) {
                    char** artists = get_music_artist(user_hist->music_stats[i].music_id);
                    int duration = user_hist->music_stats[i].duration_per_year[year_index];

                    for (int j = 0; artists[j] != NULL; j++) {
                        char* artist = artists[j];

                        if (g_hash_table_contains(artist_duration_table, artist)) {
                            int* total_duration = g_hash_table_lookup(artist_duration_table, artist);
                            *total_duration += duration;
                        } else {
                            int* total_duration = g_malloc(sizeof(int));
                            *total_duration = duration;
                            g_hash_table_insert(artist_duration_table, g_strdup(artist), total_duration);
                        }
                    }


                    g_strfreev(artists);
                }
            }
        }
    }

    GList* keys = g_hash_table_get_keys(artist_duration_table);
    char* most_listened_artist = NULL;
    int max_duration = 0;

    for (GList* iter = keys; iter != NULL; iter = iter->next) {
        char* artist = iter->data;
        int* duration = g_hash_table_lookup(artist_duration_table, artist);
        
        if (*duration > max_duration) {
            max_duration = *duration;
            most_listened_artist = artist;
        }
    }

    g_list_free(keys);
    g_hash_table_destroy(artist_duration_table);

    if (most_listened_artist != NULL) {
        return g_strdup(most_listened_artist);
    }

    
    return NULL;
}

char* genero_mais_ouvido(char* user_id, int year) {
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);
    if (user_hist == NULL) {
        return NULL;
    }

    GHashTable* genre_duration_table = g_hash_table_new(g_str_hash, g_str_equal);
    int year_index = year - 2000;

    for (int i = 0; i < user_hist->num_music_stats; i++) {
        if (year_index >= 0 && year_index < 25) {
            for(int j=0;j<user_hist->music_stats[i].num_ts;j++){
                if(year_ts(user_hist->music_stats[i].time_stamps[j]) == year) {
                    char* genre = user_hist->music_stats[i].genre;
                    int duration = user_hist->music_stats[i].duration_per_year[year_index];

                    if (g_hash_table_contains(genre_duration_table, genre)) {
                        int* total_duration = g_hash_table_lookup(genre_duration_table, genre);
                        *total_duration += duration;
                    } else {
                        int* total_duration = g_malloc(sizeof(int));
                        *total_duration = duration;
                        g_hash_table_insert(genre_duration_table, g_strdup(genre), total_duration);
                    }
                }
            }
        }
    }

    GList* keys = g_hash_table_get_keys(genre_duration_table);
    char* most_listened_genre = NULL;
    int max_duration = 0;

    for (GList* iter = keys; iter != NULL; iter = iter->next) {
        char* genre = iter->data;
        int* duration = g_hash_table_lookup(genre_duration_table, genre);

        if (*duration > max_duration || 
           (*duration == max_duration && (most_listened_genre == NULL || strcmp(genre, most_listened_genre) < 0))) {
            max_duration = *duration;
            most_listened_genre = genre;
        }
    }

    g_list_free(keys);
    g_hash_table_destroy(genre_duration_table);

    if (most_listened_genre != NULL) {
        return g_strdup(most_listened_genre);
    }

    return NULL;
}
char* data_com_mais_musicas_ouvidas(char* user_id, int year) {
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);
    if (user_hist == NULL) {
        return NULL;
    }

    GHashTable* date_count_table = g_hash_table_new(g_str_hash, g_str_equal);
    int year_index = year - 2000;

    // Iterar sobre as estatísticas de músicas e agrupar os timestamps por data
    for (int i = 0; i < user_hist->num_music_stats; i++) {
        if (year_index >= 0 && year_index < 25) {
            for (int j = 0; j < user_hist->music_stats[i].num_ts; j++) {
                char* timestamp = user_hist->music_stats[i].time_stamps[j];
                int ts_year = year_ts(timestamp);

                if (ts_year == year) {
                    // Extrair a parte da data do timestamp (ex: "YYYY-MM-DD")
                    char date[11];
                    strncpy(date, timestamp, 10);
                    date[10] = '\0';

                    if (g_hash_table_contains(date_count_table, date)) {
                        int* count = g_hash_table_lookup(date_count_table, date);
                        (*count)++;
                    } else {
                        int* count = g_malloc(sizeof(int));
                        *count = 1;
                        g_hash_table_insert(date_count_table, g_strdup(date), count);
                    }
                }
            }
        }
    }

    // Encontrar a data com o maior número de músicas ouvidas
    GList* keys = g_hash_table_get_keys(date_count_table);
    char* most_listened_date = NULL;
    int max_count = 0;

    for (GList* iter = keys; iter != NULL; iter = iter->next) {
        char* date = iter->data;
        int* count = g_hash_table_lookup(date_count_table, date);

        // Desempate: Se o número de músicas for o mesmo, escolhe a data mais recente
        if (*count > max_count || 
            (*count == max_count && (most_listened_date == NULL || strcmp(date, most_listened_date) > 0))) {
            max_count = *count;
            most_listened_date = date;
        }
    }

    g_list_free(keys);
    g_hash_table_destroy(date_count_table);

    if (most_listened_date != NULL) {
        return g_strdup(most_listened_date);
    }

    return NULL;
}

char* album_mais_ouvido(char* user_id, int year) {
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);
    if (user_hist == NULL) {
        return NULL; 
    }

    GHashTable* album_count_table = g_hash_table_new(g_str_hash, g_str_equal);
    int year_index = year - 2000;

    // Iterar sobre as músicas e agrupar os álbuns por contagem de vezes ouvidas
    for (int i = 0; i < user_hist->num_music_stats; i++) {
        if (year_index >= 0 && year_index < 25) {
            for (int j = 0; j < user_hist->music_stats[i].num_ts; j++) {
                char* timestamp = user_hist->music_stats[i].time_stamps[j];
                int ts_year = year_ts(timestamp);

                if (ts_year == year) {
                    // Obter o ID do álbum para a música atual
                    char* album_id = get_album_name(user_hist->music_stats[i].music_id);

                    if (g_hash_table_contains(album_count_table, album_id)) {
                        int* count = g_hash_table_lookup(album_count_table, album_id);
                        (*count)++;
                    } else {
                        int* count = g_malloc(sizeof(int));
                        *count = 1;
                        g_hash_table_insert(album_count_table, g_strdup(album_id), count);
                    }
                }
            }
        }
    }

    // Encontrar o álbum com o maior número de vezes ouvido (com desempate alfabético)
    GList* keys = g_hash_table_get_keys(album_count_table);
    char* most_listened_album = NULL;
    int max_count = 0;

    for (GList* iter = keys; iter != NULL; iter = iter->next) {
        char* album_id = iter->data;
        int* count = g_hash_table_lookup(album_count_table, album_id);

        // Desempate: Se o número de vezes ouvidas for o mesmo, escolhe o album com ID lexicograficamente menor
        if (*count > max_count || 
            (*count == max_count && (most_listened_album == NULL || strcmp(album_id, most_listened_album) < 0))) {
            max_count = *count;
            most_listened_album = album_id;
        }
    }

    g_list_free(keys);
    g_hash_table_destroy(album_count_table);

    if (most_listened_album != NULL) {
        return g_strdup(most_listened_album);
    }

    return NULL;
}

typedef struct artistDuration{
    char* artist;
    int duration;
} ArtistDuration;



char** get_x_most_listened_artists(char* user_id, int year, int x, int* result_count) {
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);
    if (user_hist == NULL) {
        *result_count = 0;
        return NULL; 
    }

    GHashTable* artist_duration_table = g_hash_table_new(g_str_hash, g_str_equal);
    int year_index = year - 2000;

    for (int i = 0; i < user_hist->num_music_stats; i++) {
        if (year_index >= 0 && year_index < 25) {
            char** artists = get_music_artist(user_hist->music_stats[i].music_id);
            for (int j = 0; artists[j] != NULL; j++) {
                
            }
            if (artists == NULL) {
                continue;
            }
            for(int j=0;j<user_hist->music_stats[i].num_ts;j++){
                if(year_ts(user_hist->music_stats[i].time_stamps[j]) == year) {
                    int duration = user_hist->music_stats[i].duration_per_year[year_index];
                    if(duration == 0) continue;

                    for (int j = 0; artists[j] != NULL; j++) {
                        char* artist = artists[j];
                
                        if (g_hash_table_contains(artist_duration_table, artist)) {
                            int* total_duration = g_hash_table_lookup(artist_duration_table, artist);
                            if (total_duration != NULL) {
                                *total_duration += duration;
                                
                            }
                        } else {
                            int* total_duration = g_malloc(sizeof(int));
                            *total_duration = duration;
                            g_hash_table_insert(artist_duration_table, g_strdup(artist), total_duration);
                            
                        }
                    }

                    for (int j = 0; artists[j] != NULL; j++) {
                        g_free(artists[j]); 
                    }
                    g_free(artists); 
                }
            }
            

            
        }
    }

    GList* artist_duration_list = NULL;
    GList* keys = g_hash_table_get_keys(artist_duration_table);

    for (GList* iter = keys; iter != NULL; iter = iter->next) {
        char* artist = iter->data;
        
        int* duration = g_hash_table_lookup(artist_duration_table, artist);

        ArtistDuration* ad = g_malloc(sizeof(ArtistDuration));
        ad->artist = g_strdup(artist);
        ad->duration = *duration;

        artist_duration_list = g_list_append(artist_duration_list, ad);
    }

    artist_duration_list = g_list_sort(artist_duration_list, compare_artist_duration);

    int total_artists = g_list_length(artist_duration_list);
    int limit = x < total_artists ? x : total_artists;
    char** top_artists = g_malloc0((limit + 1) * sizeof(char*));

    GList* iter = artist_duration_list;
    for (int i = 0; i < limit; i++) {
        ArtistDuration* ad = iter->data;
        top_artists[i] = g_strdup(ad->artist);
        iter = iter->next;
    }
    top_artists[limit] = NULL;

   
    *result_count = limit;
   
    g_list_free_full(artist_duration_list, (GDestroyNotify)free_artist_duration);
    g_list_free(keys);
    g_hash_table_destroy(artist_duration_table);
    return top_artists;
}

int compare_artist_duration(gconstpointer a, gconstpointer b) {
    const ArtistDuration* ad1 = (const ArtistDuration*)a;
    const ArtistDuration* ad2 = (const ArtistDuration*)b;

    if (ad1->duration > ad2->duration) {
        return -1; 
    }
    if (ad1->duration < ad2->duration) {
        return 1; 
    }

    return strcmp(ad1->artist, ad2->artist);
}


void free_artist_duration(ArtistDuration* ad) {
    if (ad != NULL) {
        g_free(ad->artist); 
        g_free(ad);        
    }
}


int get_number_of_songs_listened_by_artist(char* user_id, int year, char* artist_name) {
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);
    if (user_hist == NULL) {
        
        return 0; 
    }

    int year_index = year - 2000;
    int song_count = 0;

    // Contar músicas ouvidas do artista no ano
    for (int i = 0; i < user_hist->num_music_stats; i++) {
        if (year_index >= 0 && year_index < 25) {
            char** artists = get_music_artist(user_hist->music_stats[i].music_id);

            for (int j = 0; artists[j] != NULL; j++) {
                if (strcmp(artists[j], artist_name) == 0) {
                    song_count++;
                    break;
                }
            }

            g_strfreev(artists);
        }
    }

    return song_count;
}

int get_duration_listened_by_artist(char* user_id, int year, char* artist_name) {
    User_history* user_hist = g_hash_table_lookup(user_hist_table, user_id);
    if (user_hist == NULL) {
        return 0; 
    }

    int year_index = year - 2000;
    int total_duration = 0;

    // Calcular duração total ouvida do artista no ano
    for (int i = 0; i < user_hist->num_music_stats; i++) {
        if (year_index >= 0 && year_index < 25) {
            char** artists = get_music_artist(user_hist->music_stats[i].music_id);
            int duration = user_hist->music_stats[i].duration_per_year[year_index];

            for (int j = 0; artists[j] != NULL; j++) {
                if (strcmp(artists[j], artist_name) == 0) {
                    total_duration += duration;
                    break;
                }
            }

            g_strfreev(artists);
        }
    }

    return total_duration;
}

void format_duration(int seconds, char *formatted_time) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int remaining_seconds = seconds % 60;

    sprintf(formatted_time, "%02d:%02d:%02d", hours, minutes, remaining_seconds);
}