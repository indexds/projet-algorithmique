#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./header.h"

const char* header_names[] = {
    "SIMPLE=",
    "BITPIX=",
    "NAXIS=",
    "NAXIS1=",
    "NAXIS2=",
    "NAXIS3=",
    "EXTEND=",
    "BZERO=",
    "BSCALE=",
    "INSTRUME=",
    "DATE=",
    "DATE-OBS=",
    "XPIXSZ=",
    "YPIXSZ=",
    "XBINNING=",
    "YBINNING=",
    "CCD-TEMP=",
    "EXPTIME=",
    "BAYERPAT=",
    "XBAYROFF=",
    "YBAYROFF=",
    "PROGRAM="
};

void printHeader(Header* header) {
    printf("SIMPLE: %s\n",    header->     SIMPLE   );
    printf("BITPIX: %d\n",    header->     BITPIX   );
    printf("NAXIS: %d\n",     header->     NAXIS    );
    printf("NAXIS1: %d\n",    header->     NAXIS1   );
    printf("NAXIS2: %d\n",    header->     NAXIS2   );
    printf("NAXIS3: %d\n",    header->     NAXIS3   );
    printf("EXTEND: %s\n",    header->     EXTEND   );
    printf("BZERO: %lf\n",    header->     BZERO    );
    printf("BSCALE: %lf\n",   header->     BSCALE   );
    printf("INSTRUME: %s\n",  header->     INSTRUME );
    printf("DATE: %s\n",      header->     DATE     );
    printf("DATE-OBS: %s\n",  header->     DATE_OBS );
    printf("XPIXSZ: %lf\n",   header->     XPIXSZ   );
    printf("YPIXSZ: %lf\n",   header->     YPIXSZ   );
    printf("XBINNING: %d\n",  header->     XBINNING );
    printf("YBINNING: %d\n",  header->     YBINNING );
    printf("CCD-TEMP: %lf\n", header->     CCD_TEMP );
    printf("EXPTIME: %lf\n",  header->     EXPTIME  );
    printf("BAYERPAT: %s\n",  header->     BAYERPAT );
    printf("XBAYROFF: %d\n",  header->     XBAYROFF );
    printf("YBAYROFF: %d\n",  header->     YBAYROFF );
    printf("PROGRAM: %s\n",   header->     PROGRAM  );
};


void injecter(Header* header, const char* KEYWORD, const char* value) {
    if (strcmp(KEYWORD, "SIMPLE=") == 0) {
        snprintf(header->SIMPLE, sizeof(header->SIMPLE), "%s", value);
    }

    else if (strcmp(KEYWORD, "BITPIX=") == 0) {
        sscanf(value, "%d", &header->BITPIX);
    }

    else if (strcmp(KEYWORD, "NAXIS=") == 0) {
        sscanf(value, "%d", &header->NAXIS);
    }

    else if (strcmp(KEYWORD, "NAXIS1=") == 0) {
        sscanf(value, "%d", &header->NAXIS1);
    }

    else if (strcmp(KEYWORD, "NAXIS2=") == 0) {
        sscanf(value, "%d", &header->NAXIS2);
    }

    else if (strcmp(KEYWORD, "NAXIS3=") == 0) {
        sscanf(value, "%d", &header->NAXIS3);
    }

    else if (strcmp(KEYWORD, "EXTEND=") == 0) {
        snprintf(header->EXTEND, sizeof(header->EXTEND), "%s", value);
    }

    else if (strcmp(KEYWORD, "BZERO=") == 0) {
        sscanf(value, "%lf", &header->BZERO);
    }

    else if (strcmp(KEYWORD, "BSCALE=") == 0) {
        sscanf(value, "%lf", &header->BSCALE);
    }

    else if (strcmp(KEYWORD, "INSTRUME=") == 0) {
        snprintf(header->INSTRUME, sizeof(header->INSTRUME), "%s", value);
    }

    else if (strcmp(KEYWORD, "DATE=") == 0) {
        snprintf(header->DATE, sizeof(header->DATE), "%s", value);
    }

    else if (strcmp(KEYWORD, "DATE-OBS=") == 0) {
        snprintf(header->DATE_OBS, sizeof(header->DATE_OBS), "%s", value);
    }

    else if (strcmp(KEYWORD, "XPIXSZ=") == 0) {
        sscanf(value, "%lf", &header->XPIXSZ);
    }

    else if (strcmp(KEYWORD, "YPIXSZ=") == 0) {
        sscanf(value, "%lf", &header->YPIXSZ);
    }

    else if (strcmp(KEYWORD, "XBINNING=") == 0) {
        sscanf(value, "%d", &header->XBINNING);
    }

    else if (strcmp(KEYWORD, "YBINNING=") == 0) {
        sscanf(value, "%d", &header->YBINNING);
    }

    else if (strcmp(KEYWORD, "CCD-TEMP=") == 0) {
        sscanf(value, "%lf", &header->CCD_TEMP);
    }

    else if (strcmp(KEYWORD, "EXPTIME=") == 0) {
        sscanf(value, "%lf", &header->EXPTIME);
    }

    else if (strcmp(KEYWORD, "BAYERPAT=") == 0) {
        snprintf(header->BAYERPAT, sizeof(header->BAYERPAT), "%s", value);
    }

    else if (strcmp(KEYWORD, "XBAYROFF=") == 0) {
        sscanf(value, "%d", &header->XBAYROFF);
    }

    else if (strcmp(KEYWORD, "YBAYROFF=") == 0) {
        sscanf(value, "%d", &header->YBAYROFF);
    }

    else if (strcmp(KEYWORD, "PROGRAM=") == 0) {
        snprintf(header->PROGRAM, sizeof(header->PROGRAM), "%s", value);
    }
};


void processHeader(FILE* file, Header* header) {
    char* raw_header = (char*)malloc(3000);
    raw_header[0] = '\0';
    char line[500];

    while (fgets(line, sizeof(line), file) != NULL) {
        char substring[300];
        if (sscanf(line, "%*[^>]>%[^<]", substring) == 1) {
            if (strlen(raw_header) + strlen(substring) < 2999) {
                strncat(raw_header, substring, strlen(substring));
            } else {
                // evite le buffer overflow
                break;
            }
        }
    } // actuellement header contient tous les strings concaténés de chaque ligne entre > et <

    // Maintenant on regarde pour chaque element de header_names ce qu'il y a entre "=" et "/" => la valeur
    for (size_t i = 0; i < sizeof(header_names) / sizeof(header_names[0]); ++i) {
        char* found_adr = strstr(raw_header, header_names[i]); //renvoie l'adresse de la premiere instance de header_names[i] dans header

        char* value_start = found_adr + strlen(header_names[i]); // début de la valeur => après le =
        char* value_end = strchr(value_start, '/'); //on cherche l'adresse du premier / à partir du =

        size_t value_length = value_end - value_start;
        char value[300];
        strncpy(value, value_start, value_length); // on met dans value le str du = jusqu'au /
        value[value_length] = '\0'; //magie noire, ça marche pas sans

        injecter(header, header_names[i], value);


    }
    free(raw_header);
};


// int main() {
//     Header header;
//     FILE* file = fopen("../fit7.txt", "r");
//     processHeader(file, &header);
//     printHeader(&header);
//     fclose(file);
//     return 0;
// };