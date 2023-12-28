# Projet Algorithmique (N3S5)

Petit utilitaire pour effectuer des opérations arithmétiques sur des images FITS (Flexible Image Transport System)

# Compilation

## Linux

Dans un shell quelconque, lancer:

```bash
make
```
Une fois compilé, le programme génère un main.exe. Toujours dans le même shell, lancer

```bash
./main
```

## Windows

Sous windows, ce programme nécessite [coreutils](https://sourceforge.net/projects/gnuwin32/).

Une fois coreutils installé, il suffit d'ajouter od.exe au PATH via shell:

```bash
setx PATH "%PATH%;C:\Program Files (x86)\GnuWin32\bin"
```

Enfin, il ne reste qu'à suivre les étapes vu au-dessus pour les systemes Linux.

# Utilisation


Le programme permet de lire les arguments du header d'un fichier FITS donné, sommer deux images bit à bit, les soustraire, en faire la moyenne et les diviser. Il permet également de faire une conversion en fichier CSV, ou output une image PNG, toujours à partir d'un fichier FITS donné.
