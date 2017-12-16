/**
 * \file decompress.h
 * \brief Fonction de décompilation Huffman.
 * \author Hareski
 * \version 1.1
 * \date 16 décembre 2017
 */
#ifndef DECOMPRESS_H
#define DECOMPRESS_H
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/**
 * \fn void decompression(FILE* input, FILE* output, Noeud* tableauHuffmann, int nbrChar, int nbrASCII)
 * \brief Fonction de décompilation Huffman.
 *
 * \param input FILE*: fichier à analyser au niveau de l'encodage
 * \param output FILE*: fichier pour l'extraction
 * \param tableauHuffmann Noeud* : tableau de Huffmann de l'index
 * \param nbrChar int: nombre de caractéres dans input
 * \return void
 */
void decompression(FILE* input, FILE* output, Noeud* tableauHuffmann, int nbrChar, int nbrASCII);

#endif
