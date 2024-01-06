#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "./fits.h"
#include "./header.h"

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
    fseek(file1, BLOCK_SIZE, SEEK_SET);
    fseek(file2, BLOCK_SIZE, SEEK_SET);
    fseek(output_stream, BLOCK_SIZE, SEEK_SET);

    char buffer1[2];
    char buffer2[2];
    char buffer3[2];

     while(fread(buffer1, 1, 2, file1) != 0 && fread(buffer2, 1, 2, file2) != 0){
        //operation de sommation buffer3 = buffer2+buffer1 (gaffe overflow si FF+FF => FF)
        buffer3[0] = (buffer1[0] + buffer2[0] > MAX_BYTE_VALUE)? MAX_BYTE_VALUE : buffer1[0]+buffer2[0];
        buffer3[1] = (buffer1[1] + buffer2[1] > MAX_BYTE_VALUE)? MAX_BYTE_VALUE : buffer1[1]+buffer2[1];
        fwrite(buffer3, 2, 1, output_stream);
    };
};

void sub_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
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
    fseek(file1, BLOCK_SIZE, SEEK_SET);
    fseek(file2, BLOCK_SIZE, SEEK_SET);
    fseek(output_stream, BLOCK_SIZE, SEEK_SET);

    char buffer1[2];
    char buffer2[2];
    char buffer3[2];

     while(fread(buffer1, 1, 2, file1) != 0 && fread(buffer2, 1, 2, file2) != 0){
        //operation de sommation buffer3 = buffer2+buffer1 (gaffe overflow si FF+FF => FF)
        buffer3[0] = (buffer1[0] - buffer2[0] > MAX_BYTE_VALUE)? MAX_BYTE_VALUE : buffer1[0]-buffer2[0];
        buffer3[1] = (buffer1[1] - buffer2[1] > MAX_BYTE_VALUE)? MAX_BYTE_VALUE : buffer1[1]-buffer2[1];
        fwrite(buffer3, 2, 1, output_stream);
    };

};

void avg_fits_files(FILE* file_tab[], FILE* output_stream) {
    //cette ligne fait capoter toute la fonction , il retourne n=1 pour je ne sais quelle raison
    int n = (int)sizeof(file_tab)/sizeof(file_tab[0]);
    printf("Taille du tableau de fichier %d \n ",n);
    //on somme toutes les images
    FILE* buffer =file_tab[0];
    for (int i= 1 ; i < n ; i++){
        sum_fits_files(buffer,file_tab[i], output_stream);
        printf("Images sommées \n ");
        buffer=output_stream;
    }
    printf("Images sommées à la fin \n ");
    fseek(output_stream, BLOCK_SIZE, SEEK_SET);

    char buffer3[2];

     while(fread(buffer3, 1, 2, output_stream) != 0){
        //operation de sommation buffer3 = buffer2+buffer1 (gaffe overflow si FF+FF => FF)
        buffer3[0] = (buffer3[0]/n > MAX_BYTE_VALUE)? MAX_BYTE_VALUE : buffer3[0]/n;
        buffer3[1] = (buffer3[1]/n > MAX_BYTE_VALUE)? MAX_BYTE_VALUE : buffer3[1]/n;
        fwrite(buffer3, 2, 1, output_stream);
    };

};

void div_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
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
    fseek(file1, BLOCK_SIZE, SEEK_SET);
    fseek(file2, BLOCK_SIZE, SEEK_SET);
    fseek(output_stream, BLOCK_SIZE, SEEK_SET);

    char buffer1[2];
    char buffer2[2];
    char buffer3[2];

     while(fread(buffer1, 1, 2, file1) != 0 && fread(buffer2, 1, 2, file2) != 0){
        //operation de sommation buffer3 = buffer2+buffer1 (gaffe overflow si FF+FF => FF)
        double result1 = (buffer2[0] != 0) ? (double)buffer1[0] / (double)buffer2[0] : 0;
        double result2 = (buffer2[1] != 0) ? (double)buffer1[1] / (double)buffer2[1] : 0;

        // Convert results back to bytes
        uint8_t result_bytes1 = (result1 > MAX_BYTE_VALUE) ? MAX_BYTE_VALUE : (uint8_t)result1;
        uint8_t result_bytes2 = (result2 > MAX_BYTE_VALUE) ? MAX_BYTE_VALUE : (uint8_t)result2;

        // Store results in buffer3
        buffer3[0] = result_bytes1;
        buffer3[1] = result_bytes2;

        // Write buffer3 to the output stream
        fwrite(buffer3, 1, 2, output_stream);
    };
};

void convert_csv(FILE* file, FILE* output_stream){
    int byte;
    fseek(file, BLOCK_SIZE, SEEK_SET);
    while ((byte = fgetc(file)) != EOF) {
        fprintf(output_stream, "%02X;", byte);
    };
};

// FILE* open_fits_file_reading(char name){
//     char file_path[256];
//     char filename[256];
//     printf("PATH du fichier: ");
//     scanf("%s", file_path);
//     sprintf(filename, "../lights/%s.fit", name);
//     printf("Ouverture de \"%s\"", filename);
//     FILE *file = fopen(filename,"rb");
//     return file;
// }