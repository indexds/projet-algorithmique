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

void fprintHeader(FILE* fits_file, Header* header){
    // Fill beginning of file with spaces
     fseek(fits_file, 0, SEEK_SET);
     char spaces[BLOCK_SIZE];
     for (int i = 0; i < BLOCK_SIZE; i++) {
         spaces[i] = '\0';
     };
    fwrite(spaces, BLOCK_SIZE, 1, fits_file);
    fseek(fits_file, 0, SEEK_SET);

    fprintf(fits_file, "SIMPLE  = %36s / file conforms to FITS standard ",      header->SIMPLE);
    fprintf(fits_file, "BITPIX  = %37d / number of bits per data pixel ",       header->BITPIX);
    fprintf(fits_file, "NAXIS   = %47d / number of data axes ",                 header->NAXIS);
    fprintf(fits_file, "NAXIS1  = %45d / length of data axis 1 ",               header->NAXIS1);
    fprintf(fits_file, "NAXIS2  = %45d / length of data axis 2 ",               header->NAXIS2);
    fprintf(fits_file, "NAXIS3  = %45d / length of data axis 3 ",               header->NAXIS3);
    fprintf(fits_file, "EXTEND  = %34s / FITS dataset contains extensions ",    header->EXTEND);
    fprintf(fits_file, "BZERO   = %39f / offset data range to ushort ",         header->BZERO);
    fprintf(fits_file, "BSCALE  = %44f / default scaling factor ",              header->BSCALE);
    fprintf(fits_file, "INSTRUME= %51s / instrument name ",                     header->INSTRUME);
    fprintf(fits_file, "DATE    = %36s / UTC date that file was created ",      header->DATE);
    fprintf(fits_file, "DATE-OBS= %37s / YYYY-MM-DDThh:mm:ss obs start ",       header->DATE_OBS);
    fprintf(fits_file, "XPIXSZ  = %46f / X pixel size microns ",                header->XPIXSZ);
    fprintf(fits_file, "YPIXSZ  = %46f / Y pixel size microns ",                header->YPIXSZ);
    fprintf(fits_file, "XBINNING= %47d / Camera binning mode ",                 header->XBINNING);
    fprintf(fits_file, "YBINNING= %47d / Camera binning mode ",                 header->YBINNING);
    fprintf(fits_file, "CCD-TEMP= %53f / CCD temp in C ",                       header->CCD_TEMP);
    fprintf(fits_file, "EXPTIME = %49f / Exposure time [s] ",                   header->EXPTIME);
    fprintf(fits_file, "BAYERPAT= %47s / Bayer color pattern ",                 header->BAYERPAT);
    fprintf(fits_file, "XBAYROFF= %43d / X offset of Bayer array ",             header->XBAYROFF);
    fprintf(fits_file, "YBAYROFF= %43d / Y offset of Bayer array ",             header->YBAYROFF);
    fprintf(fits_file, "PROGRAM = %53s / Software used ",                       header->PROGRAM);
    fprintf(fits_file, "END");
};

void printHeader(Header* header) {
    printf("SIMPLE  :  %s\n",      header->     SIMPLE  );
    printf("BITPIX  :  %d\n",      header->     BITPIX  );
    printf("NAXIS   :  %d\n",      header->     NAXIS   );
    printf("NAXIS1  :  %d\n",      header->     NAXIS1  );
    printf("NAXIS2  :  %d\n",      header->     NAXIS2  );
    printf("NAXIS3  :  %d\n",      header->     NAXIS3  );
    printf("EXTEND  :  %s\n",      header->     EXTEND  );
    printf("BZERO   :  %.2f\n",    header->     BZERO   );
    printf("BSCALE  :  %.2f\n",    header->     BSCALE  );
    printf("INSTRUME:  %s\n",      header->     INSTRUME);
    printf("DATE    :  %s\n",      header->     DATE    );
    printf("DATE-OBS:  %s\n",      header->     DATE_OBS);
    printf("XPIXSZ  :  %.2f\n",    header->     XPIXSZ  );
    printf("YPIXSZ  :  %.2f\n",    header->     YPIXSZ  );
    printf("XBINNING:  %d\n",      header->     XBINNING);
    printf("YBINNING:  %d\n",      header->     YBINNING);
    printf("CCD-TEMP:  %.2f\n",    header->     CCD_TEMP);
    printf("EXPTIME :  %.2f\n",    header->     EXPTIME );
    printf("BAYERPAT:  %s\n",      header->     BAYERPAT);
    printf("XBAYROFF:  %d\n",      header->     XBAYROFF);
    printf("YBAYROFF:  %d\n",      header->     YBAYROFF);
    printf("PROGRAM :  %s\n",      header->     PROGRAM );
};


void inject(Header* header, const char* KEYWORD, const char* value) {
    for(size_t i = 0; i < sizeof(header_names)/sizeof(header_names[0]); i++){
        if(strcmp(KEYWORD, header_names[i]) == 0){
            switch(i){
                case 0:
                    strncpy(header->SIMPLE, value, strlen(value));
                    break;
                case 1:
                    sscanf(value, "%d", &header->BITPIX);
                    break;
                case 2:
                    sscanf(value, "%d", &header->NAXIS);
                    break;
                case 3:
                    sscanf(value, "%d", &header->NAXIS1);
                    break;
                case 4:
                    sscanf(value, "%d", &header->NAXIS2);
                    break;
                case 5:
                    sscanf(value, "%d", &header->NAXIS3);
                    break;
                case 6:
                    strncpy(header->EXTEND, value, strlen(value));
                    break;
                case 7:
                    sscanf(value, "%f", &header->BZERO);
                    break;
                case 8:
                    sscanf(value, "%f", &header->BSCALE);
                    break;
                case 9:
                    strncpy(header->INSTRUME, value, strlen(value));
                    break;
                case 10:
                    strncpy(header->DATE, value, strlen(value));
                    break;
                case 11:
                    strncpy(header->DATE_OBS, value, strlen(value));
                    break;
                case 12:
                    sscanf(value, "%f", &header->XPIXSZ);
                    break;
                case 13:
                    sscanf(value, "%f", &header->YPIXSZ);
                    break;
                case 14:
                    sscanf(value, "%d", &header->XBINNING);
                    break;
                case 15:
                    sscanf(value, "%d", &header->YBINNING);
                    break;
                case 16:
                    sscanf(value, "%f", &header->CCD_TEMP);
                    break;
                case 17:
                    sscanf(value, "%f", &header->EXPTIME);
                    break;
                case 18:
                    strncpy(header->BAYERPAT, value, strlen(value));
                    break;
                case 19:
                    sscanf(value, "%d", &header->XBAYROFF);
                    break;
                case 20:
                    sscanf(value, "%d", &header->YBAYROFF);
                    break;
                case 21:
                    strncpy(header->PROGRAM, value, strlen(value));
                    break;
            };
        };
    };
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

    fseek(file, 0, SEEK_SET);
    fread(raw_header, BLOCK_SIZE, 1, file);

    // Maintenant on regarde pour chaque element de header_names ce qu'il y a entre "=" et "/" => la valeur
    for (size_t i = 0; i < sizeof(header_names) / sizeof(header_names[0]); i++) {

        char* found_adr = strstr(raw_header, header_names[i]); //renvoie l'adresse de la premiere instance de header_names[i] dans header

        char* value_start = strchr(found_adr, '=') + 1; //ptr après egal
        char* value_end = strchr(value_start, '/'); //ptr premier / après egal

        size_t value_length = value_end - value_start;


        //On enleve les espaces avant la valeur
        while (isspace(*value_start)) {
            value_start++;
            value_length--;
        };

        //On enleve les espaces apres la valeur
        while (isspace(value_start[value_length - 1])) {
            value_length--;
        };

        strncpy(value, value_start, value_length);
        value[value_length] = '\0';

        inject(header, header_names[i], value);

    };
    free(raw_header);
};