#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "data_manager.h"
#include "queries.h"

int entry()
{
    char** caminho = malloc(sizeof(char*) * 2);
    caminho[1] = malloc(8 * sizeof(char));
    //system("clear");
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("|____________________________________________________________________________________________________________|\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                              ---------------                                               |\n");
    printf("|                                              | BUBBLEMUSIC |                                               |\n");
    printf("|                                              ---------------                                               |\n");
    printf("|                                                                                                            |\n");
    printf("|                                      Feel the Vibe, Own Your Rhythm                                        |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                Load dataset                                                |\n");
    printf("|____________________________________________________________________________________________________________|\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("  Introduza o caminho dos ficheiros de dados: "); scanf("%s", caminho[1]);
    if(strcmp(caminho[1], "dataset")!=0)
    {
        error();
        
        return 1;
    }
    
    printf("  Dataset carregado...\n");
    //load
    boot_inicial(caminho);
    return 0;
}

int home_page()
{
    int n = 0;
    system("clear");
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("|                                                BUBBLEMUSIC                                                 |\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|           1. Enter                                                                                         |\n");
    printf("|           2. See Creators                                                                                  |\n");
    printf("|           3. Exit                                                                                          |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(" -> "); scanf("%d",&n);
    if(n<1 || n>3) return home_page();
    else return n;
}

void error()
{
    system("clear");
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("|                                                   ERROR                                                    |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|            | |                                                                                             |\n");
    printf("|            | |===( )   //////                                                                              |\n");
    printf("|            |_|   |||  | o o|                                                                               |\n");    
    printf("|                   ||| ( c  )                  ____                                                         |\n");            
    printf("|                    ||| \\= /                  ||   \\_                                                      | \n");        
    printf("|                     ||||||                   ||     |                                                      | \n");        
    printf("|                     ||||||                ...||__/|-\"                                                      | \n");            
    printf("|                     ||||||             __|________|__                                                      | \n");           
    printf("|                       |||             |______________|                                                     | \n");         
    printf("|                       |||             || ||      || ||                                                     | \n");           
    printf("|                       |||             || ||      || ||                                                     | \n");          
    printf("|-----------------------|||-------------||-||------||-||                                                     | \n");
    printf("|                       |__>            || ||      || ||                                                     | \n");        
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");
    printf("|                                                                                                            |\n");   
    printf("|                                                                                                            |\n"); 
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    
    printf("  Pressione Enter para continuar ... ");
    while (getchar() != '\n');
    getchar();
}

void credits()
{
    system("clear");
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("|                                                  Credits                                                   |\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("| Creators:                                                                                                  |\n");
    printf("|    -> Diogo Moreira                                                                                        |\n");
    printf("|    -> Nuno Mendes                                                                                          |\n");
    printf("|    -> Rafael Silva                                                                                         |\n");
    printf("|                 __                                        __                                               |\n");     
    printf("|                |--|                                      |--|                                              |\n");      
    printf("|     .._       o' o'                     (())))     _    o' o'                                              |\n");   
    printf("|    //\\\\\\    |  __                      )) _ _))  ,' ; |  __                                                |\n");     
    printf("|   ((-.-\\)  o' |--|  ,;::::;.          (C    )   / /^ o' |--|                                               |\n");    
    printf("|  _))'='(\\-.  o' o' ,:;;;;;::.         )\\   -'( / /     o' o'                                               |\n");     
    printf("| (          \\       :' o o `::       ,-)()  /_.')/                 .                                        |\n");       
    printf("| | | .)(. |\\ \\      (  (_    )      /  (  `'  /\\_)    .:izf:,_  .  |                                        |\n");       
    printf("| | | _   _| \\ \\     :| ,==. |:     /  ,   _  / 1  \\ .:q568Glip-, \\ |                                        |\n");       
    printf("| \\ \\/ '-' (__\\_\\____::\\`--'/::    /  /   / \\/ /|\\  \\-38'^\"^`8k='  \\L,                                       |\n");      
    printf("|  \\__\\[][]____(_\\_|::,`--',::   /  /   /__/ <(  \\  \\8) o o 18-'_ ( /                                        |\n");        
    printf("|   :\\o*.-.(     '-,':   _    :`.|  L----' _)/ ))-..__)(  J  498:- /]                                        |\n");     
    printf("|   :   [   \\     |     |=|   '  |\\_____|,/.' //.   -38, 7~ P88;-'/ /                                        |\n");      
    printf("|   :  | \\   \\    |  |  |_|   |  |    ||  :: (( :   :  ,`""'`-._,' /                                           |\n");      
    printf("|   :  |  \\   \\   ;  |   |    |  |    \\ \\_::_)) |  :  ,     ,_    /                                          |\n");         
    printf("|   :( |   /  )) /  /|   |    |  |    |    [    |   \\_\\      _;--==--._                                      |\n");         
    printf("|   :  |  /  /  /  / |   |    |  |    |    Y    |    (_\\____:_        _:                                     |\n");       
    printf("|   :  | /  / _/  /  \\   |    |  |    |    |    | ,--==--.  |_`--==--'_|                                     |\n");           
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    printf("  Pressione Enter para continuar ... ");
    while (getchar() != '\n');
    getchar();
}

void play()
{
    int querie;
    char id[9], min[64], max[64], n[64], pais[64];
    int age_max= 0, age_min=0 , rec=0;

    system("clear");
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("|                                                BUBBLEMUSIC                                                 |\n");
    //fim load
    printf("  Que query deseja executar? "); scanf("%d",&querie);
    if(querie <1 || querie >6)
    {
        printf("  ERRO: essa query não existe\n");
        return;
    }
    switch (querie) {
        case 1:
            printf("  Nome do utilizador/artista: ");
            if (scanf("%8s", id) != 1) {
                printf("ERRO!\n");
                return;
            }
            printf("  Output:\n");
            q1(id, NULL, 0);
            break;
            
        case 2:
            printf("  Número: ");
            if (scanf("%63s", n) != 1) {
                printf("ERRO!\n");
                return;
            }
            printf("  País (opcional, insira 0 para ignorar): ");
            if (scanf("%63s", pais) != 1) {
                printf("ERRO!\n");
                return;
            }
            printf("  Output:\n");
            q2(n, (pais[0] != '0' ? pais : NULL), NULL, 0);
            break;
            
         case 3:
            printf("  Idade mínima: ");
            if (scanf("%d", &age_min) != 1) {
                printf("ERRO!\n");
                return;
            }
            printf("  Idade máxima: ");
            if (scanf("%d", &age_max) != 1) {
                printf("ERRO!\n");
                return;
            }
            printf("  Output:\n");
            q3(age_min, age_max, NULL, 0);
            break;
            
        case 4:
            printf("  Data mínima (opcional, insira 0000/00/00 para ignorar): ");
            if (scanf("%63s", min) != 1 || strcmp(min, "0000/00/00") == 0) {
                min[0] = '\0'; 
            }
            printf("  Data máxima (opcional, insira 0000/00/00 para ignorar): ");
            if (scanf("%63s", max) != 1 || strcmp(max, "0000/00/00") == 0) {
                max[0] = '\0';
            }
            printf("  Output:\n");
            q4((min[0] != '\0' ? min : NULL), (max[0] != '\0' ? max : NULL), NULL, 0);
            break;
            
        case 5:
            printf("  Nome do utilizador: ");
            if (scanf("%63s", id) != 1) {
                printf("ERRO!\n");
                return;
            }
            printf("  Numero de recomendações: ");
            if (scanf("%d", &rec) != 1) {
                printf("ERRO!\n");
                return;
            }
            printf("  Output:\n");
            q5(id, rec, NULL);
            break;

        case 6:
            printf("  Nome do utilizador: ");
            if (scanf("%63s", id) != 1) {
                printf("ERRO!\n");
                return;
            }
            printf("  Ano: ");
            int year;
            if (scanf("%d", &year) != 1) {
                printf("ERRO!\n");
                return;
            }
            printf("  Número de artistas (opcional, insira 0 para ignorar): ");
            int N;
            if (scanf("%d", &N) != 1 || N < 0) {
                printf("ERRO!\n");
                return;
            }
            printf("  Output:\n");
            q6(id, year, N, NULL);
            break;


        default:
            printf("ERRO!\n");
            return;
    }
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("  Pressione Enter para continuar ... ");
    while (getchar() != '\n');
    getchar();
}

void program_interface()
{
    int n  = home_page();
    if(n==1)
    {
        play();
        program_interface();
    }
    else if(n == 2) 
    {
        credits();
        program_interface();
    }
    else if(n == 3)
    {
        system("clear");
        printf("FIM!\n");
    }    
}
