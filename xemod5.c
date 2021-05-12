#include "XEnDec_Common.h"
#include "xemod_common.h"

unsigned int bitShiftNum[V5BSHIFT_ARRAY_MAX] = {0};
int ArrayLength_Global = 0;

void setBitShift(unsigned int Numbers[], int ArrayLength)
{
    int ctr1 = 0;

    ArrayLength_Global = ArrayLength;
    ArrayLength_Global %= (V5BSHIFT_ARRAY_MAX + 1);

    while( ctr1 < ArrayLength_Global )
    {
        bitShiftNum[ctr1] = Numbers[ctr1];
        ctr1++;
    }
}

int genRandXEV5()
{
	int tempRand = 0;
    int ctr1 = 0;

	tempRand = genRand32();
    while(ctr1 < ArrayLength_Global)
    {
        if( (ctr1 % 2) == 0 )
        {
   	        tempRand = tempRand << bitShiftNum[ctr1];
        }
        else
        {
            tempRand ^= (genRand32() >> bitShiftNum[ctr1]);
        }
        ctr1++;
    }
	return tempRand;
}

void EDecV5(FILE *inFile, FILE *outFile)
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
			randN = genRandXEV5();
			intToChar(randN, keyNumber, KNLENGTH);
		}
		
		outNm = tempRdNm ^ keyNumber[ctr];
		fwrite(&outNm, sizeof(outNm), 1, outFile);

		ctr++;
		ctr %= 4;
	}
}

int genXDEC5(FILE *Finp, char oFileName[])
{	
    FILE *outFile = NULL;
	char V5Identifier[SIZE_V5CORRECT + 1] = {0};
	char V5Extention[EXTENTION_LIMIT + 1] = {0};
	int V5Seed = 0;
    int bitShiftArraySize = V5BSHIFT_ARRAY_MAX;
    unsigned int bsArrayFromFile[V5BSHIFT_ARRAY_MAX] = {0};

	fread(V5Identifier, sizeof(char), SIZE_V5CORRECT, Finp);
	
	if(strcmp(V5Identifier, V5CORRECT) != 0)
	{
		printf("ファイルが不正か、対応していない形式です。\n");
		return V5_IDERR;
	}
	else
	{
		fread(&V5Seed, sizeof(int), 1, Finp);
		setRand32(V5Seed);

		fread(V5Extention, sizeof(char), EXTENTION_LIMIT, Finp);
		strcat(oFileName, V5Extention);
		printf("拡張子：%s\n", V5Extention);
		outFile = fopen(oFileName, "wb");

		if(jOpen(outFile) == FILE_CANNOT_OPEN)
        {
            return FILE_CANNOT_OPEN;
        }

		fread(&bitShiftArraySize, sizeof(int), 1, Finp);
        fread(bsArrayFromFile, sizeof(unsigned int), bitShiftArraySize, Finp);
        setBitShift(bsArrayFromFile, bitShiftArraySize);

		EDecV5(Finp, outFile);
	}

	return V5_SUCCESS;
}

int genXENC5(FILE *Finp, FILE *Fout, int seedNumF, char fExtention[])
{
	char V5Header[SIZE_V5CORRECT + 1] = V5CORRECT;
    int bitShiftArraySize = V5BSHIFT_ARRAY_MAX;
    unsigned int bsNumbers[V5BSHIFT_ARRAY_MAX] = {0};
    int ctr1 = 0;
    int tempRand = 0;
    int tempSeed = 0;

    tempSeed = (int)time(NULL);
    setRand32( tempSeed );

    while(ctr1 < V5BSHIFT_ARRAY_MAX)
    {
        bsNumbers[ctr1] = genRand32();
        bsNumbers[ctr1] %= (unsigned int)V5BSHIFT_BSLENGTH_MAX;
        ctr1++;
    }
    setBitShift(bsNumbers, V5BSHIFT_ARRAY_MAX);

	/*ヘッダ部分書き込み(順番注意)------------------------------*/
	fwrite(V5Header, sizeof(char), SIZE_V4CORRECT, Fout);
	fwrite(&seedNumF, sizeof(int), 1, Fout);
	fwrite(fExtention, sizeof(char), EXTENTION_LIMIT, Fout);
  	fwrite(&bitShiftArraySize, sizeof(int), 1, Fout);
  	fwrite(bitShiftNum , sizeof(int), ArrayLength_Global, Fout);
	/*-------------------------------------------------------*/

   	setRand32(seedNumF);
	EDecV5(Finp, Fout);
    
    return V5_SUCCESS;
}
