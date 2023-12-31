#ifndef FITS_FILE
#define FITS_FILE

int count_files(FILE* files[]);
int isCompatible(FILE* file1, FILE* file2, FILE* output_stream);

void sum_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void sub_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void avg_fits_files(FILE* file_tab[], FILE* output_stream);
void div_fits_files(FILE* file1, FILE* file2, FILE* output_stream);
void convert_csv(FILE* file, FILE* output_stream);

void generateMaster(char* directory, char* filename);
void generatePretraite(FILE* master_dark, FILE* master_flat, FILE* master_offset);

#endif