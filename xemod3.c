#include "XEnDec_Common.h"
#include "xemod_common.h"

int genRandXEV3()
{
	int tempRand = 0;

	tempRand = genRand32();
	tempRand = tempRand ^ (genRand32() << 18);
	tempRand = tempRand ^ (genRand32() << 2 );
	tempRand = tempRand ^ genRand32();
	
	tempRand = genRand32();
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand << 7;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 3;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand << 8;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 5;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand << 10;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 2;

	tempRand = tempRand ^ (genRand32() << 18);
	tempRand = tempRand ^ (genRand32() << 2 );
	tempRand = tempRand ^ genRand32();

	tempRand = tempRand ^ genRand32();
	tempRand = tempRand << 12;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 4;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand << 6;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 8;
	tempRand = tempRand ^ (genRand32() << 18);
	tempRand = tempRand << 9;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 3;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand << 6;
	tempRand = tempRand ^ genRand32();
	tempRand = tempRand >> 8;
	tempRand = tempRand ^ (genRand32() << 18);

	tempRand = tempRand ^ (genRand32() << 17);
	tempRand = tempRand ^ (genRand32() << 17);
	tempRand = tempRand ^ genRand32();

	return tempRand;
}

void EDecV3(FILE *inFile, FILE *outFile)
{
	int randN = 0;
	unsigned char outNm = 0;
	unsigned char tempRdNm = 0;

	while (fread(&tempRdNm, sizeof(tempRdNm), 1, inFile) != 0)
	{
		randN = genRandXEV3();
		randN &= 0x000000FF;

		outNm = tempRdNm ^ (unsigned char)randN;
		fwrite(&outNm, sizeof(outNm), 1, outFile);
	}
}

int genXDEC3(FILE *Finp, char oFileName[])
{
	FILE *outFile = NULL;
	char V3Identifier[SIZE_V3CORRECT + 1] = {0};
	char V3Extention[EXTENTION_LIMIT + 1] = {0};
	int V3Seed = 0;

	fread(V3Identifier, sizeof(char), SIZE_V3CORRECT, Finp);
	
	if(strcmp(V3Identifier, V3CORRECT) != 0)
	{
		return V3_IDERR;
	}
	else
	{
		fread(&V3Seed, sizeof(int), 1, Finp);

		fread(V3Extention, sizeof(char), EXTENTION_LIMIT, Finp);
		strcat(oFileName, V3Extention);
		outFile = fopen(oFileName, "wb");

		if(jOpen(outFile) == FILE_CANNOT_OPEN)
        {
            return FILE_CANNOT_OPEN;
        }

		setRand32(V3Seed);
		EDecV3(Finp, outFile);
	}

	return V3_SUCCESS;
}

int genXENC3(FILE *Finp, FILE *Fout, int seedNumF, char fExtention[])
{
	char V3Header[SIZE_V3CORRECT + 1] = V3CORRECT;

	/*ヘッダ部分書き込み(順番注意)------------------------------*/
	fwrite(V3Header, sizeof(char), SIZE_V3CORRECT, Fout);
	fwrite(&seedNumF, sizeof(int), 1, Fout);
	fwrite(fExtention, sizeof(char), EXTENTION_LIMIT, Fout);
	/*-------------------------------------------------------*/

   	setRand32(seedNumF);
	EDecV3(Finp, Fout);
    
    return V3_SUCCESS;
}
