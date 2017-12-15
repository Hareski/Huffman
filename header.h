#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud Noeud;
struct Noeud{
  int pere;
  int fg;
  int fd;
  double freq;
};
typedef struct Code Code;
struct Code{
  int bit;
  unsigned char* code;
};

/*/////////////////////////////////////////////////////////////////////////////
 * Nom :              frequency
 * Paramétres :       D input FILE*: fichier à analyser
                      R nbrChar int&: nombre de caractéres dans input
                      R nbrASCII int&: nombre de caractéres distinct dans input
 * Valeur retournée : double* : frequences de chaque codage ASCII
 */////////////////////////////////////////////////////////////////////////////
double* frequency(FILE* input, int* nbrChar, int* nbrASCII);

/*/////////////////////////////////////////////////////////////////////////////
 * Nom :              indexGeneration
 * Paramétres :       D tabASCII double* : frequences de chaque codage ASCII
 * Valeur retournée : Noeud* : arbre de compression et décompression
 */////////////////////////////////////////////////////////////////////////////
Noeud* tableauHuffmann(double* freqAscii);

/*/////////////////////////////////////////////////////////////////////////////
 * Nom :              saveHeader
 * Paramétres :       D Noeud* : arbre de compression et décompression
                      D nbrChar int: nombre de caractéres dans input
                      D nbrASCII int: nombre de caractéres distinct dans input
                      R output FILE*: fichier où sera enregistrer l'index
 * Valeur retournée : Void
 */////////////////////////////////////////////////////////////////////////////
Code* saveHeader(FILE* output, Noeud* tableauHuffmann, int nbrChar, int nbrASCII);

 /*/////////////////////////////////////////////////////////////////////////////
  * Nom :              getHeader
  * Paramétres :       D input FILE*: fichier à analyser
                       R nbrChar int*: nombre de caractéres dans input
                       R nbrASCII int*: nombre de caractéres distinct dans input
  * Valeur retournée : Noeud* : tableauHuffmann
  */////////////////////////////////////////////////////////////////////////////
Noeud* getHeader(FILE* input, int* nbrChar, int* nbrASCII);

#endif
