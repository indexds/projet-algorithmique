#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./convert.h"
#include "./header.h"
#include "./fits.h"
#include "./binary.h"


void convert_fits(char* fits_file_path, Header* header, char* data){
    FILE* fits_file = fopen(fits_file_path, "wb");

    char nil_buffer[BLOCK_SIZE];
    memset(nil_buffer, ' ', BLOCK_SIZE);
    fwrite(nil_buffer, 1, BLOCK_SIZE*2, fits_file);

    fseek(fits_file, 0, SEEK_SET);

    fprintFitsHeader(fits_file, header);

    fseek(fits_file, BLOCK_SIZE*2, SEEK_SET);
    char* buffer = (char*)malloc(sizeof(char)*4);
    int binary_buffer;

     for(int i = 0; i < header->NAXIS1*header->NAXIS2*header->NAXIS3*header->BITPIX/8; i+=2){
        memcpy(buffer, &data[i], 2);
        memcpy(buffer + 2, &data[i+1], 2);
        binary_buffer = le_to_be(binaryConvert(buffer));
        fwrite(&binary_buffer, sizeof(int), 1, fits_file);
    };

    free(buffer);
    fclose(fits_file);
};

void convert_csv(FILE* file){
    (void)file;
};

void convert_png(FILE* file){
    (void)file;
};