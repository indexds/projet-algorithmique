#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./fits.h"
#include "./header.h"
#include "./convert.h"

FILE* readBody(FILE* file){
    char* raw_body = (char*)malloc(300 * 1000000);
    raw_body[0] = '\0';
    char line[2000];

    while (fgets(line, sizeof(line), file) != NULL) {
        char substring[300];
        if (sscanf(line, "%[^>]", substring) == 1) {
            if (strlen(raw_body) + strlen(substring) < 300 * 1000000 - 1) {
                strncat(raw_body, substring, strlen(substring));
            } else {
                // evite le buffer overflow
                break;
            }
        }
    }
    FILE* body = fopen("./body.txt", "w");
    fprintf(body, "%s", raw_body);

    return body;
};

char** bodyProcess(FILE* file, Header* header){

    fseek(file, 0, SEEK_SET);
    FILE* body_stream = readBody(file);

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
    printf("Rentrer le PATH du fichier: ");
    scanf("%s", file_path);
    FILE* file = fopen(file_path, "r");

    return file;
};

FILE* create_fits_file(void){
    char file_path[150];
    printf("Rentrer le PATH du fichier: ");
    scanf("%s", file_path);
    FILE* file = fopen(file_path, "w");

    return file;
};

void parse_fits_file(const char* file_path) {
    char command[256];
    snprintf(command, sizeof(command), "%s %s", "./parser.sh", file_path);
    system(command);
};


int main() {
    Header header;
    FILE* file = fopen("../fit7.txt", "r");
    processHeader(file, &header);

    char** data = bodyProcess(readBody(file), &header);

    // for(int i = 0; i< header.NAXIS1*3; i++){
    //     for(int j = 0; j<header.NAXIS2*2; j++){
    //         printf("%s", &data[i][j]);
    //     };
    // };

    convert_fits(create_fits_file(), &header, data);

    freeBody(data, &header);
    fclose(file);
    return 0;
};