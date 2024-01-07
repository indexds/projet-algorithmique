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

Le programme permet de lire les arguments du header d'un fichier FITS donné, sommer deux images bit à bit, les soustraire, en faire la moyenne et les diviser. Il permet également de faire une conversion en fichier CSV toujours à partir d'un fichier FITS donné.

Le programme nécessite les dossiers ```/darks```, ```/flats```, ```/lights```, ```/lights_post```, ```/offsets```.

```lights_post``` contiendra les fichiers traités, et doit donc être laissé vide.<br>
```/darks``` contiendra les darks, qui seront traités en un ```master_dark.fit```.<br>
```/flats``` contiendra les offsets, qui seront traités en un ```master_flat.fit```.<br>
```/offsets``` contiendra les offsets, qui seront traités en un ```master_offset.fit```.<br>
```/lights``` contiendra les lights, qui serviront aux différentes opérations.<br>