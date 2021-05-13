#ifndef XEMOD1_H_INCLUDED
#define XEMOD1_H_INCLUDED

#include "XEnDec_Common.h"

extern unsigned char keyNumber[];
extern void genXEC(unsigned char FKEY[], unsigned int length, FILE *Finp, FILE *Fout);
extern int readKeyFile(unsigned char* keyBuffer, unsigned int *keySizeBuffer);

#endif