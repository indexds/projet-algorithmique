#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./header.h"
#include "./fits.h"

int main(void){
    Header header;
    FILE* file1;
    FILE* file2;
    FILE* output;
    char* file_path = malloc(sizeof(char)*256);
    memset(file_path, '\0', 256);
    char* output_file_name = malloc(sizeof(char)*256);
    memset(output_file_name, '\0', 256);

    int choix;

    while(1){
        printf("------------- UTILITAIRE FITS -------------\n"
            "(0) SORTIR DU PROGRAMME\n"
            "(1) LIRE LE HEADER\n"
            "(2) SOMMER DES IMAGES\n"
            "(3) SOUSTRAIRE DES IMAGES\n"
            "(4) MOYENNE DES IMAGES\n"
            "(5) DIVISER DES IMAGES\n"
            "(6) CONVERTIR EN CSV\n"
            "(7) GENERATION DE L'IMAGE GLOBALE\n"
            "-------------------------------------------\n"
        );

        if (scanf("%d", &choix) != 1) {
            printf("Input invalide, reessayer.\n");
            // clear stdin
            while (getchar() != '\n');
            continue;
        };

        switch(choix){
            case 0:
                free(file_path);
                free(output_file_name);
                exit(EXIT_SUCCESS);


            case 1:
                do {
                    printf("PATH du fichier: ");
                    scanf("%s", file_path);
                    file1 = fopen(file_path, "rb");
                    if (file1 == NULL) {
                        printf("PATH invalide, reessayer.\n");
                    }
                } while (file1 == NULL);

                printf("-------------------------------------------\n");
                processHeader(file1, &header);
                printHeader(&header);

                fclose(file1);
                break;


            case 2:
                do {
                    printf("PATH du fichier 1: ");
                    scanf("%s", file_path);
                    file1 = fopen(file_path, "rb");
                    if (file1 == NULL) {
                        printf("PATH invalide, reessayer.\n");
                    }
                } while (file1 == NULL);

                do {
                    printf("PATH du fichier 2: ");
                    scanf("%s", file_path);
                    file2 = fopen(file_path, "rb");
                    if (file2 == NULL) {
                        printf("PATH invalide, reessayer.\n");
                    }
                } while (file2 == NULL);

                output = fopen("./output_sum.fit", "wb");
                printf("Creation du fichier sortant..\n");
                sum_fits_files(file1,file2,output);
                printf("Termine.\n");

                fclose(file1);
                fclose(file2);
                fclose(output);
                break;


            case 3:
                do {
                    printf("PATH du fichier 1: ");
                    scanf("%s", file_path);
                    file1 = fopen(file_path, "rb");
                    if (file1 == NULL) {
                        printf("PATH invalide, reessayer.\n");
                    }
                } while (file1 == NULL);

                do {
                    printf("PATH du fichier 2: ");
                    scanf("%s", file_path);
                    file2 = fopen(file_path, "rb");
                    if (file2 == NULL) {
                        printf("PATH invalide, reessayer.\n");
                    }
                } while (file2 == NULL);


                output = fopen("./output_sub.fit", "wb");
                printf("Creation du fichier sortant..\n");
                sub_fits_files(file1,file2,output);
                printf("Termine.\n");

                fclose(file1);
                fclose(file2);
                fclose(output);
                break;


            case 4:
                int file_number;
                char current_file[256];
                do{
                    printf("Saisir le nombre de fichiers: ");
                    scanf("%d", &file_number);
                }
                while(file_number <= 0);

                FILE** file_tab = calloc(file_number + 1, sizeof(FILE*));

                for(int i = 0; i < file_number; i++){
                    do{
                        printf("Rentrer le fichier %d: ", i+1);
                        scanf("%255s", current_file);
                        file_tab[i] = fopen(current_file, "rb");
                    }
                    while(file_tab[i] == NULL);

                };
                output = fopen("./output_avg.fit", "wb");
                printf("Creation du fichier sortant..\n");

                avg_fits_files(file_tab, output);

                for(int i = 0; i < file_number; i++){
                    fclose(file_tab[i]);
                };
                free(file_tab);
                fclose(output);
                break;


            case 5:
                do {
                    printf("PATH du fichier 1: ");
                    scanf("%s", file_path);
                    file1 = fopen(file_path, "rb");
                    if (file1 == NULL) {
                        printf("PATH invalide, reessayer.\n");
                    }
                } while (file1 == NULL);

                do {
                    printf("PATH du fichier 2: ");
                    scanf("%s", file_path);
                    file2 = fopen(file_path, "rb");
                    if (file2 == NULL) {
                        printf("PATH invalide, reessayer.\n");
                    }
                } while (file2 == NULL);

                output = fopen("./output_div.fit", "wb");
                printf("Creation du fichier sortant..\n");
                div_fits_files(file1,file2,output);
                printf("Termine.\n");

                fclose(file1);
                fclose(file2);
                fclose(output);
                break;


            case 6:
                do {
                    printf("PATH du fichier: ");
                    scanf("%s", file_path);
                    file1 = fopen(file_path, "rb");
                    if (file1 == NULL) {
                        printf("PATH invalide, reessayer.\n");
                    }
                } while (file1 == NULL);

                strncat(output_file_name, strrchr(file_path, '/') + 1, strrchr(file_path, '.') - (strrchr(file_path, '/') + 1));
                strcat(output_file_name, ".csv");

                file1 = fopen(file_path, "rb");
                printf("Creation du fichier sortant..\n");
                output = fopen(output_file_name, "w");
                convert_csv(file1, output);
                printf("Termine.\n");

                fclose(file1);
                fclose(output);
                break;

            case 7:
                printf("Generation du master_dark..\n");
                generateMaster("../darks", "../darks/master_dark.fit");
                printf("Generation du master_flat..\n");
                generateMaster("../flats", "../flats/master_flat.fit");
                printf("Generation du master_offset..\n");
                generateMaster("../offsets", "../offsets/master_offset.fit");

                printf("Pretraitement en cours..\n");

                FILE* master_dark = fopen("../darks/master_dark.fit", "rb");
                FILE* master_flat = fopen("../flats/master_flat.fit", "rb");
                FILE* master_offset = fopen("../offsets/master_offset.fit", "rb");
                generatePretraite(master_dark, master_flat, master_offset);

                fclose(master_dark);
                fclose(master_flat);
                fclose(master_offset);
                printf("Generation du master_light_post..\n");
                generateMaster("../lights_post", "../lights_post/master_light_post.fit");
                break;


            default:
                printf("Nombre Invalide.\n");
                continue;
        };
    };

    return 0;
};
