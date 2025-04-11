#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"
#include "estatisticas.h"
#include "artist.h"
#include "music_manager.h"
#include <glib.h>
#include "queries.h"
#include "recomendador.h"
#include "artist_info.h"
#include "artist_info_manager.h"
#include "discografia_manager.h"
#include "week_manager.h"
#include "escrita.h"


//Recebe o id de um usuário, busca os dados do usuário na tabela, e escreve as informações no arquivo de saída.
void q1(char* id, FILE* fp, int equal)
{
    if (id[0]=='U')
    {
        if (user_exists(id))
        {
            char age_str[15];
            get_from_u(id,'b', age_str);
            char* email = get_from_u(id,'e', NULL);
            char* full_n = get_from_u(id,'f', NULL);
            char* last_name = get_from_u(id,'l', NULL);
            char* country = get_from_u(id,'c', NULL);
            escreve_q1_u(fp, equal,email,full_n, last_name, country, age_str);
            free(email);
            free(full_n);
            free(last_name);
            free(country);
            
        }
        else
        {
            escreve_barra(fp);
        }
    }
    else if (id[0]=='A')
    {
        if (artist_exists(id))
        {
            char* name = get_from_a(id,'n');
            char* country = get_from_a(id,'c');
            char* type = get_from_a(id,'t');
            int num = get_artist_num_albuns(id);
            double receita = get_artist_receita(id);
            escreve_q1_a(fp, equal, name, type, country, num, receita);
        }
        else
        {
            escreve_barra(fp);
        }
    }

}


//Recebe um número N e um parâmetro de país, e escreve no arquivo de saída as informações dos artistas de acordo com o país
void q2(char* n, char* param, FILE* fp, int equal)
{
    int N;
    sscanf(n, "%d", &N);
    GList* l_temp_music = get_discografias();
    
    int i = 0;
    while(i<N && l_temp_music!=NULL)
    {
        char* id = get_artist_id_disc(l_temp_music->data);
        int time = get_artist_total_time_disc(l_temp_music->data);
        char* name = get_from_a((id),'n');
        char* type = get_from_a((id),'t');
        char* country = get_from_a((id),'c');
        
        int horas = time / 3600; 
        int minutos = (time % 3600) / 60;  
        int segundos = time % 60;
        
        if(param!=NULL)
        {
            if (country != NULL && strcmp(param, country) == 0)
            {   
                escreve_q2( fp, equal, name, type, horas, minutos, segundos, country);

                l_temp_music = l_temp_music->next;
                i++;
            }
            else l_temp_music = l_temp_music->next;
        }
        else
        {
            escreve_q2( fp, equal, name, type, horas, minutos, segundos, country);
            
            l_temp_music = l_temp_music->next;
            i++;
        }
        free(name);
        free(type);
        free(country);

    }
    if(i==0)
    {
        escreve_barra(fp);
    }

    
}

typedef struct parsInt{
    int likes;
    char genre[15];
} ParstrInt;

int compare(const void* a, const void* b) {
    ParstrInt* pair1 = (ParstrInt*)a;
    ParstrInt* pair2 = (ParstrInt*)b;
    return pair1->likes - pair2->likes; 
}


//Recebe um intervalo de idades e busca os gêneros mais populares entre os usuários, escrevendo o resultado no arquivo
void q3(int agemin, int agemax, FILE* fp, int equal) 
{

    int likes_POP = 0;
    int likes_CLASSICA = 0;
    int likes_ROCK = 0;
    int likes_COUNTRY = 0;
    int likes_JAZZ = 0;
    int likes_REGGAE = 0;
    int likes_BLUE = 0;
    int likes_ELECTRONIC = 0;
    int likes_HIPPOP = 0;
    int likes_METAL = 0;

    gboolean has_data = FALSE; 
        
    for(int i=agemin;i<=agemax;i++)
    {
        for(int j=0;j<10;j++){
            
            
            char* genre = genre_from_Info(j,i);
            
            if(genre!=NULL && genre[0]!='\0'){
                
                int numLikes = numLikes_from_Info(j,i);
                
                //printf("%d, %s, %d\n",i,genre,numLikes);
                if(numLikes>0){ 
                    has_data = TRUE;
                    if (strcmp(genre, "Pop") == 0) {
                        likes_POP += numLikes;
                    } else if (strcmp(genre, "Classical") == 0) {
                        likes_CLASSICA += numLikes;
                    } else if (strcmp(genre, "Rock") == 0) {
                        likes_ROCK += numLikes;
                    } else if (strcmp(genre, "Country") == 0) {
                        likes_COUNTRY += numLikes;
                    } else if (strcmp(genre, "Jazz") == 0) {
                        likes_JAZZ += numLikes;
                    } else if (strcmp(genre, "Reggae") == 0) {
                        likes_REGGAE += numLikes;
                    } else if (strcmp(genre, "Blues") == 0) {
                        likes_BLUE += numLikes;
                    } else if (strcmp(genre, "Electronic") == 0) {
                        likes_ELECTRONIC += numLikes;
                    } else if (strcmp(genre, "Hip Hop") == 0) {
                        likes_HIPPOP += numLikes;
                    } else if (strcmp(genre, "Metal") == 0) {
                        likes_METAL += numLikes;
                    }
                }
            }
            
        }
    }
   
    if (!has_data) {
        // If no genres have likes in the age range, print a newline
        escreve_barra(fp);
    } else {

        ParstrInt data[10] = {
        {likes_POP, "Pop"},
        {likes_CLASSICA, "Classical"},
        {likes_ROCK, "Rock"},
        {likes_COUNTRY, "Country"},
        {likes_JAZZ, "Jazz"},
        {likes_REGGAE, "Reggae"},
        {likes_BLUE, "Blues"},
        {likes_ELECTRONIC, "Electronic"},
        {likes_HIPPOP, "Hip Hop"},
        {likes_METAL, "Metal"}
        };

        qsort(data,10,sizeof(ParstrInt),compare);

        for(int i=9; i>=0;i--){
            char* genre = data[i].genre;
            int likes = data[i].likes;

            escreve_q3(fp, equal, genre, likes);
        }
    }
}

void q4(char* min, char* max, FILE* fp, int equal)
{
    //intervalo de datas 
    //top 10 é calculado semanalmente
    //semana inicio domingo e fim sábado

    char min_week[11] = {0};  //ambas guardar o sábado das semanas
    char max_week[11] = {0};  //ambas guardar o sábado das semanas
    if(min!=NULL && max!=NULL){
        get_week_limits(min,min_week,NULL);
        get_week_limits(max,max_week,NULL);
    }
    
    char* name;
    int maxI = 0;
    if (min != NULL && max != NULL) maxI = get_top10Artists(min_week, max_week, &name);
    else maxI= get_top10Artists(NULL, NULL, &name);
    if (maxI == 0) 
    {
        escreve_barra(fp);
    }
    else 
    {
        char* genre = get_from_a(name, 't');
        escreve_q4(fp, equal, genre, name, maxI);
        free(name);
    }
}

void q5(char* id, int num_rec, FILE* fp) {
    // Validação de entrada
    if (id == NULL || num_rec < 0) {
        fprintf(stderr, "Parâmetros inválidos para a função q5.\n");
        return;
    }

    // Obter os dados da matriz de classificação
    int** matriz_classificacao = get_matriz_classificacao();
    char** ids_utilizadores = get_ids_utilizadores();
    int num_users = get_num_users();
    int num_generos = get_num_generos();

    gpointer user_index_ptr = g_hash_table_lookup(user_index_map, id);
    if (user_index_ptr == NULL || num_rec == 0) {
        escreve_barra(fp);
        return;
    }

    // Chamar a função recomendador
    char** recomendados = recomendaUtilizadores(id,
                                                matriz_classificacao,
                                                ids_utilizadores,
                                                (char**)GENEROS,
                                                num_users,
                                                num_generos,
                                                num_rec);

    // Escrever os resultados no arquivo
    for (int i = 0; i < num_rec; i++) {
        if (recomendados[i] != NULL) {
            escreve_q5(fp, recomendados[i]);
        }
    }
    free(recomendados);
}

void q6(char* user_id,int year,int N, FILE* fp){
    char* time_list = list_time_from_user(user_id, year);
    int num_time = num_time_list_from_user(user_id, year);
    int most_list_hour = hora_mais_ouvida(user_id, year);
    char* most_artist = artista_mais_ouvido(user_id, year);
    char* most_genre = genero_mais_ouvido(user_id, year);
    char* most_date = data_com_mais_musicas_ouvidas(user_id, year);
    char* most_album = album_mais_ouvido(user_id, year);
    if(num_time == 0) 
    {
        escreve_barra(fp);
    }
    else 
    {
        escreve_q6(fp, time_list, num_time, most_artist, most_date,most_genre,most_album,most_list_hour);
    }


    if(N>0){
        
        int result_count;
        char** artists = get_x_most_listened_artists(user_id,year,N,&result_count);
        for(int i=0;i<result_count;i++){
            
            int duration_art = get_duration_listened_by_artist(user_id,year,artists[i]);
            
            int num_art = get_number_of_songs_listened_by_artist(user_id,year,artists[i]);
            char formated[9];
            format_duration(duration_art,formated);
            escreve_q6_2(fp, artists[i], num_art, formated);
        }


    }
    
}
