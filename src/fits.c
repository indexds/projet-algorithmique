#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./fits.h"
#include "./header.h"

#define BLOCK_SIZE 2880

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
    fprintf(body, "%s\n", raw_body);

    return body;
};

char*** bodyProcess(FILE* file, Header* header){

    fseek(file, 0, SEEK_SET);
    processHeader(file, header);

    fseek(file, 0, SEEK_SET);
    FILE* body_stream = readBody(file);

    //Allocation Memory
    char*** data = (char***)malloc(sizeof(char**)*header->NAXIS1*3);

    for(int x = 0; x<header->NAXIS1; x++){
        data[x] = (char**)malloc(sizeof(char*)*header->NAXIS2*3);
        for(int y = 0; y<header->NAXIS2; y++){
            data[x][y] = (char*)malloc(sizeof(char)*2*header->NAXIS3*3);
        }
    }

    //Main program
    fseek(body_stream, BLOCK_SIZE*2, SEEK_SET);



    for(int x = 0; x<header->NAXIS1; x++){
        for(int y = 0; y<header->NAXIS2; y++){
            fread(data[x][y], 2, 1, body_stream);
        };
    };

    for(int x = 0; x<header->NAXIS1; x++){
        for(int y = 0; y<header->NAXIS2; y++){
            fread(data[x][y] + 2, 2, 1, body_stream);
        };
    };

    for(int x = 0; x<header->NAXIS1; x++){
        for(int y = 0; y<header->NAXIS2; y++){
            fread(data[x][y] + 4, 2, 1, body_stream);
        };
    };

    return data;
};

void freeBody(char*** data, Header* header){
    for(int x = 0; x<header->NAXIS1; x++){
        for(int y = 0; y<header->NAXIS2; y++){
            free(data[x][y]);
        };
        free(data[x]);
    };
    free(data);

}

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

void parse_fits_file(const char* file_path) {
    char command[256];
    snprintf(command, sizeof(command), "%s %s", "./parser.sh", file_path);
    system(command);
};


int main() {
    Header header;
    FILE* file = fopen("../fit7.txt", "r");

    FILE* body = readBody(file);

    char*** data = bodyProcess(body, &header);
    freeBody(data, &header);

    fclose(file);
    return 0;
};