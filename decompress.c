#include "decompress.h"

void decompression(FILE* input, FILE* output, Noeud* tableauHuffmann, int nbrChar, int nbrASCII){

  int nbrCharGet=0, pivotTree=510;
  unsigned char TEMP;
  fprintf(stderr, "SaLUT %u char %u charget %u nbr ascii \n", nbrChar,nbrCharGet,nbrASCII);

  while (nbrChar>nbrCharGet&&fread(&TEMP,1,1,input)) {
    fprintf(stderr, "LECTURE %u char %u charget %u nbr ascii \n", nbrChar,nbrCharGet,nbrASCII);


    for (int i = 7; i >= 0; i--) {
      if (TEMP & (0x0001<<i)) {
        fprintf(stderr, "%d-----> %d \n", i, pivotTree);

        pivotTree=tableauHuffmann[pivotTree].fd;
      }
      else {
        fprintf(stderr, "%d-----> %d \n", i, pivotTree);

        pivotTree=tableauHuffmann[pivotTree].fg;
      }
      if ((pivotTree<256)&&(nbrChar>nbrCharGet)) {
        fprintf(stderr, "%d-%c---> %d \n", i, pivotTree, pivotTree);
        fprintf(output, "%c", pivotTree);
        pivotTree=510;
        nbrCharGet++;
      }
    }
  }
}

void print(Noeud* tableauHuffmann){
    printf("...\n");
  for (size_t i = 0; i < 511; i++) {
    if (tableauHuffmann[i].pere!=-1||tableauHuffmann[i].fg!=-1||tableauHuffmann[i].fd!=-1) {
      printf("Noeud %ld : PERE[%d] FG[%d] FD[%d] de freq %f\n",i, tableauHuffmann[i].pere, tableauHuffmann[i].fg, tableauHuffmann[i].fd, tableauHuffmann[i].freq);
    }
  }
  printf("...\n");
}
