#ifndef CONVERT_FILE
#define CONVERT_FILE

#include "./header.h"

void convert_fits(char* fits_file_path, Header* header, char* data);
void convert_csv(FILE* file);
void convert_png(FILE* file);

#endif