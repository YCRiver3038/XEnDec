#ifndef XEMOD2_H_INCLUDED
#define XEMOD2_H_INCLUDED

#include "XEnDec_Common.h"

extern int genRandXEV2();
extern void EDecV2(FILE *inFile, FILE *outFile);
extern void genXENC2(int seedNumF, FILE *Finp, FILE *Fout);
extern void genXDEC2(FILE *Finp, FILE *Fout);

#endif