/**
 * \file compress.h
 * \brief Fonction de compilation Huffman.
 * \author Hareski
 * \version 1.1
 * \date 16 décembre 2017
 */
#ifndef COMPRESS_H
#define COMPRESS_H
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/**
 * \fn void compression(FILE* input, FILE* output, Code* codes)
 * \brief Fonction de compilation Huffman.
 *
 * \param input FILE*: fichier à analyser au niveau de l'encodage
 * \param output FILE*: fichier pour la compression
 * \param codes Code*: codage des caractéres ASCII
 * \return void
 */
void compression(FILE* input, FILE* output, Code* codes);

#endif
