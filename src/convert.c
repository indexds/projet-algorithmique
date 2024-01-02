#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./convert.h"
#include "./header.h"
#include "./fits.h"
#include "./binary.h"

void fill_with_nil(FILE* file) {
    char nil_buffer[BLOCK_SIZE];
    memset(nil_buffer, ' ', BLOCK_SIZE);
    fwrite(nil_buffer, 1, BLOCK_SIZE*2, file);
};


void convert_fits(char* fits_file_path, Header* header, char* data){
    FILE* fits_file = fopen(fits_file_path, "wb");
    fseek(fits_file, 0, SEEK_SET);
    fill_with_nil(fits_file);
    fseek(fits_file, 0, SEEK_SET);

    fprintf(fits_file, "SIMPLE   =                    %s / conforms to FITS standard ",                    header->SIMPLE);
    fprintf(fits_file, "BITPIX   =                    %d / array data type ",                              header->BITPIX);
    fprintf(fits_file, "NAXIS    =                    %d / number of array dimensions ",                   header->NAXIS);
    fprintf(fits_file, "NAXIS1   =                    %d / size of dimension 1 ",                          header->NAXIS1);
    fprintf(fits_file, "NAXIS2   =                    %d / size of dimension 2 ",                          header->NAXIS2);
    fprintf(fits_file, "NAXIS3   =                    %d / size of dimension 3 ",                          header->NAXIS3);
    fprintf(fits_file, "EXTEND   =                    %s / FITS dataset may contain extensions ",          header->EXTEND);
    fprintf(fits_file, "BZERO    =                    %f / offset data range to that of unsigned short ",  header->BZERO);
    fprintf(fits_file, "BSCALE   =                    %f / default scaling factor ",                     header->BSCALE);
    fprintf(fits_file, "INSTRUME =                    %s / instrument name ",                             header->INSTRUME);
    fprintf(fits_file, "DATE     =                    %s / UTC date that FITS file was created ",        header->DATE);
    fprintf(fits_file, "DATE-OBS =                    %s / YYYY-MM-DDThh:mm:ss observation start ",       header->DATE_OBS);
    fprintf(fits_file, "XPIXSZ   =                    %f / X pixel size microns ",                       header->XPIXSZ);
    fprintf(fits_file, "YPIXSZ   =                    %f / Y pixel size microns ",                       header->YPIXSZ);
    fprintf(fits_file, "XBINNING =                    %d / Camera binning mode ",                         header->XBINNING);
    fprintf(fits_file, "YBINNING =                    %d / Camera binning mode ",                         header->YBINNING);
    fprintf(fits_file, "CCD-TEMP =                    %f / CCD temp in C ",                                header->CCD_TEMP);
    fprintf(fits_file, "EXPTIME  =                    %f / Exposure time [s] ",                          header->EXPTIME);
    fprintf(fits_file, "BAYERPAT =                    %s / Bayer color pattern ",                          header->BAYERPAT);
    fprintf(fits_file, "XBAYROFF =                    %d / X offset of Bayer array ",                      header->XBAYROFF);
    fprintf(fits_file, "YBAYROFF =                    %d / Y offset of Bayer array ",                     header->YBAYROFF);
    fprintf(fits_file, "PROGRAM  =                    %s / Software that created this HDU ",              header->PROGRAM);
    fprintf(fits_file, "END\n");

    fseek(fits_file, BLOCK_SIZE*2 + 1, SEEK_SET);
    char* buffer = (char*)malloc(sizeof(char)*2);
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