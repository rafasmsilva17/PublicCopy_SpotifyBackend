#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <glib.h>


#include "parsing.h"
#include "validation.h"

#include "user_manager.h"
#include "artist_manager.h"
#include "albuns_manager.h"
#include "historico_manager.h"
#include "estatisticas.h"
#include "matrix_manager.h"
#include "music_manager.h"
#include "artist_info.h"
#include "artist_info_manager.h"
#include "discografia_manager.h"
#include "week_manager.h"
#include "escrita.h"

void init()
{
    init_hashtable_artist();
    init_hashtable_user();
    init_hashtable_music();

    init_hashtable_album();
    init_hashtable_historico();

    init_artist_disc_table();
    init_genrelikesT_table();
    init_weekly();
}


void open_files(char** argv, FILE** files)
{

    // -> abrir pasta dataset  (precisa de ser alterado para a pasta geral)
    char *csv_folder = argv[1];
    FILE* fp1 = fopen(csv_folder, "r");

    //cria o caminho artist.csv
    char* artist_csv_caminho = malloc(strlen(csv_folder)+strlen("/artists.csv") +1);
    sprintf(artist_csv_caminho, "%s/artists.csv", csv_folder);

    //cria o caminho music.csv
    char* music_csv_caminho = malloc(strlen(csv_folder)+strlen("/musics.csv") +1);
    sprintf(music_csv_caminho, "%s/musics.csv", csv_folder);

    //cria o caminho user.csv
    char* user_csv_caminho = malloc(strlen(csv_folder)+strlen("/users.csv") +1);
    sprintf(user_csv_caminho, "%s/users.csv", csv_folder);

    //cria o caminho album.csv
    char* album_csv_caminho = malloc(strlen(csv_folder)+strlen("/albums.csv") +1);
    sprintf(album_csv_caminho, "%s/albums.csv", csv_folder);

    //cria o caminho album.csv
    char* historico_csv_caminho = malloc(strlen(csv_folder)+strlen("/history.csv") +1);
    sprintf(historico_csv_caminho, "%s/history.csv", csv_folder);
    

    
    // Abrir o arquivo artists.csv
    FILE* artist_csv = fopen(artist_csv_caminho, "r");
    free(artist_csv_caminho);
    files[0] = artist_csv;
    
    // Abrir o arquivo musics.csv
    FILE* music_csv = fopen(music_csv_caminho, "r");
    free(music_csv_caminho);
    files[1] = music_csv;

    // Abrir o arquivo users.csv
    FILE* user_csv = fopen(user_csv_caminho, "r");
    free(user_csv_caminho);
    files[2] = user_csv;

    // Abrir o arquivo albuns
    FILE* album_csv = fopen(album_csv_caminho, "r");
    free(album_csv_caminho);
    files[3] = album_csv;

    // Abrir o arquivo albuns
    FILE* historico_csv = fopen(historico_csv_caminho, "r");
    free(historico_csv_caminho);
    files[4] = historico_csv;
    fclose(fp1);
}


//Lê os dados dos arquivos de Artistas, Músicas e Usuários, processando as linhas de cada um.
//Para cada linha, a função tokeniza os dados, valida sintaticamente e logicamente, e organiza as informações nas tabelas apropriadas.
void process_file(FILE* fp, char tipo, void (*organize_func)(char**)) {
    ssize_t read;
    char* line = NULL;
    size_t len;

    // Ignorar a primeira linha do arquivo
    getline(&line, &len, fp);

    // Processar o arquivo
    while ((read = getline(&line, &len, fp)) != -1) {
        char** string = malloc(8 * sizeof(char*)); // Alocar memória para 8 tokens
        if (string == NULL) {
            printf("Erro de alocação de memória em process_file.\n");
            continue;
        }
        tokenize_pars(line, string);  // Preencher os tokens no array já alocado
        if (syntactic_validation(string, tipo) && logic_validation(string, tipo)) {
            organize_func(string);
            if(tipo == 'H'){
                organize_hist_week(string[0]);
            }
        } else {
            escreve_erros(string, tipo);
        }
        free(string);  // Liberar o array de strings
    }

    // Liberar a memória alocada para a linha (line)
    free(line); // Certificar-se de que a memória de 'line' está sendo liberada
    line = NULL; // Garantir que o ponteiro 'line' não aponta para um endereço inválido
}

void readLine(FILE* fpA, FILE* fpM, FILE* fpU, FILE* fpAlb , FILE* fpHist){
    
    process_file(fpA, 'A', organizeA);

    process_file(fpAlb, 'B', organizeAlb);

    process_file(fpM, 'S', organizeMusic);

    process_file(fpU, 'U', organizeU);

    process_file(fpHist, 'H', organizeHist);
    
    organize_discografia();
    organize_artist_info();
    organizaGenreLikes(); 
    organize_user_hist();
    init_genre_index_map();
    create_user_genre_matrix();
}


//Tokeniza uma linha de dados separada por ponto e vírgula, retornando os tokens em um array de strings.
//A linha pode ter até 8 tokens.
void tokenize_pars(char* line, char** strings) {
    int i = 0;
    char* rest = line;
    char* token = strtok_r(line, ";", &rest);

    while (token != NULL && i < 8) {
        // Remover aspas, se existirem
        if (token[0] == '"') token++;
        if (token[strlen(token) - 1] == '\n') token[strlen(token) - 1] = '\0';
        if (token[strlen(token) - 1] == '"') token[strlen(token) - 1] = '\0';
        strings[i++] = token;
        token = strtok_r(NULL, ";", &rest);
    }

    // Preencher o restante com NULL caso não tenha completado 8 tokens
    while (i < 8) {
        strings[i++] = NULL;
    }
}