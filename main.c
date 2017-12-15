#include <string.h>
#include <stdio.h>
#include "header.h"
#include "compress.h"
#include "decompress.h"

/*/////////////////////////////////////////////////////////////////////////////
 * Nom :              help
 * Paramétres :       D exeName char* : nom de l'executable
 * Valeur retournée : void
 */////////////////////////////////////////////////////////////////////////////
void help(char* exeName) {
  printf("Usage: %s MODE INPUT OUTPUT\n"
  " INPUT\n"
  "  Precice the full filename of the input file\n"
  "\n"
  " MODE\n"
  "  -c  --compress      compress input\n"
  "  -x  --extract       extract input\n"
  "\n"
  " OUTPUT\n"
  "  Precice the full filename of the output file\n"
  "\n"
  "                      This help will be display\n"
  "                      if the usage is not respected\n",exeName);
}


int main(int argc, char *argv[]) {

  if (argc>1) {
    if ((strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
      help(argv[0]);
      return 0;
    }
    if ((strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0)&&argc==4) {
      // Ouverture des fichiers
      FILE* input = NULL;
      input = fopen(argv[2], "r");
      FILE* output = NULL;
      output = fopen(argv[3], "w");
      if (input == NULL || output == NULL){fprintf(stderr, "Les fichiers n'ont pu être chargé \n");return 2;}

      // Etapes de compression
      int nbrChar, nbrASCII;
      double* tabASCII = frequency(input, &nbrChar, &nbrASCII);
      Noeud* huff = tableauHuffmann(tabASCII);
      Code* codes = saveHeader(output,huff,nbrChar,nbrASCII);
      rewind(input);
      compression(input, output, codes);

      // Fermeture fichiers
      fclose(input);
      fclose(output);

      return 0;
    }

    if ((strcmp(argv[1], "-x") == 0 || strcmp(argv[1], "--extract") == 0)&&argc==4) {
      // Ouverture des fichiers
      FILE* input = NULL;
      input = fopen(argv[2], "r");
      FILE* output = NULL;
      output = fopen(argv[3], "w");
      if (input == NULL || output == NULL){fprintf(stderr, "Les fichiers n'ont pu être chargé \n");return 2;}

      // Etapes de compression
      int nbrChar, nbrASCII;
        Noeud* huff = getHeader(input, &nbrChar, &nbrASCII);
        decompression(input, output, huff, nbrChar, nbrASCII);

      // Fermeture fichiers
      fclose(input);
      fclose(output);

      return 0;
    }
  }
  fprintf(stderr, "Arguments incompatibles \n");
  help(argv[0]);
  return 1;
}
