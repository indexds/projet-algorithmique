#include <stdio.h>
#include "./fits.c"
#include "./header.h"
#include "./structs.h"

int main(void){
    while(1){
        printf("------------- UTILITAIRE FITS -------------\n"
            "(1) LIRE LE HEADER\n"
            "(2) SOMMER DES IMAGES\n"
            "(3) SOUSTRAIRE DES IMAGES\n"
            "(4) MOYENNE DES IMAGES\n"
            "(5) DIVISER DES IMAGES\n"
            "(6) CONVERTIR EN CSV\n"
            "(7) CONVERTIR EN PNG\n"
            "-------------------------------------------\n"
        );
        FILE* file;
        FILE* file_1;
        FILE* file_2;
        int choix;
        scanf("%d", &choix);

        switch(choix){
            case 1:
                file = open_fits_file();
                read_header(file);
                fclose(file);
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
                file = open_fits_file();
                convert_csv(file);
                fclose(file);
                break;
            case 7:
                file = open_fits_file();
                convert_png(file);
                fclose(file);
                break;

            default:
                printf("Nombre Invalide.\n");
                continue;
        }
    }
    return 0;
}
