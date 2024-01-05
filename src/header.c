#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./header.h"


const char* header_names[] = {
    "SIMPLE",
    "BITPIX",
    "NAXIS",
    "NAXIS1",
    "NAXIS2",
    "NAXIS3",
    "EXTEND",
    "BZERO",
    "BSCALE",
    "INSTRUME",
    "DATE",
    "DATE-OBS",
    "XPIXSZ",
    "YPIXSZ",
    "XBINNING",
    "YBINNING",
    "CCD-TEMP",
    "EXPTIME",
    "BAYERPAT",
    "XBAYROFF",
    "YBAYROFF",
    "PROGRAM"
};

void fprintFitsHeader(FILE* fits_file, Header* header){
    // Fill beginning of file with spaces
     fseek(fits_file, 0, SEEK_SET);
     char spaces[BLOCK_SIZE];
     for (int i = 0; i < BLOCK_SIZE; i++) {
         spaces[i] = '\0';
     };
    fwrite(spaces, BLOCK_SIZE, 1, fits_file);
    fseek(fits_file, 0, SEEK_SET);

    fprintf(fits_file, "SIMPLE = %37s / file conforms to FITS standard ", header->SIMPLE);
    fprintf(fits_file, "BITPIX = %38d / number of bits per data pixel ",  header->BITPIX);
    fprintf(fits_file, "NAXIS = %49d / number of data axes ", header->NAXIS);
    fprintf(fits_file, "NAXIS1 = %46d / length of data axis 1 ", header->NAXIS1);
    fprintf(fits_file, "NAXIS2 = %46d / length of data axis 2 ", header->NAXIS2);
    fprintf(fits_file, "NAXIS3 = %46d / length of data axis 3 ", header->NAXIS3);
    fprintf(fits_file, "EXTEND = %35s / FITS dataset contains extensions ", header->EXTEND);
    fprintf(fits_file, "BZERO = %41f / offset data range to ushort ", header->BZERO);
    fprintf(fits_file, "BSCALE = %45f / default scaling factor ", header->BSCALE);
    fprintf(fits_file, "INSTRUME = %50s / instrument name ", header->INSTRUME);
    fprintf(fits_file, "DATE = %39s / UTC date that file was created ", header->DATE);
    fprintf(fits_file, "DATE-OBS = %36s / YYYY-MM-DDThh:mm:ss obs start ", header->DATE_OBS);
    fprintf(fits_file, "XPIXSZ = %47f / X pixel size microns ", header->XPIXSZ);
    fprintf(fits_file, "YPIXSZ = %47f / Y pixel size microns ", header->YPIXSZ);
    fprintf(fits_file, "XBINNING = %46d / Camera binning mode ", header->XBINNING);
    fprintf(fits_file, "YBINNING = %46d / Camera binning mode ", header->YBINNING);
    fprintf(fits_file, "CCD-TEMP = %52f / CCD temp in C ", header->CCD_TEMP);
    fprintf(fits_file, "EXPTIME = %49f / Exposure time [s] ", header->EXPTIME);
    fprintf(fits_file, "BAYERPAT = %46s / Bayer color pattern ", header->BAYERPAT);
    fprintf(fits_file, "XBAYROFF = %42d / X offset of Bayer array ", header->XBAYROFF);
    fprintf(fits_file, "YBAYROFF = %42d / Y offset of Bayer array ", header->YBAYROFF);
    fprintf(fits_file, "PROGRAM = %53s / Software used ", header->PROGRAM);
    fprintf(fits_file, "END ");
};

void printHeader(Header* header) {
    printf("SIMPLE  :  %s\n",      header->     SIMPLE  );
    printf("BITPIX  :  %d\n",      header->     BITPIX  );
    printf("NAXIS   :  %d\n",      header->     NAXIS   );
    printf("NAXIS1  :  %d\n",      header->     NAXIS1  );
    printf("NAXIS2  :  %d\n",      header->     NAXIS2  );
    printf("NAXIS3  :  %d\n",      header->     NAXIS3  );
    printf("EXTEND  :  %s\n",      header->     EXTEND  );
    printf("BZERO   :  %.2f\n",     header->     BZERO   );
    printf("BSCALE  :  %.2f\n",     header->     BSCALE  );
    printf("INSTRUME:  %s\n",      header->     INSTRUME);
    printf("DATE    :  %s\n",      header->     DATE    );
    printf("DATE-OBS:  %s\n",      header->     DATE_OBS);
    printf("XPIXSZ  :  %.2f\n",     header->     XPIXSZ  );
    printf("YPIXSZ  :  %.2f\n",     header->     YPIXSZ  );
    printf("XBINNING:  %d\n",      header->     XBINNING);
    printf("YBINNING:  %d\n",      header->     YBINNING);
    printf("CCD-TEMP:  %.2f\n",     header->     CCD_TEMP);
    printf("EXPTIME :  %.2f\n",     header->     EXPTIME );
    printf("BAYERPAT:  %s\n",      header->     BAYERPAT);
    printf("XBAYROFF:  %d\n",      header->     XBAYROFF);
    printf("YBAYROFF:  %d\n",      header->     YBAYROFF);
    printf("PROGRAM :  %s\n",      header->     PROGRAM );
};


void injecter(Header* header, const char* KEYWORD, const char* value) {
    if (strcmp(KEYWORD, "SIMPLE") == 0) {
        strncpy(header->SIMPLE, value, strlen(value));
    }

    else if (strcmp(KEYWORD, "BITPIX") == 0) {
        sscanf(value, "%d", &header->BITPIX);
    }

    else if (strcmp(KEYWORD, "NAXIS") == 0) {
        sscanf(value, "%d", &header->NAXIS);
    }

    else if (strcmp(KEYWORD, "NAXIS1") == 0) {
        sscanf(value, "%d", &header->NAXIS1);
    }

    else if (strcmp(KEYWORD, "NAXIS2") == 0) {
        sscanf(value, "%d", &header->NAXIS2);
    }

    else if (strcmp(KEYWORD, "NAXIS3") == 0) {
        sscanf(value, "%d", &header->NAXIS3);
    }

    else if (strcmp(KEYWORD, "EXTEND") == 0) {
        strncpy(header->EXTEND, value, strlen(value));
    }

    else if (strcmp(KEYWORD, "BZERO") == 0) {
        sscanf(value, "%f", &header->BZERO);
    }

    else if (strcmp(KEYWORD, "BSCALE") == 0) {
        sscanf(value, "%f", &header->BSCALE);
    }

    else if (strcmp(KEYWORD, "INSTRUME") == 0) {
        strncpy(header->INSTRUME, value, strlen(value));
    }

    else if (strcmp(KEYWORD, "DATE") == 0) {
       strncpy(header->DATE, value, strlen(value));
    }

    else if (strcmp(KEYWORD, "DATE-OBS") == 0) {
       strncpy(header->DATE_OBS, value, strlen(value));
    }

    else if (strcmp(KEYWORD, "XPIXSZ") == 0) {
        sscanf(value, "%f", &header->XPIXSZ);
    }

    else if (strcmp(KEYWORD, "YPIXSZ") == 0) {
        sscanf(value, "%f", &header->YPIXSZ);
    }

    else if (strcmp(KEYWORD, "XBINNING") == 0) {
        sscanf(value, "%d", &header->XBINNING);
    }

    else if (strcmp(KEYWORD, "YBINNING") == 0) {
        sscanf(value, "%d", &header->YBINNING);
    }

    else if (strcmp(KEYWORD, "CCD-TEMP") == 0) {
        sscanf(value, "%f", &header->CCD_TEMP);
    }

    else if (strcmp(KEYWORD, "EXPTIME") == 0) {
        sscanf(value, "%f", &header->EXPTIME);
    }

    else if (strcmp(KEYWORD, "BAYERPAT") == 0) {
        strncpy(header->BAYERPAT, value, strlen(value));
    }

    else if (strcmp(KEYWORD, "XBAYROFF") == 0) {
        sscanf(value, "%d", &header->XBAYROFF);
    }

    else if (strcmp(KEYWORD, "YBAYROFF") == 0) {
        sscanf(value, "%d", &header->YBAYROFF);
    }

    else if (strcmp(KEYWORD, "PROGRAM") == 0) {
        strncpy(header->PROGRAM, value, strlen(value));
    }
};


void processHeader(FILE* file, Header* header) {
    char* raw_header = (char*)malloc(2*BLOCK_SIZE);
    memset(raw_header, '\0', BLOCK_SIZE*2);
    char value[128];


    memset(header->SIMPLE, '\0', 128);
    memset(header->EXTEND, '\0', 128);
    memset(header->INSTRUME, '\0', 128);
    memset(header->DATE, '\0', 128);
    memset(header->DATE_OBS, '\0', 128);
    memset(header->BAYERPAT, '\0', 128);
    memset(header->PROGRAM, '\0', 128);

    fread(raw_header, BLOCK_SIZE-750, 1, file);
    // Maintenant on regarde pour chaque element de header_names ce qu'il y a entre "=" et "/" => la valeur
    for (size_t i = 0; i < sizeof(header_names) / sizeof(header_names[0]); i++) {

        char* found_adr = strstr(raw_header, header_names[i]); //renvoie l'adresse de la premiere instance de header_names[i] dans header
        char* found_equal = strchr(found_adr, '=');

        char* value_start = found_equal + 1; // début de la valeur => après le =
        char* value_end = strchr(value_start, '/'); //on cherche l'adresse du premier / à partir du =
        size_t value_length = value_end - value_start;


        //On enleve les espaces avant le string
        while (isspace(*value_start)) {
            value_start++;
            value_length--;
        };

        //On enleve les espaces apres le string
        while (value_length > 0 && isspace(value_start[value_length - 1])) {
            value_length--;
        };

        strncpy(value, value_start, value_length); // on met dans value le str du = jusqu'au /
        value[value_length] = '\0'; //on rajoute le null terminator à la fin de value

        injecter(header, header_names[i], value);


    };
    free(raw_header);
};