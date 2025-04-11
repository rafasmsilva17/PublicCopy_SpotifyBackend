#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "music_manager.h"
#include "historico_manager.h"
#include <time.h>

#include "week.h"

GHashTable *weekly_ht = NULL;
GHashTable *artists_count = NULL;

void init_weekly()
{
    weekly_ht = g_hash_table_new(g_str_hash, g_str_equal);
}

void get_top10Artists_week(char *week, ArtistAggregate **top10)
{
    int i = 0;
    WeeklyAggregate *week_s = g_hash_table_lookup(weekly_ht, week);
    if (week_s == NULL)
        return;
    
    GHashTable* artists_hash = get_artist_hash(week_s);
    GList *keys = g_hash_table_get_keys(artists_hash);
    GList *iter = keys;
    while (iter != NULL)
    {
        ArtistAggregate *a = g_hash_table_lookup(artists_hash, iter->data);
        if (i < 10)
        {
            top10[i] = create_artist_agg(NULL, 0,0);
            strcpy(get_artist_aggregate(top10[i]), iter->data);
            add_time(top10[i], a);
            i++;
        }
        else
        {
            int min_index = 0;
            for (int j = 1; j < 10; j++)
            {
                if (get_time(top10[j]) < get_time(top10[min_index]))
                {
                    min_index = j;
                }
            }
            if (get_time(a) > get_time(top10[min_index]))
            {
                strcpy(get_artist_aggregate(top10[min_index]), iter->data);
                add_time(top10[min_index], a);
            }
        }
        iter = iter->next;
    }
    g_list_free(keys);
}

void add_hash_count(GHashTable *table, ArtistAggregate **top)
{
    for (int i = 0; i < 10; i++)
    {
        if (top[i] == NULL)
        {
            continue;
        }

        if (g_hash_table_contains(table, get_artist_aggregate(top[i])))
        {
            ArtistAggregate *a = g_hash_table_lookup(table,get_artist_aggregate(top[i]));
            inc_time_top(a);
        }
        else
        {
            g_hash_table_insert(table, strdup(get_artist_aggregate(top[i])), create_artist_agg(get_artist_aggregate(top[i]), 0, 1));
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (top[i] != NULL)
        {
            free(top[i]);
            top[i] = NULL;
        }
    }
}


int get_top10Artists(char *week1, char *week2, char **name)
{
    artists_count = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);

    if (week1 == NULL && week2 == NULL)
    {
        GList *week_list = g_hash_table_get_keys(weekly_ht);

        for (GList *cop = week_list; cop != NULL; cop = cop->next)
        {
            ArtistAggregate *top10[10] = {NULL}; 
            get_top10Artists_week(cop->data, top10);
            add_hash_count(artists_count, top10);
        }

        g_list_free(week_list);
    }
    else
    {
        char *week = strdup(week1);
        if (!week)
        {
            return -1;
        }
        
        inc_week(week2);

        while (strcmp(week, week2) != 0)
        {
            ArtistAggregate *top10[10] = {NULL};  
            get_top10Artists_week(week, top10);
            add_hash_count(artists_count, top10);

            inc_week(week);
        }
        free(week); 
    }
    
    GList *keys_origin = g_hash_table_get_keys(artists_count);
    int max = 0;

    for (GList *keys = keys_origin; keys != NULL; keys = keys->next)
    {
        if (keys->data != NULL)
        {
            ArtistAggregate *a = g_hash_table_lookup(artists_count, keys->data);
            if (a != NULL)
            {
                if (get_time_top(a) > max)
                {
                    max = get_time_top(a);
                    
                    *name = strdup(get_artist_aggregate(a));
                    if (!*name) 
                    {
                        g_list_free(keys_origin);
                        g_hash_table_destroy(artists_count); 
                        return -1;
                    }
                }
                else if (get_time_top(a) == max)
                {
                    ArtistAggregate *b = g_hash_table_lookup(artists_count, *name);
                    if (b != NULL && strcmp(get_artist_aggregate(a), get_artist_aggregate(b)) < 0)
                    {
                        if (*name != NULL)
                        {
                            free(*name);
                        }
                        *name = strdup(get_artist_aggregate(a));
                        if (!*name) 
                        {
                            g_list_free(keys_origin); 
                            g_hash_table_destroy(artists_count); 
                            return -1;
                        }
                    }
                }
            }
        }
    }

    g_list_free(keys_origin);

    g_hash_table_destroy(artists_count);
    artists_count = NULL;

    return max;
}




void add_artist_to_aggregate(char *start_date, char *end_date, char *artist_name, int time)
{
    WeeklyAggregate *week = g_hash_table_lookup(weekly_ht, start_date);

    if (!week)
    {
        week = create_week(start_date, end_date);
        g_hash_table_insert(weekly_ht, strdup(start_date), week);
    }

    ArtistAggregate *artist_data = g_hash_table_lookup(get_artist_hash(week), artist_name);
    if (artist_data)
    {
        add_time_num(artist_data, time);
    }
    else
    {
        g_hash_table_insert(get_artist_hash(week), strdup(artist_name), create_artist_agg(artist_name, time,0));
    }
}


void cleanup_week() {
    if (weekly_ht) {
        GList* week_keys = g_hash_table_get_keys(weekly_ht);
        
        for (GList* wk = week_keys; wk != NULL; wk = wk->next) {
            char* key = wk->data;
            WeeklyAggregate* week = g_hash_table_lookup(weekly_ht, key);

            if (week) {
                if (get_artist_hash(week)) {
                    GHashTable* artist_ht = get_artist_hash(week);
                    g_hash_table_destroy(artist_ht);
                }

                free(week);
            }

            g_free(key);
        }

        g_list_free(week_keys);

        g_hash_table_destroy(weekly_ht);
        weekly_ht = NULL;
    }

    
}


void organize_hist_week(char *id_hist)
{
    char *music = get_from_hist(id_hist, 'm');
    char start_date[11] = {0};
    char end_date[11] = {0};
    char *time_prod = get_from_hist(id_hist, 'd');

    int hours, minutes, seconds, total_seconds;
    sscanf(time_prod, "%d:%d:%d", &hours, &minutes, &seconds);
    total_seconds = hours * 3600 + minutes * 60 + seconds;
    free(time_prod);

    char **artists = get_music_artist(music);
    char *t = get_from_hist(id_hist, 't');
    free(music);
    get_week_limits(t, start_date, end_date);
    free(t);
    for (int i = 0; artists[i] != NULL; i++)
    {
        add_artist_to_aggregate(start_date, end_date, artists[i], total_seconds);
    }

    for (int i = 0; artists[i] != NULL; i++)
    {
        free(artists[i]);
    }
    free(artists);
}
