#include <stdio.h>
#include <stdlib.h>
#include "./header.h"
#include "./fits.h"
#include "./convert.h"

int main(void){
    Header header;
    FILE* file_1;
    FILE* file_2;
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
            "(7) CONVERTIR EN PNG\n"
            "-------------------------------------------\n"
        );

        scanf("%d", &choix);
        getchar();

        switch(choix){
            case 8: // TEST CASE
                file_2 = fopen("r_lights_00004.txt", "r");
                processHeader(file_2, &header);
                fclose(file_2);

                file_1 = fopen("r_lights_00004_body.txt", "r");

                char* data = bodyProcess(file_1, &header);
                convert_fits("test.fit", &header, data);

                free(data);
                fclose(file_1);
                break;

            case 0:
                exit(EXIT_SUCCESS);
            case 1:
                file_1 = open_fits_file();

                processHeader(file_1, &header);
                printf("-------------------------------------------\n");
                printHeader(&header);
                printf("-------------------------------------------\n");
                fclose(file_1);
                break;
            case 2:
                file_1 = open_fits_file();
                file_2 = open_fits_file();
                sum_fits_files(file_1, file_2);
                fclose(file_1);
                fclose(file_2);
                break;
            case 3:
                file_1 = open_fits_file();
                file_2 = open_fits_file();
                sub_fits_files(file_1, file_2);
                fclose(file_1);
                fclose(file_2);
                break;
            case 4:
                file_1 = open_fits_file();
                file_2 = open_fits_file();
                avg_fits_files(file_1, file_2);
                fclose(file_1);
                fclose(file_2);
                break;
            case 5:
                file_1 = open_fits_file();
                file_2 = open_fits_file();
                div_fits_files(file_1, file_2);
                fclose(file_1);
                fclose(file_2);
                break;
            case 6:
                file_1 = open_fits_file();
                convert_csv(file_1);
                fclose(file_1);
                break;
            case 7:
                file_1 = open_fits_file();
                convert_png(file_1);
                fclose(file_1);
                break;

            default:
                printf("Nombre Invalide.\n");
                continue;
        };
    };
    return 0;
};
