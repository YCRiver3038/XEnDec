#include "XEnDec_Common.h"
#include "xemod_common.h"

int genRandXEV4()
{
	int tempRand = 0;

	tempRand = genRand32();

	tempRand = tempRand << 9;
	tempRand ^= (genRand32() >> 12);
	tempRand = tempRand << 7;
	tempRand ^= (genRand32() >> 3);
	tempRand = tempRand << 4;
	tempRand ^= (genRand32() >> 8);
	tempRand = tempRand << 3;
	tempRand ^= (genRand32() >> 6);
	tempRand = tempRand << 16;
	tempRand ^= (genRand32() >> 12);
	tempRand = tempRand << 5;
	tempRand ^= (genRand32() >> 11);
	tempRand = tempRand << 9;
	tempRand ^= (genRand32() >> 7);
	setRand32(tempRand);

	return tempRand;
}

void EDecV4(FILE *inFile, FILE *outFile)
{
	int randN = 0;
	unsigned char outNm = 0;
	unsigned char tempRdNm = 0;
	int ctr = 0;
	unsigned char keyNumber[KNLENGTH] = {0};

	while (fread(&tempRdNm, sizeof(tempRdNm), 1, inFile) != 0)
	{
		if(ctr == 0)
		{
			randN = genRandXEV4();
			intToChar(randN, keyNumber, KNLENGTH);
		}
		
		outNm = tempRdNm ^ keyNumber[ctr];
		fwrite(&outNm, sizeof(outNm), 1, outFile);

		ctr++;
		ctr %= 4;
	}
}

int genXDEC4(FILE *Finp, char oFileName[])
{
	FILE *outFile = NULL;
	char V4Identifier[SIZE_V4CORRECT + 1] = {0};
	char V4Extention[EXTENTION_LIMIT + 1] = {0};
	int V4Seed = 0;

	fread(V4Identifier, sizeof(char), SIZE_V4CORRECT, Finp);
	
	if(strcmp(V4Identifier, V4CORRECT) != 0)
	{
		return V4_IDERR;
	}
	else
	{
		fread(&V4Seed, sizeof(int), 1, Finp);

		fread(V4Extention, sizeof(char), EXTENTION_LIMIT, Finp);
		strcat(oFileName, V4Extention);
		outFile = fopen(oFileName, "wb");
		if(jOpen(outFile) == FILE_CANNOT_OPEN)
        {
            return FILE_CANNOT_OPEN;
        }

		setRand32(V4Seed);
		EDecV4(Finp, outFile);
	}

	return V4_SUCCESS;
}

int genXENC4(FILE *Finp, FILE *Fout, int seedNumF, char fExtention[])
{
	char V4Header[SIZE_V4CORRECT + 1] = V4CORRECT;

	/*ヘッダ部分書き込み(順番注意)------------------------------*/
	fwrite(V4Header, sizeof(char), SIZE_V4CORRECT, Fout);
	fwrite(&seedNumF, sizeof(int), 1, Fout);
	fwrite(fExtention, sizeof(char), EXTENTION_LIMIT, Fout);
	/*-------------------------------------------------------*/

   	setRand32(seedNumF);
	EDecV4(Finp, Fout);
    
    return V4_SUCCESS;
}

