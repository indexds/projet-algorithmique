# Projet Algorithmique (N3S5)

Petit utilitaire pour effectuer des opérations arithmétiques sur des images FITS (Flexible Image Transport System)

# Compilation

Dans un shell quelconque, lancer:

```bash
make
```
Une fois compilé, le programme génère un main.exe. Toujours dans le même shell, lancer

```bash
./main
```

# Utilisation


Le programme permet de lire les arguments du header d'un fichier FITS donné, sommer deux images bit à bit, les soustraire, en faire la moyenne et les diviser. Il permet également de faire une conversion en fichier CSV, ou output une image PNG, toujours à partir d'un fichier FITS donné.
