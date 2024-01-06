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
    char file_path[256];
    char output_file_name[256];
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
            "-------------------------------------------\n"
        );

        scanf("%d", &choix);
        getchar();

        switch(choix){
            case 0:
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
                    printf("Saisir le nombre de fichier : \n");
                    scanf("%d",&file_number);
                }
                while(file_number <= 0);

                FILE** file_tab = malloc(sizeof(FILE*)*file_number);

                for(int i = 0; i < file_number; i++){
                    do{
                        printf("Rentrer le fichier %d: ", i);
                        scanf("%s", current_file);
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


            default:
                printf("Nombre Invalide.\n");
                continue;
        };
    };
    return 0;
};
