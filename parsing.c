#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./header.h"
#include "./injection.h"

Header parse(FILE* file){
    Header header;
    char word[50];
    char buffer[50];

    char* headerNames[] = {
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

    while(fscanf(file,"%s", word)){
        

    };

    return header;
}


int main(void){
    FILE* file = fopen("./lights/r_lights_00001.fit", "r");
    Header header = parse(file);
    printf("SIMPLE: %s\n", header.SIMPLE);
    printf("BITPIX: %d\n", header.BITPIX);
    printf("NAXIS: %d\n", header.NAXIS);
    printf("NAXIS1: %d\n", header.NAXIS1);
    printf("NAXIS2: %d\n", header.NAXIS2);
    printf("NAXIS3: %d\n", header.NAXIS3);
    printf("EXTEND: %s\n", header.EXTEND);
    printf("BZERO: %f\n", header.BZERO);
    printf("BSCALE: %f\n", header.BSCALE);
    printf("INSTRUME: %s\n", header.INSTRUME);
    printf("DATE: %s\n", header.DATE);
    printf("DATEOBS: %s\n", header.DATEOBS);
    printf("XPIXSZ: %f\n", header.XPIXSZ);
    printf("YPIXSZ: %f\n", header.YPIXSZ);
    printf("XBINNING: %d\n", header.XBINNING);
    printf("YBINNING: %d\n", header.YBINNING);
    printf("CCDTEMP: %f\n", header.CCDTEMP);
    printf("EXPTIME: %f\n", header.EXPTIME);
    printf("BAYERPAT: %s\n", header.BAYERPAT);
    printf("XBAYROFF: %d\n", header.XBAYROFF);
    printf("YBAYROFF: %d\n", header.YBAYROFF);
    printf("PROGRAM: %s\n", header.PROGRAM);

    fclose(file);
    return 0;

}