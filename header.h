/**
 * \file header.h
 * \brief Fonction de Création d'index Huffman.
 * \author Hareski
 * \version 1.1
 * \date 16 décembre 2017
 */
#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>

/**
 * \struct Noeud
 * \brief Noeud de l'arbre d'Huffman.
 *
 * pere est le père du Noeud.
 * fg est le fils gauche du Noeud.
 * fd est le fils droit du Noeud.
 * freq est le poid du noeud.
 * Le poid peut être négligé dans certaine condition d'utilisation
 * comme la décompression.
 */
typedef struct
{
  int pere;
  int fg;
  int fd;
  double freq;
}
Noeud;

/**
 * \struct Code
 * \brief Codage d'un charactère.
 *
 * bit est le nombre de bit du code.
 * code est le code.
 */
typedef struct
{
  int bit; /*!< bit != (byte||octet) */
  unsigned char* code;
}
Code;

 /**
  * \fn double* frequency(FILE* input, int* nbrChar, int* nbrASCII)
  * \brief Fonction de calcul de la fréquences d'ASCII Etendu.
  *
  * \param input FILE*: fichier à analyser
  * \param nbrChar int&: nombre de caractéres dans input
  * \param nbrASCII int&: nombre de caractéres distinct dans input
  * \return void
  */
double* frequency(FILE* input, int* nbrChar, int* nbrASCII);

 /**
  * \fn Noeud* tableauHuffmann(double* freqAscii)
  * \brief Fonction de géneration d'arbre Huffman.
  *
  * \param tabASCII double* : frequences de chaque codage ASCII
  * \return Noeud* : arbre de compression et décompression
  */
Noeud* tableauHuffmann(double* freqAscii);

 /**
  * \fn Code* saveHeader(FILE* output, Noeud* tableauHuffmann, int nbrChar, int nbrASCII)
  * \brief Fonction de sauvegarde fichier et tableau d'arbre Huffman.
  *
  * \param output FILE*: fichier pour l'index
  * \param tableauHuffmann Noeud* : tableau de Huffmann de l'index
  * \param nbrChar int: nombre de caractéres dans input
  * \param nbrASCII int: nombre de ASCII distinct
  * \return Code* : tableau des codes ASCII selon l'arbre
  */
Code* saveHeader(FILE* output, Noeud* tableauHuffmann, int nbrChar, int nbrASCII);

  /**
   * \fn Noeud* getHeader(FILE* input, int* nbrChar, int* nbrASCII)
   * \brief Fonction de récupération sur fichier d'arbre Huffman.
   *
   * \param input FILE*: fichier de l'index
   * \param nbrChar int*: nombre de caractéres dans input
   * \param nbrASCII int*: nombre de ASCII distinct
   * \return Noeud* : tableau d'Huffmann
   */
Noeud* getHeader(FILE* input, int* nbrChar, int* nbrASCII);

#endif
