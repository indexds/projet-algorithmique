#include <stdio.h>
#include <string.h>
#include "./convert.h"
#include "./header.h"


void convert_csv(FILE* file){
    Header header;
    processHeader(file,&header);
    char file_path[150]="./";
    char file_name[50];
    //faut la fonction qui stocke les données hors_entête dans un tableau
    printf("Rentrez le nom du fichier : /n");
    scanf("%s",file_name);
    strcat(file_path,file_name);
    FILE* file_csv = fopen(file_path, "rw");
};

void convert_png(FILE* file){

};
 int main(void){    
    FILE* file =fopen("../lights/r_lights_00001.fit", "r");
    convert_csv(file);
    fclose(file);
    return 0;

 };