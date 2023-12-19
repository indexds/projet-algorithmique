#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./structs.h"

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
        "INSTRUME",
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

        if(lock == 1) {
            continue;
        }

        if(strcmp(word, "=") == 0) {
            continue;
        }



         injecter(&header, keyword, word);
    };

        return header;
    };

Image body_parse(FILE* file){
    Image image;
    char word[50];

    while(fscanf(file, "%s", word)){
        if(strcmp(word, "END") == 1){
            continue;
        }
        printf("%s", word);
    }

    return image;
}



int main(void){
    FILE* file = fopen("./lights/r_lights_00001.fit", "r");
    Header header = header_parse(file);
    printf("SIMPLE: %s\n", header.SIMPLE);
    printf("BITPIX: %d\n", header.BITPIX);
    printf("NAXIS: %d\n", header.NAXIS);
    printf("NAXIS1: %d\n", header.NAXIS1);
    printf("NAXIS2: %d\n", header.NAXIS2);
    printf("NAXIS3: %d\n", header.NAXIS3);
    printf("BZERO: %f\n", header.BZERO);
    printf("BSCALE: %f\n", header.BSCALE);
    printf("DATE: %s\n", header.DATE);

    Image image = body_parse(file);

    fclose(file);
    return 0;

}