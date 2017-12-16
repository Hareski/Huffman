#include "decompress.h"

void decompression(FILE* input, FILE* output, Noeud* tableauHuffmann, int nbrChar, int nbrASCII){

  int nbrCharGet=0, pivotTree=510;
  unsigned char TEMP;

  while (nbrChar>nbrCharGet&&fread(&TEMP,1,1,input)) {
    for (int i = 7; i >= 0; i--) {
      if (TEMP & (0x0001<<i)) {
        pivotTree=tableauHuffmann[pivotTree].fd;
      }
      else {
        pivotTree=tableauHuffmann[pivotTree].fg;
      }
      if ((pivotTree<256)&&(nbrChar>nbrCharGet)) {
        fprintf(output, "%c", pivotTree);
        pivotTree=510;
        nbrCharGet++;
      }
    }
  }
}
