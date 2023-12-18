#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Header{
    bool SIMPLE;        //File does conform to FITS standard.
    int BITPIX;         //Number of bits per data pixel.
    int NAXIS;          //Number of data axes.
    int NAXIS1;         //Length of data axis 1.
    int NAXIS2;         //Length of data axis 2.
    int NAXIS3;          //Length of data axis 3.
    bool EXTEND;        //FITS Dataset may contain extensions.
    short BZERO;        //Offset data range to that of unsigned short.
    short BSCALE;       //Default scaling factor.
    char INSTRUME[50];  //Default instrument name.
    char DATE[50];      //UTC data that FITS file was created.
    char DATEOBS[50];   //YYYY-MM-DDThh:mm:ss observation start.
    float XPIXSZ;        //X pixel size in microns.
    float YPIXSZ;       //Y pixel size in microns.
    int XBINNING;       //Camera binning mode.
    int YBINNING;       //Camera binning mode.
    float CCDTEMP;      //CCD Temp in Celsius.
    float EXPTIME;      //Exposure Time in seconds.
    char BAYERPAT[30];  //Bayer color pattern.
    int XBAYROFF;       //X offset of Bayer array.
    int YBAYROFF;       //Y offset of Bayer array.
    char PROGRAM[30];   //Software that created this HDU;

}Header;

enum headerNames{
    SIMPLE,
    BITPIX,
    NAXIS,
    NAXIS1,
    NAXIS2,
    NAXIS3,
    EXTEND,
    BZERO,
    BSCALE,
    INSTRUME,
    DATE,
    DATEOBS,
    XPIXSZ,
    YPIXSZ,
    XBINNING,
    YBINNING,
    CCDTEMP,
    EXPTIME,
    BAYERPAT,
    XBAYROFF,
    YBAYROFF,
    PROGRAM
};

const char* headerStrings[] = {
    "SIMPLE",
    "BITPIX",
    "NAXIS",
    "NAXIS1",
    "NAXIS2",
    "NAXIS3",
    "EXTEND",
    "BZERO",
    "BSCALE",
    "INSTRUME",
    "DATE",
    "DATEOBS",
    "XPIXSZ",
    "YPIXSZ",
    "XBINNING",
    "YBINNING",
    "CCDTEMP",
    "EXPTIME",
    "BAYERPAT",
    "XBAYROFF",
    "YBAYROFF",
    "PROGRAM"
};

FILE* openFile(char filePath[]){
    return fopen(filePath, "r");
};

Header Parse(FILE* file){
    Header header;

    while(1){
        char* word;

        while(fscanf(file,"%49s", word) != EOF){
            char* buffer;



            if(strcmp(word, "END") == 0){
                break;
            };

            else if(strcmp(word, "=") == 0){
                continue;
            };

            else if(strcmp(word, "/") == 0){
                memset(buffer, 0, 50);
                continue;
            };

            for(int headerName=SIMPLE; headerName<=PROGRAM; headerName++){
                if(strcmp(word, headerStrings[headerName]) == 0){
                    strcpy(buffer, word);
                };
            };

            


        };
    };

    return header;
};


void main(void){
    Header header = Parse(openFile("./lights/r_lights_00001.fit"));

    printf("%s", header);

};