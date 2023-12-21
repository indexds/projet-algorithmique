#ifndef FITS_FILE
#define FITS_FILE

#include "./header.h"

FILE* open_fits_file(void);
void sum_fits_files(FILE* file1, FILE* file2);
void sub_fits_files(FILE* file1, FILE* file2);
void avg_fits_files(FILE* file1, FILE* file2);
void div_fits_files(FILE* file1, FILE* file2);
void freeBody(char*** data, Header* header);

#endif