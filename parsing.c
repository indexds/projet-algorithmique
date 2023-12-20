#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "./structs.h"

#define BLOCK_SIZE 2880

void injecter(Header* header, char* KEYWORD, char* word) {
    if (strcmp(KEYWORD, "SIMPLE") == 0) {
        sscanf(word, "%9s", header->SIMPLE);
    }
    else if (strcmp(KEYWORD, "BITPIX") == 0) {
        sscanf(word, "%d", &header->BITPIX);
    }
    else if (strcmp(KEYWORD, "NAXIS") == 0) {
        sscanf(word, "%d", &header->NAXIS);
    }
    else if (strcmp(KEYWORD, "NAXIS1") == 0) {
        sscanf(word, "%d", &header->NAXIS1);
    }
    else if (strcmp(KEYWORD, "NAXIS2") == 0) {
        sscanf(word, "%d", &header->NAXIS2);
    }
    else if (strcmp(KEYWORD, "NAXIS3") == 0) {
        sscanf(word, "%d", &header->NAXIS3);
    }
    else if (strcmp(KEYWORD, "BZERO") == 0) {
        sscanf(word, "%f", &header->BZERO);
    }
    else if (strcmp(KEYWORD, "BSCALE") == 0) {
        sscanf(word, "%f", &header->BSCALE);
    }
    else if (strcmp(KEYWORD, "DATE") == 0) {
        sscanf(word, "'%99[^']", header->DATE);
    }
}

Header header_parse(FILE* file){
    Header header;
    char word[50];
    char keyword[50];
    int lock = 0;

    char* headerNames[] = {
        "SIMPLE",
        "BITPIX",
        "NAXIS",
        "NAXIS1",
        "NAXIS2",
        "NAXIS3",
        "BZERO",
        "BSCALE",
        "DATE",
    };

    while(fscanf(file, "%30s", word) == 1) {
        if(strcmp(word, "END") == 0) {
            break;
        }

        if(strcmp(word, "/") == 0) {
            lock = 1;
            continue;
        }

        for(size_t i = 0; i < sizeof(headerNames)/sizeof(headerNames[0]); i++) {
            if(strcmp(word, headerNames[i]) == 0) {
                strcpy(keyword, word);
                lock = 0;
            }
        }

        if(lock == 1 || strcmp(word, "=") == 0) {
            continue;
        }

         injecter(&header, keyword, word);
    };

        return header;
    };


void read_block(FILE* file, char* block) {
    fread(block, 1, BLOCK_SIZE, file);
}

void body_parse_16(FILE* file, Header* header) {
    size_t x_size = header->NAXIS1;
    size_t y_size = header->NAXIS2;
    size_t z_size = header->NAXIS3;

    fseek(file, BLOCK_SIZE * 2, SEEK_SET);

    uint16_t* data_brute = malloc(x_size * y_size * z_size * sizeof(uint16_t));
    fread(data_brute, sizeof(uint16_t), x_size * y_size * z_size, file);

    uint16_t ***data = malloc(x_size * sizeof(uint16_t**));
    for (size_t x = 0; x < x_size; x++) {
        data[x] = malloc(y_size * sizeof(uint16_t*));
        for (size_t y = 0; y < y_size; y++) {
            data[x][y] = malloc(z_size * sizeof(uint16_t));
        }
    }

    for (size_t x = 0; x < x_size; x++) {
        for (size_t y = 0; y < y_size; y++) {
            for (size_t z = 0; z < z_size; z++) {
                size_t index = x + y + z;
                size_t pixel_value = data_brute[index];
                data[x][y][z] = pixel_value;
            }
        }
    }

    for (size_t x = 0; x < x_size; x++) {
        for (size_t y = 0; y < y_size; y++) {
            for (size_t z = 0; z < z_size; z++) {
                printf("%d ", data[x][y][z]);
            }
            printf("\n");
        }
        printf("\n");
    }

    for (size_t x = 0; x < x_size; x++) {
        for (size_t y = 0; y < y_size; y++) {
            free(data[x][y]);
        }
        free(data[x]);
    }
    free(data);
    free(data_brute);
}


int main(void){
    FILE* file = fopen("./lights/r_lights_00001.fit", "r");
    Header header = header_parse(file);
    fclose(file);
    printf("SIMPLE: %s\n", header.SIMPLE);
    printf("BITPIX: %d\n", header.BITPIX);
    printf("NAXIS: %d\n", header.NAXIS);
    printf("NAXIS1: %d\n", header.NAXIS1);
    printf("NAXIS2: %d\n", header.NAXIS2);
    printf("NAXIS3: %d\n", header.NAXIS3);
    printf("BZERO: %.2f\n", header.BZERO);
    printf("BSCALE: %.2f\n", header.BSCALE);
    printf("DATE: %s\n", header.DATE);

    file = fopen("./lights/r_lights_00001.fit", "r");
    body_parse_16(file, &header);
    fclose(file);

    return 0;

}