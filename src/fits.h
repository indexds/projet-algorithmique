#ifndef FITS_FILE
#define FITS_FILE

#define MAX_BYTE_VALUE 11111111

int count_files(FILE* files[]);
int isCompatible(FILE* file1, FILE* file2, FILE* output_stream);
void sum_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void sub_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void avg_fits_files(FILE* file_tab[], FILE* output_stream);
void div_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void convert_csv(FILE* file, FILE* output_stream);

#endif