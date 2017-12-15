#ifndef DECOMPRESS_H
#define DECOMPRESS_H
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/*/////////////////////////////////////////////////////////////////////////////
 * Nom :              decompression
 * Paramétres :       D input FILE*: fichier à analyser au niveau de l'encodage
                      R output FILE*: fichier pour l'extraction
                      D Noeud* : tableauHuffmann
                      R nbrChar int: nombre de caractéres dans input
                      R nbrASCII int: nombre de caractéres distinct dans input
 * Valeur retournée : void
 */////////////////////////////////////////////////////////////////////////////
void decompression(FILE* input, FILE* output, Noeud* tableauHuffmann, int nbrChar, int nbrASCII);

#endif
