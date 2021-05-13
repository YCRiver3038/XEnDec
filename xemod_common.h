#ifndef XEMOD_COMMON_H_INCLUDED
#define XEMOD_COMMON_H_INCLUDED
#include "XEnDec_Common.h"

extern int randNum;
extern int genRand32();
extern void setRand32(int number);
extern int jOpen(FILE *inputf);
extern void intToChar(int source, unsigned char target[], int wordLength);
extern int fileTypeDetect(char** fext);

#endif