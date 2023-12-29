#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./fits.h"
#include "./header.h"
#include "./convert.h"

FILE* readBody(char* file_path) {

    char* output_file_name = (char*)malloc(sizeof(char)*250);

    char* last_slash = strrchr(file_path, '/');
    char* last_dot = strrchr(file_path, '.');

    strncpy(output_file_name, last_slash + 1, last_dot - last_slash - 1);
    strcat(output_file_name, "_body.txt");

    FILE* file = fopen(file_path, "r");
    FILE* body = fopen(output_file_name, "w");
    char substring[4000];
    char line[5000];

    while (fgets(line, sizeof(line), file) != NULL) {

        if (sscanf(line, "%[^>]", substring) == 1) {
            fprintf(body, "%s", substring);
        };
    };
    fclose(file);
    free(output_file_name);
    return body;
};

char** bodyProcess(char* file_path, Header* header){

    FILE* body_stream = readBody(file_path);

    //Allocation Memory
    char** data = (char**)malloc(sizeof(char*)*header->NAXIS1*header->NAXIS3);

    for(int i = 0; i<header->NAXIS1*header->NAXIS3; i++){
        data[i] = (char*)malloc(sizeof(char)*header->NAXIS2*2);
    };
    //Main program
    fseek(body_stream, BLOCK_SIZE*2, SEEK_SET);

    //Fill data with body_stream
    for(int i = 0; i < header->NAXIS1*3; i++){
        for(int j = 0; j < header->NAXIS2*2; j++){
            fread(&data[i][j], 2, 1, body_stream);
        };
    };

    return data;
};

void freeBody(char** data, Header* header){
    for(int i = 0; i<header->NAXIS1*header->NAXIS3; i++){
        free(data[i]);
    };
    free(data);
};

void sum_fits_files(FILE* file1, FILE* file2) {
    (void)file1;
    (void)file2;
};

void sub_fits_files(FILE* file1, FILE* file2) {
    (void)file1;
    (void)file2;
};

void avg_fits_files(FILE* file1, FILE* file2) {
    (void)file1;
    (void)file2;
};

void div_fits_files(FILE* file1, FILE* file2) {
    (void)file1;
    (void)file2;
};

FILE* open_fits_file(void){
    char file_path[150];
    FILE* file = NULL;

    while(file == NULL){
        printf("Rentrer le PATH du fichier: ");
        scanf("%s", file_path);
        file = fopen(file_path, "r");

        if(file == NULL){
            printf("File does not exist, please try again.\n");
        };

    };
    return file;
};

char* parse_fits_file(const char* file_path) { //Should return filename.txt
    char command[256];
    char* output_file_name = (char*)malloc(sizeof(char)*125);

    char* last_slash = strrchr(file_path, '/');
    char* last_dot = strrchr(file_path, '.');
    strncpy(output_file_name, last_slash + 1, last_dot - last_slash - 1);
    strcat(output_file_name, ".txt");

    snprintf(command, sizeof(command), "od --endian=big -w20 -A d -t x2z -v %s | cut -c 9- | tr -d ' ' > %s", file_path, output_file_name);

    system(command); // MODIFIER LES ARGUMENTS POUR AVOIR PAREIL QUE FIT7.TXT

    return output_file_name;

};