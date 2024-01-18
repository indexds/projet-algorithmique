#ifndef HEADER_FILE
#define HEADER_FILE

#define BLOCK_SIZE 2880

typedef struct Header{
    char SIMPLE[128];
    int BITPIX;
    int NAXIS;
    int NAXIS1;
    int NAXIS2;
    int NAXIS3;
    char EXTEND[128];
    float BZERO;
    float BSCALE;
    char INSTRUME[128];
    char DATE[128];
    char DATE_OBS[128];
    float XPIXSZ;
    float YPIXSZ;
    int XBINNING;
    int YBINNING;
    float CCD_TEMP;
    float EXPTIME;
    char BAYERPAT[128];
    int XBAYROFF;
    int YBAYROFF;
    char PROGRAM[128];
}Header;

void printHeader(Header* header);
void processHeader(FILE* file, Header* header);
void fprintHeader(FILE* fits_file, Header* header);

#endif