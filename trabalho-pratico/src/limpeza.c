#include <stdio.h>
#include <stdlib.h>
#include "data_manager.h"
#include "estatisticas.h"
#include "discografia_manager.h"
#include "week_manager.h"
#include "artist_info_manager.h"
#include "matrix_manager.h"

void limpeza()
{
    free_user_hash_table();
    free_artist_hash_table();
    free_historico_hash_table();
    free_album_hash_table();
    free_music_hash_table();
    free_gl_hash_table();
    cleanup_week();
    free_artistinfo_hash_table();
    free_user_genre_matrix();
    free_user_hist_hash_table();
    free_disc_hash_table();
}