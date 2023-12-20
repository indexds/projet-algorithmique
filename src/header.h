typedef struct Header{
    char SIMPLE[2];
    int BITPIX;
    int NAXIS;
    int NAXIS1;
    int NAXIS2;
    int NAXIS3;
    char EXTEND[2];
    double BZERO;
    double BSCALE;
    char INSTRUME[50];
    char DATE[50];
    char DATE_OBS[50];
    double XPIXSZ;
    double YPIXSZ;
    int XBINNING;
    int YBINNING;
    double CCD_TEMP;
    double EXPTIME;
    char BAYERPAT[50];
    int XBAYROFF;
    int YBAYROFF;
    char PROGRAM[50];
}Header;

void printHeader(Header* header);
void processHeader(FILE* file, Header* header);