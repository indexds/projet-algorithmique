#include <stdio.h>
#include <stdlib.h>
#include "./header.h"
#include "./fits.h"
#include <string.h>

int main(void){
    Header header;
    FILE* file_1;
    FILE* file_2;
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
        (void)file_1;
        switch(choix){
            case 8: // TEST CASE
                file_1 = fopen("../lights/r_lights_00004.fit", "rb");
                file_2 = fopen("../lights/r_lights_00005.fit", "rb");
                output = fopen("./output.fit", "wb");

                sum_fits_files(file_1, file_2, output);

                fclose(file_1);
                fclose(file_2);
                fclose(output);
                break;

            case 0:
                exit(EXIT_SUCCESS);
            case 1:
                printf("PATH du fichier: ");
                scanf("%s", file_path);
                file_1 = fopen(file_path, "rb");
                processHeader(file_1, &header);
                printHeader(&header);
                break;
            case 2:
                printf("Not Implemented (SUM).");
                break;
            case 3:
                printf("Not Implemented (AVG).");
                break;
            case 4:
                printf("Not Implemented (SUB).");
                break;
            case 5:
                printf("Not Implemented (DIV).");
                break;
            case 6:
                printf("PATH du fichier: ");
                scanf("%s", file_path);

                char output_file_name[256];
                strcpy(output_file_name, "output_");
                strncat(output_file_name, strrchr(file_path, '/') + 1, strrchr(file_path, '.') - (strrchr(file_path, '/') + 1));
                strcat(output_file_name, ".csv");

                file_1 = fopen(file_path, "rb");
                output = fopen(output_file_name, "w");
                convert_csv(file_1, output);
                fclose(file_1);
                fclose(output);
                break;
            default:
                printf("Nombre Invalide.\n");
                continue;
        };
    };
    return 0;
};
