#ifndef XEMOD4_H_INCLUDED
#define XEMOD4_H_INCLUDED

#include "XEnDec_Common.h"

extern int genRandXEV4();
extern void EDecV4(FILE *inFile, FILE *outFile);
extern int genXDEC4(FILE *Finp, char oFileName[]);
extern int genXENC4(FILE *Finp, FILE *Fout, int seedNumF, char fExtention[]);

#endif