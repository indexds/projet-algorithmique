#include <stdio.h>
#include <string.h>
#include "./convert.h"
#include "./header.h"
#include "./fits.h"

void fill_with_nil(FILE* file) {

    // Buffer filled with nil (zero bytes)
    char nil_buffer[BLOCK_SIZE];
    memset(nil_buffer, 0, BLOCK_SIZE);

    // Write nil to the first two blocks
    for (int i = 0; i < 2; i++) {
        fwrite(nil_buffer, 1, BLOCK_SIZE, file);
    }
}

void convert_fits(FILE* new_file, Header* header, char** data){
    fseek(new_file, 0, SEEK_SET);
    fill_with_nil(new_file);
    fseek(new_file, 0, SEEK_SET);

    fprintf(new_file, "SIMPLE   =                    %s / conforms to FITS standard\n",                    header->SIMPLE);
    fprintf(new_file, "BITPIX   =                    %d / array data type\n",                              header->BITPIX);
    fprintf(new_file, "NAXIS    =                    %d / number of array dimensions\n",                   header->NAXIS);
    fprintf(new_file, "NAXIS1   =                    %d / size of dimension 1\n",                          header->NAXIS1);
    fprintf(new_file, "NAXIS2   =                    %d / size of dimension 2\n",                          header->NAXIS2);
    fprintf(new_file, "NAXIS3   =                    %d / size of dimension 3\n",                          header->NAXIS3);
    fprintf(new_file, "EXTEND   =                    %s / FITS dataset may contain extensions\n",          header->EXTEND);
    fprintf(new_file, "BZERO    =                    %f / offset data range to that of unsigned short\n",  header->BZERO);
    fprintf(new_file, "BSCALE   =                    %f / default scaling factor  \n",                     header->BSCALE);
    fprintf(new_file, "INSTRUME =                    %s / instrument name \n",                             header->INSTRUME);
    fprintf(new_file, "DATE     =                    %s / UTC date that FITS file was created  \n",        header->DATE);
    fprintf(new_file, "DATE-OBS =                    %s / YYYY-MM-DDThh:mm:ss observation start,\n",       header->DATE_OBS);
    fprintf(new_file, "XPIXSZ   =                    %f / X pixel size microns  \n",                       header->XPIXSZ);
    fprintf(new_file, "YPIXSZ   =                    %f / Y pixel size microns  \n",                       header->YPIXSZ);
    fprintf(new_file, "XBINNING =                    %d / Camera binning mode \n",                         header->XBINNING);
    fprintf(new_file, "YBINNING =                    %d / Camera binning mode \n",                         header->YBINNING);
    fprintf(new_file, "CCD-TEMP =                    %f / CCD temp in C     \n",                           header->CCD_TEMP);
    fprintf(new_file, "EXPTIME  =                    %f / Exposure time [s]  \n",                          header->EXPTIME);
    fprintf(new_file, "BAYERPAT =                    %s / Bayer color pattern\n",                          header->BAYERPAT);
    fprintf(new_file, "XBAYROFF =                    %d / X offset of Bayer array\n",                      header->XBAYROFF);
    fprintf(new_file, "YBAYROFF =                    %d / Y offset of Bayer array \n",                     header->YBAYROFF);
    fprintf(new_file, "PROGRAM  =                    %s / Software that created this HDU \n",              header->PROGRAM);
    fprintf(new_file, "END\n");

    fseek(new_file, BLOCK_SIZE*2, SEEK_SET);

    for(int i = 0; i < header->NAXIS1*3; i++){
        for(int j = 0; j < header->NAXIS2*2; j++){
            fprintf(new_file, "%s", &data[i][j]);
        };
    };

};

void convert_csv(FILE* file){
    (void)file;
};

void convert_png(FILE* file){
    (void)file;

};
//  int main(void){
//     FILE* file =fopen("../lights/r_lights_00001.fit", "r");
//     convert_csv(file);
//     fclose(file);
//     return 0;

//  };