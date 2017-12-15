#include "compress.h"

void compression(FILE* input, FILE* output, Code* codes){
  unsigned char buffer[2], writer[8], TEMP;
  int positionBuffer=0;
  while (fread(buffer,1,1,input)) {
    for (int i = 0; i < codes[(int) *buffer].bit; i++) {
      writer[positionBuffer]=codes[(int) *buffer].code[i];
      positionBuffer++;
      if (positionBuffer==8) {
        TEMP=0x0000;
        while (positionBuffer>0) {
          positionBuffer--;
          if (writer[positionBuffer]==1) {
            TEMP += (0x0001 << (7-positionBuffer));
          }
        }
        fprintf(output, "%c", TEMP);
      }
    }
  }
  if (positionBuffer>0) {
    TEMP=0x0000;
    while (positionBuffer>0) {
      positionBuffer--;
      if (writer[positionBuffer]==1) {
        TEMP += (0x0001 << (7-positionBuffer));
      }
    }
    fprintf(output, "%c", TEMP);
  }
}
