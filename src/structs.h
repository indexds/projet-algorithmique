#ifndef Header

#define Header typedef struct Header{
    char SIMPLE[2];
    int BITPIX;
    int NAXIS;
    int NAXIS1;
    int NAXIS2;
    int NAXIS3;
    char EXTEND[2];
    double BZERO;
    double BSCALE;
    char INSTRUME[15];
    char DATE[20];
    char DATE_OBS[28];
    double XPIXSZ;
    double YPIXSZ;
    int XBINNING;
    int YBINNING;
    double CCD_TEMP;
    double EXPTIME;
    char BAYERPAT[5];
    int XBAYROFF;
    int YBAYROFF;
    char PROGRAM[13];
}Header;

#endif