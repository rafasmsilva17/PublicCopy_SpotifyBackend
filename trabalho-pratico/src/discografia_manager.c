#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "discografia.h"
#include "music_manager.h"
#include "artist_info_manager.h"


GList* discografias = NULL;
GHashTable* artist_disc_table = NULL;

void init_artist_disc_table()
{
    artist_disc_table = g_hash_table_new(g_str_hash, g_str_equal); 
}

GList* get_discografias()
{   
    return discografias;
}


//Função comparadora para ordenar discos de artistas com base no tempo total de forma decrescente
int compare_discographies(gconstpointer a, gconstpointer b)
{
    Artist_disc* disc_a = (Artist_disc*) a;
    Artist_disc* disc_b = (Artist_disc*) b;

    int total_time_a = get_artist_total_time_disc(disc_a);
    int total_time_b = get_artist_total_time_disc(disc_b);

    // Ordenação decrescente (maior tempo primeiro)
    if (total_time_b > total_time_a) {
        return 1;
    } else if (total_time_b < total_time_a) {
        return -1;
    } else {
        return 0;
    }
}

void free_disc(Artist_disc* disc) {
    if (disc != NULL) {
        free(disc);  // Liberar a memória alocada para o objeto
    }
}

void free_disc_hash_table() {
    GList* keys = g_hash_table_get_keys(artist_disc_table);
    GList* iter = keys;
    while (iter != NULL) {
        char* key = (char*)iter->data;
        Artist_disc* art = g_hash_table_lookup(artist_disc_table, key);
        free(key);  
        free_disc(art); 
        iter = iter->next;
    }
    g_list_free(keys);
    g_hash_table_destroy(artist_disc_table);
}

//Organiza a discografia dos artistas a partir da tabela de músicas e artistas.
//Para cada música, soma o tempo de execução às discografias dos artistas correspondentes. 
// musar para artistas / gestor
void organize_discografia() {
    GList* keys = get_keys_music_hash_table();
    init_artist_disc_table();

    if (keys == NULL) {
        printf("Tabelas de músicas ou artistas estão vazias.\n");
        return;
    }

    for (GList* key_cop = keys; key_cop != NULL; key_cop = key_cop->next) {
        char* music_id = (char*) key_cop->data;

        char** artistas = get_music_artist(music_id);
        int music_time = get_music_time(music_id);

        // Para cada artista da música, verificar ou criar a discografia
        for (int i = 0; artistas[i] != NULL; i++) {
            Artist_disc* disc = (Artist_disc*) g_hash_table_lookup(artist_disc_table, artistas[i]);

            if (disc != NULL) {
                soma_tempo_disc(disc, music_time);
            } else {
                Artist_disc* new_disc = create_disc(artistas[i], music_time);
                g_hash_table_insert(artist_disc_table, strdup(artistas[i]), new_disc); 
            }

            free(artistas[i]); 
        }
        free(artistas); 
    }
    g_list_free(keys);

    GList* temp_list = NULL;
    GList* keys_artists = get_keys_artist_hash_table();
    for (GList* key_cop = keys_artists; key_cop != NULL; key_cop = key_cop->next) {
        char* artist_id = (char*) key_cop->data;
        Artist_disc* disc = (Artist_disc*) g_hash_table_lookup(artist_disc_table, artist_id);
        if (disc != NULL) { // Filtrar elementos nulos
            temp_list = g_list_append(temp_list, disc);
            
        }
    }
    g_list_free(keys_artists);

    discografias = g_list_sort(temp_list, compare_discographies);
    
}