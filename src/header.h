#ifndef HEADER_FILE
#define HEADER_FILE

typedef struct Header{
    char SIMPLE[256];
    int BITPIX;
    int NAXIS;
    int NAXIS1;
    int NAXIS2;
    int NAXIS3;
    char EXTEND[256];
    float BZERO;
    float BSCALE;
    char INSTRUME[256];
    char DATE[256];
    char DATE_OBS[256];
    float XPIXSZ;
    float YPIXSZ;
    int XBINNING;
    int YBINNING;
    float CCD_TEMP;
    float EXPTIME;
    char BAYERPAT[256];
    int XBAYROFF;
    int YBAYROFF;
    char PROGRAM[256];
}Header;

void printHeader(Header* header);
void processHeader(FILE* file, Header* header);
void fprintFitsHeader(FILE* fits_file, Header* header);

#endif