#include "XEnDec_Common.h"

int genRandXEV2()
{
	int tempRand = 0;

	tempRand = rand();
	tempRand = tempRand ^ rand();
	tempRand = tempRand >> 7;
	tempRand = tempRand ^ rand();
	
	return tempRand;
}

void EDecV2(FILE *inFile, FILE *outFile)
{
	int randN = 0;
	unsigned char outNm = 0;
	unsigned char tempRdNm = 0;

	while (fread(&tempRdNm, sizeof(tempRdNm), 1, inFile) != 0)
	{
		randN = genRandXEV2();
		randN &= 0x000000FF;

		outNm = tempRdNm ^ (unsigned char)randN;
		fwrite(&outNm, sizeof(outNm), 1, outFile);
	}
}

void genXENC2(int seedNumF, FILE *Finp, FILE *Fout)
{
	char V2ID[7] = V2CORRECT;

	fwrite(V2ID, sizeof(char), SIZE_V2CORRECT, Fout);
	fwrite(&seedNumF, sizeof(int), 1, Fout);

	srand(seedNumF);
    EDecV2(Finp, Fout);
}


void genXDEC2(FILE *Finp, FILE *Fout)
{
	char V2Header[7] = { 0 };
	int initNumFromFile = 0;

	fread(&V2Header, sizeof(char), SIZE_V2CORRECT, Finp);	

	if(strcmp(V2CORRECT, V2Header) == 0)
	{
		fread(&initNumFromFile, sizeof(int), 1, Finp);
		srand(initNumFromFile);
        EDecV2(Finp, Fout);
	}
	else 
	{
		printf("\nファイルが不正か、対応していない形式です。\n");
	}
}
