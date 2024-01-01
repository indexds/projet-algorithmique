#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./convert.h"
#include "./header.h"
#include "./fits.h"
#include "./binary.h"

void fill_with_nil(FILE* file) {

    // Buffer filled with nil (zero bytes)
    char nil_buffer[BLOCK_SIZE];
    memset(nil_buffer, 0, BLOCK_SIZE);

    // Write nil to the first two blocks
    for (int i = 0; i < 2; i++) {
        fwrite(nil_buffer, 1, BLOCK_SIZE, file);
    };
};

void convert_fits(char* fits_file_path, Header* header, char* data){
    FILE* fits_file = fopen(fits_file_path, "w");
    fill_with_nil(fits_file);
    fseek(fits_file, 0, SEEK_SET);

    fprintf(fits_file, "SIMPLE   =                    %s / conforms to FITS standard\n",                    header->SIMPLE);
    fprintf(fits_file, "BITPIX   =                    %d / array data type\n",                              header->BITPIX);
    fprintf(fits_file, "NAXIS    =                    %d / number of array dimensions\n",                   header->NAXIS);
    fprintf(fits_file, "NAXIS1   =                    %d / size of dimension 1\n",                          header->NAXIS1);
    fprintf(fits_file, "NAXIS2   =                    %d / size of dimension 2\n",                          header->NAXIS2);
    fprintf(fits_file, "NAXIS3   =                    %d / size of dimension 3\n",                          header->NAXIS3);
    fprintf(fits_file, "EXTEND   =                    %s / FITS dataset may contain extensions\n",          header->EXTEND);
    fprintf(fits_file, "BZERO    =                    %f / offset data range to that of unsigned short\n",  header->BZERO);
    fprintf(fits_file, "BSCALE   =                    %f / default scaling factor  \n",                     header->BSCALE);
    fprintf(fits_file, "INSTRUME =                    %s / instrument name \n",                             header->INSTRUME);
    fprintf(fits_file, "DATE     =                    %s / UTC date that FITS file was created  \n",        header->DATE);
    fprintf(fits_file, "DATE-OBS =                    %s / YYYY-MM-DDThh:mm:ss observation start,\n",       header->DATE_OBS);
    fprintf(fits_file, "XPIXSZ   =                    %f / X pixel size microns  \n",                       header->XPIXSZ);
    fprintf(fits_file, "YPIXSZ   =                    %f / Y pixel size microns  \n",                       header->YPIXSZ);
    fprintf(fits_file, "XBINNING =                    %d / Camera binning mode \n",                         header->XBINNING);
    fprintf(fits_file, "YBINNING =                    %d / Camera binning mode \n",                         header->YBINNING);
    fprintf(fits_file, "CCD-TEMP =                    %f / CCD temp in C     \n",                           header->CCD_TEMP);
    fprintf(fits_file, "EXPTIME  =                    %f / Exposure time [s]  \n",                          header->EXPTIME);
    fprintf(fits_file, "BAYERPAT =                    %s / Bayer color pattern\n",                          header->BAYERPAT);
    fprintf(fits_file, "XBAYROFF =                    %d / X offset of Bayer array\n",                      header->XBAYROFF);
    fprintf(fits_file, "YBAYROFF =                    %d / Y offset of Bayer array \n",                     header->YBAYROFF);
    fprintf(fits_file, "PROGRAM  =                    %s / Software that created this HDU \n",              header->PROGRAM);
    fprintf(fits_file, "END\n");
    fclose(fits_file);


    fits_file = fopen(fits_file_path, "wb");
    fseek(fits_file, BLOCK_SIZE*2, SEEK_SET);
    
    char buffer[5];
     for(int i = 0; i < header->NAXIS1*header->NAXIS2*header->NAXIS3*header->BITPIX/8; i++){
            if (i%2 == 0){
                memset(buffer, '\0', sizeof(buffer));

                snprintf(buffer, 5, "%s%s", &data[i], &data[i + 1]);
                printf("%s", buffer);
                fwrite(binaryConvert(buffer), 4, 1, fits_file);
            };
         };

    fclose(fits_file);
};

void convert_csv(FILE* file){
    (void)file;
};

void convert_png(FILE* file){
    (void)file;

};