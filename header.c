#include "header.h"

void printT(Noeud* tableauHuffmann){
    printf("Arbre d'Huffman :\n");
  for (size_t i = 0; i < 511; i++) {
    if (tableauHuffmann[i].pere!=-1||tableauHuffmann[i].fg!=-1||tableauHuffmann[i].fd!=-1) {
      printf("Noeud %ld : PERE[%d] FG[%d] FD[%d] de poids %f\n",i, tableauHuffmann[i].pere, tableauHuffmann[i].fg, tableauHuffmann[i].fd, tableauHuffmann[i].freq);
    }
  }
  printf("...\n");
}

void printFreq(double* tabAscii){
    printf("...\nListe des caractères et leur probabilité d’apparition :\n");
  for (int i = 0; i < 256; i++) {
    if (tabAscii[i]!=0) {
      printf(" > %c apparait avec une probabilité de %f \n",i,tabAscii[i]);
    }
  }
  printf("...\n");
}

double* frequency(FILE* input, int* nbrChar, int* nbrASCII){

  // Allocation mémoire du tableau à retourner
  double* tabAscii = (double*) malloc(511 * sizeof(double));
  if (tabAscii != NULL){for (int i = 0; i < 256; i++) {tabAscii[i]=0.0;}}
  else{fprintf(stderr, "Le tableau n'a pu être généré. \n");return NULL;}

  // Lecture du fichier, modification du tableau à retourner et des paramètres
  unsigned char buffer[2]; *nbrChar = 0; *nbrASCII = 0;
  while (fread(buffer,1,1,input)) {
    if (tabAscii[(int) buffer[0]] == 0.0) {(*nbrASCII)++;}
    tabAscii[(int) buffer[0]] += 1;
    (*nbrChar)++;
  }
  // Division par le nombre de char pour obtenir la frequence et retour
  for (int i = 0; i < 256; i++) {tabAscii[i]/=(double) *nbrChar;}
  printFreq(tabAscii);
  return tabAscii;
}

Noeud* tableauHuffmann(double* freqAscii){

  // Allocation mémoire du tableau
  Noeud* tableauHuffmann = (Noeud*) malloc(511 * sizeof(Noeud));

  if (tableauHuffmann != NULL){
    // Copie des valeurs de frequence de 0 à 255
    for (int i = 0; i < 256; i++) {
      tableauHuffmann[i].pere=-1;
      tableauHuffmann[i].fg=-1;
      tableauHuffmann[i].fd=-1;
      tableauHuffmann[i].freq=freqAscii[i];
    }
    // Copie des valeurs de frequence de 256 à 510
    for (int i = 256; i < 511; i++) {
      tableauHuffmann[i].pere=-1;
      tableauHuffmann[i].fg=-1;
      tableauHuffmann[i].fd=-1;
      tableauHuffmann[i].freq=0.0;
    }
  }
  else{
    fprintf(stderr, "Le tableau n'a pu être généré. \n");
    return NULL;
  }

  int imin1;
  int imin2;
  double fmin1;
  double fmin2;
  int pere = 255;

  while (tableauHuffmann[pere].freq<1) {
    imin1 = -1;
    imin2 = -1;
    fmin1 = 1.0;
    fmin2 = 1.0;
    for (size_t i = 0; i < 510; i++) {
      if ((tableauHuffmann[i].pere==(-1)) && ((tableauHuffmann[i].freq<=fmin2)||(tableauHuffmann[i].freq<=fmin1)) && (tableauHuffmann[i].freq>0.0)) {
        if (fmin1<fmin2) {
          fmin2 = tableauHuffmann[i].freq;
          imin2 = i;
        } else {
          fmin1 = tableauHuffmann[i].freq;
          imin1 = i;
        }
      }
    }
    if (fmin1+fmin2>=1) {
      fmin1=0;
      fmin2=1;
      pere = 510;
    }
    else {
      pere++;
    }

    tableauHuffmann[imin1].pere=pere;
    tableauHuffmann[imin2].pere=pere;
    tableauHuffmann[pere].fg=imin1;
    tableauHuffmann[pere].fd=imin2;
    tableauHuffmann[pere].freq=fmin1+fmin2;
  }
  printT(tableauHuffmann);
  return tableauHuffmann;
}

 Code* saveHeader(FILE* output, Noeud* tableauHuffmann, int nbrChar, int nbrASCII){
   fprintf(output, "%d|%d|", nbrChar, nbrASCII);
   int pivotTree, positionASCII = 0, bitBuffer, bitCode, bitCodeSUM;
   unsigned char buffer[263], TEMP;
   Code* codes = (Code*) malloc (256 * sizeof(Code));
   while (positionASCII<256) {
     if (tableauHuffmann[positionASCII].freq!=0.0) {
       bitBuffer = 0;
       pivotTree = positionASCII;

       while (pivotTree<510) {
         if (tableauHuffmann[(tableauHuffmann[pivotTree].pere)].fg==pivotTree) {
           buffer[bitBuffer] = 0;
           bitBuffer++;
         }
         else if (tableauHuffmann[(tableauHuffmann[pivotTree].pere)].fd==pivotTree) {
           buffer[bitBuffer] = 1;
           bitBuffer++;
         }
         pivotTree = tableauHuffmann[pivotTree].pere;
       }

       codes[positionASCII].bit = bitBuffer;
       bitCodeSUM += bitBuffer;
       printf("codeChar(%c)=",positionASCII);
       codes[positionASCII].code = (unsigned char*) malloc (codes[positionASCII].bit * sizeof(unsigned char));
       for (int i = 0; i < bitBuffer; i++) {
         codes[positionASCII].code[i]=buffer[bitBuffer-i-1];
         printf("%d",codes[positionASCII].code[i]);
       }
       printf("\n");

       fprintf(output, "%c%c",positionASCII, (char)codes[positionASCII].bit);
       bitCode = 0;
       while (bitCode<codes[positionASCII].bit) {
         TEMP=0x0000;
         for (size_t i = 0; i < 8; i++) {
           if (bitCode<=codes[positionASCII].bit) {
             if (codes[positionASCII].code[bitCode]==1) {
               TEMP += (0x0001 << (7-bitCode%8));
             }
           }
           bitCode++;
         }
         fprintf(output, "%c", TEMP);
       }
     }
     positionASCII++;
   }
   printf("La longueur moyenne de codage est %d\n", bitCodeSUM/nbrASCII);
   return codes;
 }

Noeud* getHeader(FILE* input, int* nbrChar, int* nbrASCII){

  // Allocation mémoire du tableau
  Noeud* tableauHuffmann = (Noeud*) malloc(511 * sizeof(Noeud));

  if (tableauHuffmann != NULL){
    for (int i = 0; i < 511; i++) {
      tableauHuffmann[i].pere=-1;
      tableauHuffmann[i].fg=-1;
      tableauHuffmann[i].fd=-1;
      tableauHuffmann[i].freq=0.0;
    }
  }
  else{
    fprintf(stderr, "Le tableau n'a pu être généré. \n");
    return NULL;
  }

  fscanf (input, "%d|%d|", nbrChar,nbrASCII);

  int nbrASCIIGet=0, pivotTree, bestFils = 509;
  unsigned char charGet, TEMP, bitBuffer;

  while (nbrASCIIGet<*nbrASCII) {
    fscanf (input, "%c%c", &charGet,&bitBuffer);
    pivotTree = 510;
    while ((unsigned int)bitBuffer>0) {
      fscanf (input, "%c", &TEMP);
      for (int i = 7; i >= 0; i--) {
        if ((unsigned int)bitBuffer>1) {
          if (TEMP & (0x0001<<i)) {
            if (tableauHuffmann[pivotTree].fd==-1) {
              tableauHuffmann[pivotTree].fd=bestFils;
              tableauHuffmann[bestFils].pere=pivotTree;
              bestFils--;
            }
            pivotTree=tableauHuffmann[pivotTree].fd;
            bitBuffer--;
          }
          else{
            if (tableauHuffmann[pivotTree].fg==-1) {
              tableauHuffmann[pivotTree].fg=bestFils;
              tableauHuffmann[bestFils].pere=pivotTree;
              bestFils--;
            }
            pivotTree=tableauHuffmann[pivotTree].fg;
            bitBuffer--;
          }
        }
        else if ((unsigned int)bitBuffer==1){
          if (TEMP & (0x0001<<i)) {
            if (tableauHuffmann[pivotTree].fd==-1) {
              tableauHuffmann[pivotTree].fd=(int)charGet;
              tableauHuffmann[(int)charGet].pere=pivotTree;
              bitBuffer=0;
            }
            else{fprintf(stderr, "Header error %d \n", __LINE__);bitBuffer=0;}
          }
          else{
            if (tableauHuffmann[pivotTree].fg==-1) {
              tableauHuffmann[pivotTree].fg=(int)charGet;
              tableauHuffmann[(int)charGet].pere=pivotTree;
              bitBuffer=0;
            }
            else{fprintf(stderr, "Header error %d \n", __LINE__);bitBuffer=0;}
          }
        }
        if (bestFils<255) {
          printf("Header error %d \n", __LINE__);
          exit(1);
        }
      }
    }
    nbrASCIIGet++;
  }
  return tableauHuffmann;
}
