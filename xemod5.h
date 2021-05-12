#ifndef XEMOD5_H_INCLUDED
#define XEMOD5_H_INCLUDED

#include "XEnDec_Common.h"

extern void setBitShift(unsigned int Numbers[], int ArrayLength);
extern int genRandXEV5();
extern void EDecV5(FILE *inFile, FILE *outFile);
extern int genXDEC5(FILE *Finp, char oFileName[]);
extern int genXENC5(FILE *Finp, FILE *Fout, int seedNumF, char fExtention[]);

#endif