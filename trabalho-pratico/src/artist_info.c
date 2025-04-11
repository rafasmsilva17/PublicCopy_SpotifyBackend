#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "music_manager.h"
#include "artist_manager.h"

typedef struct artist_info
{
    char id[9];
    char type[11];
    char rate_per_stream[5];
    GHashTable *albuns;
    int num_albuns;
    double group_receita;
    double receita;
    double reprod;
} Artist_info;

typedef struct a_inc
{
    char album[9];
    int num;
} A_inc;

int insert_albuns(GHashTable *albuns, char *id)
{
    if (g_hash_table_contains(albuns, id) == 0)
    {
        A_inc *z = malloc(sizeof(A_inc));
        strcpy(z->album, id);
        z->num = 1;
        g_hash_table_insert(albuns, strdup(id), z);
        free(id);
        return 1;
    }
    else
    {
        A_inc *z = g_hash_table_lookup(albuns, id);
        z->num++;
        free(id);
        return 0;
    }
}

Artist_info *create_artist_info_struct(char *id, char *musica)
{

    Artist_info *art = malloc(sizeof(Artist_info));
    strcpy(art->id, id);

    char *type = get_from_a(id, 't');
    strcpy(art->type, type);
    free(type);

    char *rate = get_from_a(id, 'r');
    strcpy(art->rate_per_stream, rate);
    free(rate);

    art->albuns = g_hash_table_new(g_str_hash, g_str_equal);
    art->num_albuns = insert_albuns(art->albuns, get_album_name(musica));
    art->group_receita = 0;
    art->receita = 0;
    art->reprod = 0;

    return art;
}

void free_artistinfo_struct(Artist_info *artinf)
{
    if (artinf != NULL)
    {
        if (artinf->albuns != NULL)
        {
            GList *albuns_keys = g_hash_table_get_keys(artinf->albuns);
            GList *iter = albuns_keys;
            while (iter != NULL)
            {
                A_inc *album_info = (A_inc *)g_hash_table_lookup(artinf->albuns, iter->data);
                if (album_info != NULL)
                {
                    free(album_info);
                }
                free(iter->data);
                iter = iter->next;
            }
            g_list_free(albuns_keys);
            g_hash_table_destroy(artinf->albuns);
        }
    }
}

double get_rate_num(Artist_info* r1)
{
    double num;
    sscanf(r1->rate_per_stream, "%lf", &num);
    return num;
}

int get_artist_num_albuns_struct(Artist_info *r )
{
    return r->num_albuns;
}

void set_add_receita(Artist_info* r2, double num, int size)
{
    r2->receita += num * (1.0 / size);
}

void add_num_albuns_insert(Artist_info* art, char* musica)
{
    art->num_albuns += insert_albuns(art->albuns, get_album_name(musica));
}

char* get_a_i_id(Artist_info* r)
{
    return strdup(r->id);
}

double get_artist_receita_struct(Artist_info *r)
{
    return r->receita;
}

void free_album_info(gpointer key, gpointer value, gpointer user_data)
{
    A_inc *info = (A_inc *)value;
    free(info);
}

void free_artist_info(gpointer key, gpointer value, gpointer user_data)
{
    Artist_info *info = (Artist_info *)value;
    g_hash_table_foreach(info->albuns, free_album_info, NULL);
    g_hash_table_destroy(info->albuns);

    free(key);
    free(info);
}
