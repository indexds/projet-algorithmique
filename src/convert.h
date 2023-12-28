#ifndef CONVERT_FILE
#define CONVERT_FILE

#include "./header.h"
void convert_csv(FILE* file);
void convert_png(FILE* file);
void convert_fits(FILE* file, Header* header, char** data);

#endif