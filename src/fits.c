#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include "./fits.h"
#include "./header.h"



int count_files(FILE* files[]) {
    int count = 0;

    while (files[count] != NULL) {
        count++;
    }
    return count;
};


int isCompatible(FILE* file1, FILE* file2, FILE* output_stream){
    Header header1;
    Header header2;
    processHeader(file1, &header1);
    processHeader(file2, &header2);

    if(strcmp(header1.SIMPLE, "T") != 0 || strcmp(header2.SIMPLE, "T") != 0){
        printf("FITS file does not conform to standard, exiting.");
        return 1;
    };

    if(header1.NAXIS1 != header2.NAXIS1 ||
       header1.NAXIS2 != header2.NAXIS2 ||
       header1.NAXIS3 != header2.NAXIS3 ||
       header1.BITPIX != header2.BITPIX){
        printf("Image Formats are different, exiting.");
        return 1;
    };
    fprintHeader(output_stream, &header1);
    fseek(file1, BLOCK_SIZE, SEEK_SET);
    fseek(file2, BLOCK_SIZE, SEEK_SET);
    fseek(output_stream, BLOCK_SIZE, SEEK_SET);
    return 0;
};


void sum_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    if (isCompatible(file1, file2, output_stream) == 1) {
        return;
    }

    unsigned char buffer1;
    unsigned char buffer2;
    unsigned char buffer3;

    while (fread(&buffer1, 1, 1, file1) != 0 && fread(&buffer2, 1, 1, file2) != 0) {

        buffer3 = buffer1 + buffer2;
        fwrite(&buffer3, 1, 1, output_stream);
    };
};


void sub_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    if(isCompatible(file1, file2, output_stream) == 1){
        return;
    };

    unsigned char buffer1;
    unsigned char buffer2;
    unsigned char buffer3;

    while (fread(&buffer1, 1, 1, file1) != 0 && fread(&buffer2, 1, 1, file2) != 0) {

        buffer3 = buffer1 - buffer2;
        fwrite(&buffer3, 1, 1, output_stream);
    };
};


void avg_fits_files(FILE* file_tab[], FILE* output_stream) {
    int n = count_files(file_tab);
    unsigned char buffer3;
    Header header;

    FILE* temp = file_tab[0];
    FILE* buffer_file = fopen("buffer_file.fit", "w+b");

    for(int i = 1; i < n; i ++){
        printf("[%d/%d]\n", i, n-1);
        sum_fits_files(temp, file_tab[i], buffer_file);
        temp = buffer_file;
    };
    processHeader(buffer_file, &header);
    fprintHeader(output_stream, &header);


    fseek(output_stream, BLOCK_SIZE, SEEK_SET);
    fseek(buffer_file, BLOCK_SIZE, SEEK_SET);

     while(fread(&buffer3, 1, 1, buffer_file) != 0){
        buffer3 /= n;
        fwrite(&buffer3, 1, 1, output_stream);
    };

    fclose(buffer_file);
    fclose(temp);
    remove("./buffer_file.fit");
};


void div_fits_files(FILE* file1, FILE* file2, FILE* output_stream) {
    if(isCompatible(file1, file2, output_stream) == 1){
        return;
    };

    unsigned char buffer1;
    unsigned char buffer2;
    unsigned char buffer3;

     while(fread(&buffer1, 1, 1, file1) != 0 && fread(&buffer2, 1, 1, file2) != 0){

        if(buffer2 == 0){
            buffer3 = buffer1;
        }
        else{
            buffer3 = buffer1 / buffer2;
        }

        fwrite(&buffer3, 1, 1, output_stream);
    };
};


void convert_csv(FILE* file, FILE* output_stream){
    int byte;
    fseek(file, BLOCK_SIZE, SEEK_SET);
    while ((byte = fgetc(file)) != EOF) {
        fprintf(output_stream, "%02X;", byte);
    };
};

void generateMaster(char* directory, char* filename){
    struct dirent* entry;
    DIR* dir = opendir(directory);
    FILE* output;
    FILE* file;
    char buffer;
    char first_entry[256];
    char file_path[256];
    int file_count = 0;

    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
                strcpy(first_entry, entry->d_name);
                file_count++;
            };
        };
    rewinddir(dir);

    if(file_count == 1){

        snprintf(file_path, sizeof(file_path), "%s/%s", directory, first_entry);

        output = fopen(filename, "wb");
        file = fopen(file_path, "rb");

        while(fread(&buffer, 1, 1, file) != 0){
            fwrite(&buffer, 1, 1, output);
        };

        fclose(output);
        fclose(file);
        closedir(dir);
        return;
    };

    FILE** file_tab = calloc(file_count + 1, sizeof(FILE*)); //+1 to get null terminator

    int i = 0;
    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            snprintf(file_path, sizeof(file_path), "%s/%s", directory, entry->d_name);
            file_tab[i] = fopen(file_path, "rb");
            i++;
        };
    };

    output = fopen(filename, "wb");

    avg_fits_files(file_tab, output);

    for(int j = 0; j < file_count; j++){
        fclose(file_tab[j]);
    };
    free(file_tab);
    fclose(output);
    closedir(dir);

};

void generatePretraite(FILE* master_dark, FILE* master_flat, FILE* master_offset){
    // (lights[i]- master_dark)/ (master_flat - master_offset)
    struct dirent* entry;
    DIR* directory = opendir("../lights");
    FILE* output;
    int file_count = 0;
    char file_path[256];
    char output_name[256];


    while((entry = readdir(directory)) != NULL){
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
                file_count++;
            };
        };
    rewinddir(directory);

    FILE** lights = calloc(file_count + 1, sizeof(FILE*)); //+1 to get null terminator

    int i = 0;
    while((entry = readdir(directory)) != NULL){
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            snprintf(file_path, sizeof(file_path), "../lights/%s", entry->d_name);
            lights[i] = fopen(file_path, "rb");
            i++;
        };
    };

    FILE* soustraction_numerateur = fopen("soustraction_numerateur.fit", "w+b");
    FILE* soustraction_denominateur = fopen("soustraction_denominateur.fit", "w+b");

    for(int t = 0; t < file_count; t++){
        snprintf(output_name, sizeof(output_name), "../lights_post/light_post_traitement_%d.fit", t);
        output = fopen(output_name, "wb");
        printf("[%d/%d] \n", t+1, file_count);

        sub_fits_files(lights[t], master_dark, soustraction_numerateur);
        sub_fits_files(master_flat, master_offset, soustraction_denominateur);
        div_fits_files(soustraction_numerateur, soustraction_denominateur, output);
    };

    for(int j = 0; j < file_count; j++){
        fclose(lights[j]);
    };

    fclose(soustraction_numerateur);
    fclose(soustraction_denominateur);
    free(lights);
    closedir(directory);
    fclose(output);
    remove("./soustraction_denominateur.fit");
    remove("./soustraction_numerateur.fit");
};