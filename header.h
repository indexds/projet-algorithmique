typedef struct Header{
    char SIMPLE[10];        //File does conform to FITS standard.
    int BITPIX;         //Number of bits per data pixel.
    int NAXIS;          //Number of data axes.
    int NAXIS1;         //Length of data axis 1.
    int NAXIS2;         //Length of data axis 2.
    int NAXIS3;          //Length of data axis 3.
    char EXTEND[10];        //FITS Dataset may contain extensions.
    float BZERO;        //Offset data range to that of unsigned short.
    float BSCALE;       //Default scaling factor.
    char INSTRUME[100];  //Default instrument name.
    char DATE[100];      //UTC data that FITS file was created.
    char DATEOBS[100];   //YYYY-MM-DDThh:mm:ss observation start.
    float XPIXSZ;        //X pixel size in microns.
    float YPIXSZ;       //Y pixel size in microns.
    int XBINNING;       //Camera binning mode.
    int YBINNING;       //Camera binning mode.
    float CCDTEMP;      //CCD Temp in Celsius.
    float EXPTIME;      //Exposure Time in seconds.
    char BAYERPAT[50];  //Bayer color pattern.
    int XBAYROFF;       //X offset of Bayer array.
    int YBAYROFF;       //Y offset of Bayer array.
    char PROGRAM[50];   //Software that created this HDU;

}Header;