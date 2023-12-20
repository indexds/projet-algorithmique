FILE* open_fits_file(void);

void read_header(FILE* file);

void sum_fits_files(FILE* file1, FILE* file2);
void sub_fits_files(FILE* file1, FILE* file2);
void avg_fits_files(FILE* file1, FILE* file2);
void div_fits_files(FILE* file1, FILE* file2);

FILE* convert_csv(FILE* file);
FILE* convert_png(FILE* file);