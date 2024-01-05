#ifndef FITS_FILE
#define FITS_FILE

void sum_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void sub_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void avg_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void div_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void convert_csv(FILE* file, FILE* output_stream);

#endif