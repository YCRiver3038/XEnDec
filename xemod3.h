#ifndef XEMOD3_H_INCLUDED
#define XEMOD3_H_INCLUDED

#include "XEnDec_Common.h"

extern int genRandXEV3();
extern void EDecV3(FILE *inFile, FILE *outFile);
extern int genXDEC3(FILE *Finp, char oFileName[]);
extern int genXENC3(FILE *Finp, FILE *Fout, int seedNumF, char fExtention[]);

#endif