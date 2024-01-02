#ifndef FITS_FILE
#define FITS_FILE

#include "./header.h"
#define BLOCK_SIZE 2880

FILE* open_fits_file(void);
void readBody(char* file_path);
char* bodyProcess(FILE* body_stream, Header* header);
void sum_fits_files(FILE* file1, FILE* file2);
void sub_fits_files(FILE* file1, FILE* file2);
void avg_fits_files(FILE* file1, FILE* file2);
void div_fits_files(FILE* file1, FILE* file2);
char* parse_fits_file(const char* file_path);

#endif