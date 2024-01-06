#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "./fits.h"
#include "./header.h"

int count_files(FILE* files[]) {
    int count = 0;
    while (files[count] != NULL) {
        count++;
    }
    return count;
};


int isCompatible(FILE* file1, FILE* file2, FILE* output_stream){
    Header header1;
    Header header2;
    processHeader(file1, &header1);
    processHeader(file2, &header2);

    if(strcmp(header1.SIMPLE, "T") != 0 || strcmp(header2.SIMPLE, "T") != 0){
        printf("FITS file does not conform to standard, exiting.");
        return 1;
    };

    if(header1.NAXIS1 != header2.NAXIS1 ||
       header1.NAXIS2 != header2.NAXIS2 ||
       header1.NAXIS3 != header2.NAXIS3 ||
       header1.BITPIX != header2.BITPIX){
        printf("Image Formats are different, exiting.");
        return 1;
    };
    fprintFitsHeader(output_stream, &header1);
    fseek(file1, BLOCK_SIZE, SEEK_SET);
    fseek(file2, BLOCK_SIZE, SEEK_SET);
    fseek(output_stream, BLOCK_SIZE, SEEK_SET);
    return 0;
};


void sum_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    if (isCompatible(file1, file2, output_stream) == 1) {
        return;
    }

    unsigned char buffer1;
    unsigned char buffer2;
    unsigned char buffer3;

    while (fread(&buffer1, 1, 1, file1) != 0 && fread(&buffer2, 1, 1, file2) != 0) {

        buffer3 = buffer1 + buffer2;
        fwrite(&buffer3, 1, 1, output_stream);
    };
};


void sub_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    if(isCompatible(file1, file2, output_stream) == 1){
        return;
    };

    unsigned char buffer1;
    unsigned char buffer2;
    unsigned char buffer3;

    while (fread(&buffer1, 1, 1, file1) != 0 && fread(&buffer2, 1, 1, file2) != 0) {

        buffer3 = buffer1 - buffer2;
        fwrite(&buffer3, 1, 1, output_stream);
    };
};


void avg_fits_files(FILE* file_tab[], FILE* output_stream) {
    int n = count_files(file_tab);
    char buffer3;

    FILE* buffer = file_tab[0];
    fseek(buffer, BLOCK_SIZE, SEEK_SET);

    for (int i = 1; i < n; i++){

        isCompatible(buffer, file_tab[i], output_stream);
        sum_fits_files(buffer, file_tab[i], output_stream);
        buffer = output_stream;

    };

     while(fread(&buffer3, 1, 1, output_stream) != 0){
        buffer3 /= n;
        fwrite(&buffer3, 1, 1, output_stream);
    };
};


void div_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    if(isCompatible(file1, file2, output_stream) == 1){
        return;
    };

    unsigned char buffer1;
    unsigned char buffer2;
    unsigned char buffer3;

     while(fread(&buffer1, 1, 1, file1) != 0 && fread(&buffer2, 1, 1, file2) != 0){

        if(buffer2 == 0){
            buffer3 = buffer1;
        }
        else{
            buffer3 = buffer1 / buffer2;
        }

        fwrite(&buffer3, 1, 1, output_stream);
    };
};


void convert_csv(FILE* file, FILE* output_stream){
    int byte;
    fseek(file, BLOCK_SIZE, SEEK_SET);
    while ((byte = fgetc(file)) != EOF) {
        fprintf(output_stream, "%02X;", byte);
    };
};