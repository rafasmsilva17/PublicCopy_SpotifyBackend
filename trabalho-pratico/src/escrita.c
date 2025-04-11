#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void escreve_barra(FILE *fp)
{
    if (fp != NULL)
        fprintf(fp, "\n");
    else
        printf("  -> Data não encontrada\n");
}

void escreve_q1_u(FILE *fp, int equal, char *email, char *full_n, char *last_name, char *country, char *age_str)
{
    if (equal == 1)
    {
        if (fp != NULL)
            fprintf(fp, "%s=%s=%s=%s=%s\n", email, full_n, last_name, age_str, country);
        else
            printf("  -> %s=%s=%s=%s=%s\n", email, full_n, last_name, age_str, country);
    }
    else
    {
        if (fp != NULL)
            fprintf(fp, "%s;%s;%s;%s;%s\n", email, full_n, last_name, age_str, country);
        else
            printf("  -> %s;%s;%s;%s;%s\n", email, full_n, last_name, age_str, country);
    }
}

void escreve_q1_a(FILE *fp, int equal, char *name, char *type, char *country, int num, double receita)
{
    if (equal == 1)
    {
        if (fp)
            fprintf(fp, "%s=%s=%s=%d=%.2lf\n", name, type, country, num, receita);
        else
            printf("  -> %s=%s=%s=%d=%.2lf\n", name, type, country, num, receita);
    }
    else
    {
        if (fp)
            fprintf(fp, "%s;%s;%s;%d;%.2lf\n", name, type, country, num, receita);
        else
            printf("  -> %s;%s;%s;%d;%.2lf\n", name, type, country, num, receita);
    }
}

void escreve_q2(FILE *fp, int equal, char *name, char *type, int horas, int minutos, int segundos, char *country)
{
    if (equal == 1)
    {
        if (fp)
            fprintf(fp, "%s=%s=%02d:%02d:%02d=%s\n", name, type, horas, minutos, segundos, country);
        else
            printf("  -> %s=%s=%02d:%02d:%02d=%s\n", name, type, horas, minutos, segundos, country);
    }
    if (equal == 0)
    {
        if (fp)
            fprintf(fp, "%s;%s;%02d:%02d:%02d;%s\n", name, type, horas, minutos, segundos, country);
        else
            printf("  -> %s;%s;%02d:%02d:%02d;%s\n", name, type, horas, minutos, segundos, country);
    }
}

void escreve_q3(FILE *fp, int equal, char *genre, int likes)
{
    if (equal == 1)
    {
        if (fp)
            fprintf(fp, "%s=%d\n", genre, likes);
        else
            printf("  -> %s=%d\n", genre, likes);
    }
    else
    {
        if (fp)
            fprintf(fp, "%s;%d\n", genre, likes);
        else
            printf("  -> %s;%d\n", genre, likes);
    }
}

void escreve_q4(FILE *fp, int equal, char *genre, char *name, int maxI)
{
    if (equal == 1)
    {
        if (fp)
            fprintf(fp, "%s=%s=%d\n", name, genre, maxI);
        else
            printf("  -> %s=%s=%d\n", name, genre, maxI);
    }
    else
    {
        if (fp)
            fprintf(fp, "%s;%s;%d\n", name, genre, maxI);
        else
            printf("  -> %s;%s;%d\n", name, genre, maxI);
    }
}

void escreve_q5(FILE *fp, char* recomendados)
{
    if (fp)
        fprintf(fp, "%s\n", recomendados);
    else
        printf("  -> %s\n", recomendados);
}

void escreve_q6(FILE *fp,char* time_list,int num_time,char* most_artist,char* most_date,char*most_genre,char*most_album,int most_list_hour)
{
    if(fp) fprintf(fp,"%s;%d;%s;%s;%s;%s;%02d\n",time_list,num_time,most_artist,most_date,most_genre,most_album,most_list_hour);
    else printf("  -> %s;%d;%s;%s;%s;%s;%02d\n",time_list,num_time,most_artist,most_date,most_genre,most_album,most_list_hour);
}

void escreve_q6_2(FILE* fp, char* artist, int num_art, char* formated)
{
    if (fp) fprintf(fp,"%s;%d;%s\n",artist,num_art,formated);
    else printf("  -> %s;%d;%s\n",artist,num_art,formated);
}




// Função que escreve as linhas inválidas no ficheiro
void escreve_erros(char** line, char type) {
    if (line == NULL) {
        fprintf(stderr, "Erro: linha nula em escreve_erros.\n");
        return;
    }

    char filename[256];
    const char* header;

    // Determinar o nome do arquivo e o cabeçalho com base no tipo
    switch (type) {
        case 'U':
            strcpy(filename, "./resultados/users_errors.csv");
            header = "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"\n";
            break;
        case 'S':
            strcpy(filename, "./resultados/musics_errors.csv");
            header = "\"id\";\"title\";\"artist_id\";\"album_id\";\"duration\";\"genre\";\"year\";\"lyrics\"\n";
            break;
        case 'A':
            strcpy(filename, "./resultados/artists_errors.csv");
            header = "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"\n";
            break;
        case 'H':
            strcpy(filename, "./resultados/history_errors.csv");
            header = "\"id\";\"user_id\";\"music_id\";\"timestamp\";\"duration\";\"platform\"\n";
            break;
        default:
            fprintf(stderr, "Erro: tipo inválido.\n");
            return;
    }

    // Abrir o arquivo no modo adição
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Erro ao abrir ou criar o arquivo");
        return;
    }

    // Verificar se o cabeçalho precisa ser escrito
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == 0) {
        fprintf(file, "%s", header);
    }

    // Escrever a linha no arquivo
    for (int i = 0; i < 8; i++) {
        if (line[i] == NULL) break; // Parar ao encontrar o primeiro campo nulo
        fprintf(file, "\"%s\"", line[i]);
        if (i < 7 && line[i + 1] != NULL) {
            fprintf(file, ";");
        }
    }
    fprintf(file, "\n");

    // Fechar o arquivo
    fclose(file);
}