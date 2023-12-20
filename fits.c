#include <stdio.h>
#include <stdlib.h>

void read_header(FILE* file);

void sum_fits_files(FILE* file1, FILE* file2);
void sub_fits_files(FILE* file1, FILE* file2);
void avg_fits_files(FILE* file1, FILE* file2);
void div_fits_files(FILE* file1, FILE* file2);

FILE* convert_csv(FILE* file);
FILE* convert_png(FILE* file);

FILE* open_fits_file(void){
    char file_path[150];
    scanf("Rentrer le PATH du fichier: %s", file_path);
    FILE* file = fopen(file_path, "r");

    return file;
}

void parse_fits_file(const char* file_path) {
    char command[256];
    snprintf(command, sizeof(command), "%s %s", "./parser.sh", file_path);
    system(command);
}
