#ifndef FITS_FILE
#define FITS_FILE

#include "./header.h"
#define BLOCK_SIZE 2880

void sum_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void sub_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void avg_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void div_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void convert_csv(FILE* file, FILE* output_stream);

#endif