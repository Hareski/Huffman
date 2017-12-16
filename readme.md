Application C permettant la compression et la décompression de fichier
en utilisant l’algorithme de Huffman avec un archiveur en python

# Utilisation
## Prérequis
### Makefile
**Avant d'utiliser le programme, il faut compiler :

```sh
$ make
```
### Python
L'archiveur nécessite Python ainsi que le programme déja compilé
dans le même dossier avec pour nom huff

## Programme en C
### Compression
Pour compresser un fichier faite :

```sh
$ huff -c INPUT OUTPUT
```
avec INPUT et OUTPUT respectivement le fichier d'entré et de sortie.

### Décompression
Pour décompresser un fichier faite :

```sh
$ huff -x INPUT OUTPUT
```
avec INPUT et OUTPUT respectivement le fichier d'entré et de sortie.

## Archiveur en python
### Compression
Pour compresser un fichier faite :

```sh
$ ./archiveur.py -c INPUT
```
avec INPUT le fichier ou dossier d'entré.
La sortie portera le même nom suivi de ".huff" pour les fichiers et 
"_huff" pour les dossiers.

### Décompression
Pour décompresser un fichier faite :

```sh
$ ./archiveur.py -x INPUT
```
avec INPUT le fichier ou dossier d'entré.
La sortie portera le même nom suivi de ".dec" pour les fichiers et 
"_dec" pour les dossiers.

 

