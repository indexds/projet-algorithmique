#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./header.h"

void injecter(Header* header, char* KEYWORD, char* word) {
    if (strcmp(KEYWORD, "SIMPLE") == 0) {
        sscanf(word, "%9s", header->SIMPLE);
    }
    else if (strcmp(KEYWORD, "BITPIX") == 0) {
        sscanf(word, "%d", &header->BITPIX);
    }
    else if (strcmp(KEYWORD, "NAXIS") == 0) {
        sscanf(word, "%d", &header->NAXIS);
    }
    else if (strcmp(KEYWORD, "NAXIS1") == 0) {
        sscanf(word, "%d", &header->NAXIS1);
    }
    else if (strcmp(KEYWORD, "NAXIS2") == 0) {
        sscanf(word, "%d", &header->NAXIS2);
    }
    else if (strcmp(KEYWORD, "NAXIS3") == 0) {
        sscanf(word, "%d", &header->NAXIS3);
    }
    else if (strcmp(KEYWORD, "EXTEND") == 0) {
        sscanf(word, "%9s", header->EXTEND);
    }
    else if (strcmp(KEYWORD, "BZERO") == 0) {
        sscanf(word, "%f", &header->BZERO);
    }
    else if (strcmp(KEYWORD, "BSCALE") == 0) {
        sscanf(word, "%f", &header->BSCALE);
    }
    else if (strcmp(KEYWORD, "INSTRUME") == 0) {
        sscanf(word, "%99s", header->INSTRUME);
    }
    else if (strcmp(KEYWORD, "DATE") == 0) {
        sscanf(word, "'%99[^']", header->DATE);
    }
    else if (strcmp(KEYWORD, "DATE-OBS") == 0) {
        sscanf(word, "'%99[^']", header->DATEOBS);
    }
    else if (strcmp(KEYWORD, "XPIXSZ") == 0) {
        sscanf(word, "%f", &header->XPIXSZ);
    }
    else if (strcmp(KEYWORD, "YPIXSZ") == 0) {
        sscanf(word, "%f", &header->YPIXSZ);
    }
    else if (strcmp(KEYWORD, "XBINNING") == 0) {
        sscanf(word, "%d", &header->XBINNING);
    }
    else if (strcmp(KEYWORD, "YBINNING") == 0) {
        sscanf(word, "%d", &header->YBINNING);
    }
    else if (strcmp(KEYWORD, "CCD-TEMP") == 0) {
        sscanf(word, "%f", &header->CCDTEMP);
    }
    else if (strcmp(KEYWORD, "EXPTIME") == 0) {
        sscanf(word, "%f", &header->EXPTIME);
    }
    else if (strcmp(KEYWORD, "BAYERPAT") == 0) {
        sscanf(word, "%49s", header->BAYERPAT);
    }
    else if (strcmp(KEYWORD, "XBAYROFF") == 0) {
        sscanf(word, "%d", &header->XBAYROFF);
    }
    else if (strcmp(KEYWORD, "YBAYROFF") == 0) {
        sscanf(word, "%d", &header->YBAYROFF);
    }
    else if (strcmp(KEYWORD, "PROGRAM") == 0) {
        sscanf(word, "'%49s", header->PROGRAM);
    }
}
