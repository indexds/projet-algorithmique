typedef struct Header{
    char SIMPLE[10];        //File does conform to FITS standard.
    int BITPIX;         //Number of bits per data pixel.
    int NAXIS;          //Number of data axes.
    int NAXIS1;         //Length of data axis 1.
    int NAXIS2;         //Length of data axis 2.
    int NAXIS3;          //Length of data axis 3.
    float BZERO;        //Offset data range to that of unsigned short.
    float BSCALE;       //Default scaling factor.
    char DATE[100];      //UTC data that FITS file was created.
}Header;