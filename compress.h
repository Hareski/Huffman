#ifndef COMPRESS_H
#define COMPRESS_H
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/*/////////////////////////////////////////////////////////////////////////////
 * Nom :              compression
 * Paramétres :       D input FILE*: fichier à analyser au niveau de l'encodage
                      R output FILE*: fichier pour la compression
                      D codes Code*: codage des caractéres ASCII
 * Valeur retournée : void
 */////////////////////////////////////////////////////////////////////////////
void compression(FILE*, FILE*, Code*);

#endif
