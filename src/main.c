#include <stdio.h>
#include <stdlib.h>
#include "./header.h"
#include "./fits.h"

int main(void){
    //Header header;
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
        (void)file_1;
        switch(choix){
            case 8: // TEST CASE
                file_1 = fopen("../lights/r_lights_00004.fit", "rb");
                file_2 = fopen("../lights/r_lights_00005.fit", "rb");
                FILE* output = fopen("../lights/output.fit", "wb");

                sum_fits_files(file_1, file_2, output);

                fclose(file_1);
                fclose(file_2);
                fclose(output);
                break;

            case 0:
                exit(EXIT_SUCCESS);
            case 1:
                printf("Not Implemented.");
                break;
            case 2:
                printf("Not Implemented.");
                break;
            case 3:
                printf("Not Implemented.");
                break;
            case 4:
                printf("Not Implemented.");
                break;
            case 5:
                printf("Not Implemented.");
                break;
            case 6:
                printf("Not Implemented.");
                break;
            case 7:
                printf("Not Implemented.");
                break;
            default:
                printf("Nombre Invalide.\n");
                continue;
        };
    };
    return 0;
};
