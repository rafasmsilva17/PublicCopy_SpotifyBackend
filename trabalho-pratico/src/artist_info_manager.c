#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "artist_info.h"
#include "music_manager.h"
#include "artist_manager.h"

//Funções para q4
GHashTable *artist_info_ht = NULL;

void init_info_ht()
{
    artist_info_ht = g_hash_table_new(g_str_hash, g_str_equal);
}

void free_artistinfo_hash_table()
{
    if (artist_info_ht != NULL)
    {
        GList *keys = g_hash_table_get_keys(artist_info_ht);
        GList *iter = keys;

        while (iter != NULL)
        {
            char *key = (char *)iter->data;
            Artist_info *artinf = g_hash_table_lookup(artist_info_ht, key);

            if (artinf != NULL)
            {
                free_artistinfo_struct(artinf);  
            }

            free(key);  
            iter = iter->next;
        }

        g_list_free(keys);  
        g_hash_table_destroy(artist_info_ht);  
        artist_info_ht = NULL;
    }
}


double get_artist_receita(char *id)
{
    if (g_hash_table_contains(artist_info_ht, id) == 0)
    {
        return 0;
    }
    else
    {
        return get_artist_receita_struct(g_hash_table_lookup(artist_info_ht, id));
    }
}


void calculate_band(char *id)
{

    Artist_info *r1 = g_hash_table_lookup(artist_info_ht, id);
    double num = get_rate_num(r1);

    char **m = NULL;
    char* id2 = get_a_i_id(r1);
    int size = get_from_artist_array_num(id2, &m);
    free(id2);
    for (int i = 0; i < size; i++)
    {
        Artist_info *r2 = g_hash_table_lookup(artist_info_ht, m[i]);
        if (r2 != NULL)
            set_add_receita(r2, num, size);
        free(m[i]);
    }
    free(m);
}

void create_artist_info(char *id, char *musica)
{
    if (g_hash_table_contains(artist_info_ht, id) == 0)
    {
        g_hash_table_insert(artist_info_ht, strdup(id), create_artist_info_struct(id, musica));
    }
    else
    {
        Artist_info *art = g_hash_table_lookup(artist_info_ht, id);
        add_num_albuns_insert(art, musica);
    }
    free(id);
}


int get_artist_num_albuns(char *id)
{
    if (g_hash_table_contains(artist_info_ht, id))
        return get_artist_num_albuns_struct(g_hash_table_lookup(artist_info_ht, id));
    else
        return 0;
}

void organize_artist_info()
{
    init_info_ht();

    GList *k = get_keys_music_hash_table();
    GList *keys = k;

    while (keys != NULL)
    {
        char **list_a = get_music_artist(keys->data);
        for (int i = 0; list_a[i] != NULL; i++)
        {
            create_artist_info(list_a[i], keys->data);
        }
        free(list_a);
        keys = keys->next;
    }

    g_list_free(k);

    k = getKeys_hist();
    keys = k;

    while (keys != NULL)
    {
        char *music = get_from_hist(keys->data, 'm');
        char **list_a = get_music_artist(music);
        free(music);

        for (int i = 0; list_a[i] != NULL; i++)
        {
            if (g_hash_table_contains(artist_info_ht, list_a[i]))
            {
                Artist_info *art = g_hash_table_lookup(artist_info_ht, list_a[i]);

                char *artist_type = get_from_a(list_a[i], 't');
                if (strcmp(artist_type, "individual") != 0)
                {
                    calculate_band(list_a[i]);
                }
                free(artist_type);

                double num = get_rate_num(art);
                
                set_add_receita(art, num, 1);
                //art->reprod += 1;
            }
            free(list_a[i]);
        }

        free(list_a);
        keys = keys->next;
    }

    g_list_free(k);
}

void cleanup_artist_band_info()
{
    g_hash_table_foreach(artist_info_ht, free_artist_info, NULL);
    g_hash_table_destroy(artist_info_ht);
}
