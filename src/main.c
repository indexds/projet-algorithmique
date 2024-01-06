#include <stdio.h>
#include <stdlib.h>
#include "./header.h"
#include "./fits.h"
#include <string.h>

int main(void){
    Header header;
    FILE* file1;
    FILE* file2;
    FILE* output;
    char file_path[256];
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
            case 8: // TEST CASE
                file1 = fopen("../lights/r_lights_00001.fit", "rb");
                file2 = fopen("../lights/r_lights_00002.fit", "rb");
                FILE* file_3 = fopen("../lights/r_lights_00003.fit", "rb");
                FILE* file_4 = fopen("../lights/r_lights_00004.fit", "rb");
                FILE* file_5 = fopen("../lights/r_lights_00005.fit", "rb");
                FILE* file_6 = fopen("../lights/r_lights_00010.fit", "rb");
                FILE* file_7 = fopen("../lights/r_lights_00011.fit", "rb");
                FILE* file_8 = fopen("../lights/r_lights_00012.fit", "rb");
                FILE* file_9 = fopen("../lights/r_lights_00013.fit", "rb");
                output = fopen("./output_avg.fit", "wb");
                FILE* file_tab[10] = {file1,file2,file_3,file_4,file_5,file_6,file_7,file_8,file_9};
                printf("Creation du fichier sortant..\n");
                avg_fits_files(file_tab, output);
                fclose(file1);
                fclose(file2);
                fclose(file_3);
                fclose(file_4);
                fclose(file_5);
                fclose(file_6);
                fclose(file_7);
                fclose(file_8);
                fclose(file_9);
                fclose(output);
                break;

            case 0:
                exit(EXIT_SUCCESS);


            case 1:
                printf("PATH du fichier: ");
                scanf("%s", file_path);
                file1 = fopen(file_path, "rb");
                
                printf("-------------------------------------------\n");
                processHeader(file1, &header);
                printHeader(&header);

                fclose(file1);
                break;


            case 2:
                printf("PATH du fichier 1: ");
                scanf("%s", file_path);
                file1 = fopen(file_path, "rb");

                printf("PATH du fichier 2: ");
                scanf("%s", file_path);
                file2 = fopen(file_path, "rb");

                output = fopen("./output_sum.fit", "wb");
                printf("Creation du fichier sortant..\n");
                sum_fits_files(file1,file2,output);
                printf("Termine.");

                fclose(file1);
                fclose(file2);
                fclose(output);
                break;


            case 3:
                printf("PATH du fichier: ");
                scanf("%s", file_path);
                file1 = fopen(file_path, "rb");

                printf("PATH du fichier: ");
                scanf("%s", file_path);
                file2 = fopen(file_path, "rb");


                output = fopen("./output_sub.fit", "wb");
                printf("Creation du fichier sortant..\n");
                sub_fits_files(file1,file2,output);
                printf("Termine.");

                fclose(file1);
                fclose(file2);
                fclose(output);
                break;


            case 4:
                printf("Not Implemented. (AVG)");
                break;


            case 5:
                printf("PATH du fichier: ");
                scanf("%s", file_path);
                file1 = fopen(file_path, "rb");

                printf("PATH du fichier: ");
                scanf("%s", file_path);
                file2 = fopen(file_path, "rb");

                output = fopen("./output_div.fit", "wb");
                printf("Creation du fichier sortant..\n");
                div_fits_files(file1,file2,output);
                printf("Termine.");

                fclose(file1);
                fclose(file2);
                fclose(output);
                break;


            case 6:
                char output_file_name[256];
                printf("PATH du fichier: ");
                scanf("%s", file_path);

                strncat(output_file_name, strrchr(file_path, '/') + 1, strrchr(file_path, '.') - (strrchr(file_path, '/') + 1));
                strcat(output_file_name, ".csv");

                file1 = fopen(file_path, "rb");
                printf("Creation du fichier sortant..\n");
                output = fopen(output_file_name, "w");
                convert_csv(file1, output);
                printf("Termine.");

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
