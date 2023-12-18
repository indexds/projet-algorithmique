main.c
    -Fonction main lançant l'interface graphique

app.c
    -Fonction gérant la création de l'interface graphique
    -Fonction gérant la création des boutons
    -Fonction gérant les modules

parsing.c
    -Fonction d'ouverture du fichier (PRIM_30)
    -Conversion des données FITS -> csv avec séparateur (PRIM_40)
    -Fonction de parsage du fichier
    -Fonction de fermeture du fichier


logique.c
    -Fonction addition bit à bit des images (PRIM_50)
    -Fonction moyenne bit à bit des images (PRIM_60)
    -Fonction soustraction bit à bit des images (PRIM_70)
    -Fonction division bit à bit des images (PRIM_80)


header.buffer = word;




SIMPLE  =                    T / file does conform to FITS standard
BITPIX  =                   16 / number of bits per data pixel
NAXIS   =                    3 / number of data axes
NAXIS1  =                 4144 / length of data axis 1
NAXIS2  =                 2822 / length of data axis 2
NAXIS3  =                    3 / length of data axis 3
EXTEND  =                    T / FITS dataset may contain extensions
COMMENT   FITS (Flexible Image Transport System) format is defined in 'Astronomy
COMMENT   and Astrophysics', volume 376, page 359; bibcode: 2001A&A...376..359H
BZERO   =               32768. / offset data range to that of unsigned short
BSCALE  =                   1. / default scaling factor
INSTRUME= 'ZWO ASI294MC Pro'   / instrument name
DATE    = '2023-12-16T19:04:54' / UTC date that FITS file was created
DATE-OBS= '2021-03-21T00:08:53.7575967' / YYYY-MM-DDThh:mm:ss observation start,
XPIXSZ  =                 4.63 / X pixel size microns
YPIXSZ  =                 4.63 / Y pixel size microns
XBINNING=                    1 / Camera binning mode
YBINNING=                    1 / Camera binning mode
CCD-TEMP=                -19.8 / CCD temp in C
EXPTIME =                  16. / Exposure time [s]
BAYERPAT= 'GBRG    '           / Bayer color pattern
XBAYROFF=                    0 / X offset of Bayer array
YBAYROFF=                    0 / Y offset of Bayer array
PROGRAM = 'Siril v0.9.12'      / Software that created this HDU
END


SIMPLE  =                    T / file does conform to FITS standard
BITPIX  =                   16 / number of bits per data pixel
NAXIS   =                    3 / number of data axes
NAXIS1  =                 4144 / length of data axis 1
NAXIS2  =                 2822 / length of data axis 2
NAXIS3  =                    3 / length of data axis 3
EXTEND  =                    T / FITS dataset may contain extensions
COMMENT   FITS (Flexible Image Transport System) format is defined in 'Astronomy
COMMENT   and Astrophysics', volume 376, page 359; bibcode: 2001A&A...376..359H
BZERO   =               32768. / offset data range to that of unsigned short
BSCALE  =                   1. / default scaling factor
INSTRUME= 'ZWO ASI294MC Pro'   / instrument name
DATE    = '2023-12-13T09:42:55' / UTC date that FITS file was created
DATE-OBS= '2021-03-20T23:26:08.7195266' / YYYY-MM-DDThh:mm:ss observation start,
XPIXSZ  =                 4.63 / X pixel size microns
YPIXSZ  =                 4.63 / Y pixel size microns
XBINNING=                    1 / Camera binning mode
YBINNING=                    1 / Camera binning mode
CCD-TEMP=                -21.4 / CCD temp in C
EXPTIME =                  16. / Exposure time [s]
BAYERPAT= 'GBRG    '           / Bayer color pattern
XBAYROFF=                    0 / X offset of Bayer array
YBAYROFF=                    0 / Y offset of Bayer array
PROGRAM = 'Siril v0.9.12'      / Software that created this HDU
END