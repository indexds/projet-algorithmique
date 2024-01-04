#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./fits.h"
#include "./header.h"
#include "./binary.h"

void sum_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    Header header1;
    Header header2;
    processHeader(file1, &header1);
    processHeader(file2, &header2);

    if(strcmp(header1.SIMPLE, "T") != 0 || strcmp(header2.SIMPLE, "T") != 0){
        printf("FITS file does not conform to standard, exiting.");
        return;
    };

    if(header1.NAXIS1 != header2.NAXIS1 ||
       header1.NAXIS2 != header2.NAXIS2 ||
       header1.NAXIS3 != header2.NAXIS3 ||
       header1.BITPIX != header2.BITPIX){
        printf("Image Formats are different, exiting.");
        return;
    };
    fprintFitsHeader(output_stream, &header1);
    printHeader(&header1);
    fseek(file1, BLOCK_SIZE-1, SEEK_SET);
    fseek(file2, BLOCK_SIZE-1, SEEK_SET);
    fseek(output_stream, BLOCK_SIZE-1, SEEK_SET);

    char buffer1[2];
    char buffer2[2];


     while(fread(buffer1, 1, 2, file1) != 0 && fread(buffer2, 1, 2, file2) != 0){
        fwrite(buffer1, 2, 1, output_stream);
    };
};

void sub_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    (void)file1;
    (void)file2;
    (void)output_stream;

};

void avg_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    (void)file1;
    (void)file2;
    (void)output_stream;
};

void div_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    (void)file1;
    (void)file2;
    (void)output_stream;
};
