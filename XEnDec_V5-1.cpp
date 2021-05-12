#include "XEnDec_Common.h"

int randNum = 2885;
unsigned int bitShiftNum[V5BSHIFT_ARRAY_MAX] = {0};
int ArrayLength_Global = 0;

int genRand32()//(AX+B)modM
{
	randNum = ( (RAND_A * randNum) + RAND_B ) % RAND_M;
	return randNum;
}

void setRand32(int number)
{
	randNum = number;
}

int jOpen(FILE *inputf)
{
	if (inputf == NULL)
	{
		printf("ファイルが開けませんでした。\n");
		return FILE_CANNOT_OPEN;
	}

    return FILE_OPENED;
}

void intToChar(int source, unsigned char target[], int wordLength)
{
	int ctr = (wordLength - 1);
	
	while(ctr > -1)
	{
		target[ctr] = (unsigned char)source;
		source = source >> 8;
		ctr--;
	}
}

int genRandXEV2()
{
	int tempRand = 0;

	tempRand = rand();
	tempRand = tempRand ^ rand();
	tempRand = tempRand >> 7;
	tempRand = tempRand ^ rand();
	
	return tempRand;
}

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


void genXEC(unsigned char FKEY[], unsigned int length, FILE *Finp, FILE *Fout)
{
	unsigned char tempRdNm = 0;
	unsigned char outNm = 0;
	int ctr1 = 0;

	while (fread(&tempRdNm, sizeof(tempRdNm), 1, Finp) != 0)
	{
		outNm = tempRdNm ^ FKEY[ctr1];

		fwrite(&outNm, sizeof(outNm), 1, Fout);

		ctr1++;
		ctr1 %= length;
	}
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

void genXENC2(int seedNumF, FILE *Finp, FILE *Fout)
{
	char V2ID[7] = V2CORRECT;

	fwrite(V2ID, sizeof(char), SIZE_V2CORRECT, Fout);
	fwrite(&seedNumF, sizeof(int), 1, Fout);

	srand(seedNumF);
    EDecV2(Finp, Fout);
}

int genXDEC3(FILE *Finp, char fileName[])
{
	FILE *outFile = NULL;
	char V3Identifier[SIZE_V3CORRECT + 1] = {0};
	char V3Extention[EXTENTION_LIMIT + 1] = {0};
	int V3Seed = 0;

	fread(V3Identifier, sizeof(char), SIZE_V3CORRECT, Finp);
	
	if(strcmp(V3Identifier, V3CORRECT) != 0)
	{
		printf("ファイルが不正か、対応していない形式です。\n");
		return V3_IDERR;
	}
	else
	{
		fread(&V3Seed, sizeof(int), 1, Finp);

		fread(V3Extention, sizeof(char), EXTENTION_LIMIT, Finp);
		strcat(fileName, V3Extention);
		printf("拡張子：%s\n", V3Extention);
		outFile = fopen(fileName, "wb");
		jOpen(outFile);

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

int genXDEC4(FILE *Finp, char fileName[])
{
	FILE *outFile = NULL;
	char V4Identifier[SIZE_V4CORRECT + 1] = {0};
	char V4Extention[EXTENTION_LIMIT + 1] = {0};
	int V4Seed = 0;

	fread(V4Identifier, sizeof(char), SIZE_V4CORRECT, Finp);
	
	if(strcmp(V4Identifier, V4CORRECT) != 0)
	{
		printf("ファイルが不正か、対応していない形式です。\n");
		return V4_IDERR;
	}
	else
	{
		fread(&V4Seed, sizeof(int), 1, Finp);

		fread(V4Extention, sizeof(char), EXTENTION_LIMIT, Finp);
		strcat(fileName, V4Extention);
		printf("拡張子：%s\n", V4Extention);
		outFile = fopen(fileName, "wb");
		jOpen(outFile);

		setRand32(V4Seed);
		EDecV4(Finp, outFile);
	}

	return V4_SUCCESS;
}

int genXDEC5(FILE *Finp, char fileName[])
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
		strcat(fileName, V5Extention);
		printf("拡張子：%s\n", V5Extention);
		outFile = fopen(fileName, "wb");
		jOpen(outFile);

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

int readKeyFile(unsigned char* keyBuffer, unsigned int *keySizeBuffer)
{
    FILE *keyFile = NULL;
    char keyFileName[MAXFN] = { 0 };
    char V1KeyHeader[SIZE_V1KEY_CORRECT + 1] = { 0 };

    printf("キーファイル名は？\n");
    scanf("%2047s", keyFileName);
    fseek(stdin, (long)0, SEEK_SET);

    keyFile = fopen(keyFileName, "rb");
    
    if(jOpen(keyFile) == FILE_CANNOT_OPEN)
    {
        return V1KEY_IDERR;
    }

    fread(V1KeyHeader, sizeof(char), SIZE_V1KEY_CORRECT, keyFile);

    if(strcmp(V1KeyHeader, V1KEY_CORRECT) != 0)
    {
        printf("キーファイルが正しくありません。\n");
        return V1KEY_IDERR;
    }
    else
    {
        fread(keySizeBuffer, sizeof(unsigned int), 1, keyFile);
        *keySizeBuffer *= sizeof(unsigned int);
        *keySizeBuffer %= (MAX_KEYSIZE + 1);

        printf("最大サイズ：%d\n", *keySizeBuffer);

        fread(keyBuffer, sizeof(unsigned char), *keySizeBuffer, keyFile);
        printf("キーファイル読み込み完了\n");
    }
    fclose(keyFile);
	
	return V1KEY_SUCCESS;
}

void body(char fileName[])
{
	FILE *openF = NULL;
	FILE *outF = NULL;
	char internalFileName[MAXFN + EXTENTION_LIMIT] = { 0 };
	char inputedFileName[MAXFN] = { 0 };
	char ftype[EXTENTION_LIMIT + 1] = { 0 };
	int V2seed = 0;
	int V3seed = 0;
	int V4seed = 0;
	int V5seed = 0;    
	int ctr1 = 0;
	int ctr2 = 0;
	int nStr = 0;
	int nExt = 0;
	int ftNum = 0;
    int isfromKeyFile = 0;
    unsigned int keySizeFromFile = 0;
	int verSelect = 0;

    unsigned char keyFromFile[MAX_KEYSIZE] = { 0 };
   	unsigned char keyNumber[DEFAULT_KEYSIZE] = 
	{ 
		0x0F, 0xFF, 0x8D, 0x46, 0x0C, 0x28, 0x01, 0x60, //8
		0x28, 0xDF, 0xFD, 0xFA, 0x9D, 0x56, 0x32, 0x23, //16
		0x16, 0x45, 0xF0, 0x55, 0xCE, 0x8D, 0x70, 0xC0, //24
		0xE3, 0xFD, 0x3B, 0x7C, 0xD6, 0xD6, 0x0D, 0x61, //32
		0x01, 0x2F, 0x0F, 0x41, 0x5A, 0x36, 0x8A, 0x2F, //40
		0x0E, 0x7F, 0xB3, 0x79, 0x05, 0xD1, 0xC6, 0x6C, //48
		0x09, 0x73, 0xB0, 0xEE, 0x0E, 0xEC, 0x86, 0xC9, //56
		0x46, 0x31, 0xC2, 0xE0, 0x16, 0x5A, 0x1C, 0x19  //64
	};

	strcpy(inputedFileName, fileName);
	/*拡張子の抽出------------------------------*/
	nExt = 0;
	while (inputedFileName[nExt] != '\0')
	{
		nExt++;
		if(nExt > MAXFN)
		{
			break;
		}
	}
	while (inputedFileName[nExt] != '.')
	{
		nExt--;
		if (nExt == -1)
		{
			break;
		}
	}

	if(nExt != -1)
	{
		nStr = nExt;
		ctr1 = 0;
		while(inputedFileName[nExt] != '\0')
		{
			ftype[ctr1] = inputedFileName[nExt];
			nExt++;
			ctr1++;
			if( (ctr1 > EXTENTION_LIMIT) || (nExt > MAXFN) ) 
			{
				break;
			}
		}

		/*ファイル名の抽出------------------------------*/
		ctr2 = 0;
		while(ctr2 < nStr)
		{
			internalFileName[ctr2] = inputedFileName[ctr2];
			ctr2++;
			if(ctr2 > MAXFN)
			{
				break;
			}
		}
		/*----------------------------------------------*/
		printf("拡張子：%s\nファイル名(パス)：%s\n", ftype, internalFileName);
	}
	else
	{
		strcpy(internalFileName, inputedFileName);
		printf("拡張子なし\nファイル名(パス)：%s\n", internalFileName);	
	}
    /*----------------------------------------------------*/

	/*-拡張子によるファイル種別の判定(大小文字区別なし)-------*/
	/*-xett-----------------------------------------------*/
	if (stricmp(".xett", ftype) == 0) { ftNum = 2; }
	/*-テキストファイル-------------------------------------*/
	else if (stricmp(".txt", ftype) == 0) { ftNum = 1; }
	else if (stricmp("c", ftype) == 0) { ftNum = 1; }
	else if (stricmp("cpp", ftype) == 0) { ftNum = 1; }
	else if (stricmp("h", ftype) == 0) { ftNum = 1; }
	else if (stricmp("csv", ftype) == 0) { ftNum = 1; }
	/*-xebn-----------------------------------------------*/
	else if (stricmp(".xebn", ftype) == 0) { ftNum = 3; }
	/*-xeut-----------------------------------------------*/
	else if (stricmp(".xeut", ftype) == 0) { ftNum = 4; }
	/*-xet2-----------------------------------------------*/
	else if (stricmp(".xet2", ftype) == 0) { ftNum = 5; }
	/*-xeb2-----------------------------------------------*/
	else if (stricmp(".xeb2", ftype) == 0) { ftNum = 6; }
	/*-xeu2-----------------------------------------------*/
	else if (stricmp(".xeu2", ftype) == 0) { ftNum = 7; }
	/*-xeb3-----------------------------------------------*/
	else if (stricmp(".xeb3", ftype) == 0) { ftNum = 8;	}
	/*-xeb4-----------------------------------------------*/
	else if (stricmp(".xeb4", ftype) == 0) { ftNum = 9;	}
    /*-xeb5-----------------------------------------------*/
	else if (stricmp(".xeb5", ftype) == 0) { ftNum = 10;	}
	/*-uxb------------------------------------------------*/
	else if (stricmp(".uxb", ftype) == 0) 
	{
		printf("指定されたファイルは、既に復号されています。\n");/*英語化準備：(Specified file has already been decrypted.)*/
		return;
	}	
	/*-ふつうのファイル-----------------------------------*/
	else { ftNum = 0; }

	/*-種別の判定終了-----------------------------------------*/

	/*種別ごとの取扱いかた------------------------------------------*/
	if (ftNum == 10) //入力がVer4(xeb4)
	{
		openF = fopen(inputedFileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }
		
        printf("処理中...\n");
		genXDEC5(openF, internalFileName);
	}
    else if (ftNum == 9) //入力がVer4(xeb4)
	{
		openF = fopen(inputedFileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }

		printf("処理中...\n");
		genXDEC4(openF, internalFileName);
	}
	else if (ftNum == 8) //入力がVer3(xeb3)
	{
		openF = fopen(inputedFileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }

		printf("処理中...\n");
		genXDEC3(openF, internalFileName);
	}
    else if ( (ftNum == 7) || (ftNum == 6) || (ftNum == 5) ) //入力がVer2(xeu2, xeb2, xet2)
    {
		if(ftNum != 6) //入力がxeb2でない
		{
			strcat(internalFileName, ".txt");
		}
		else
		{
			strcat(internalFileName, ".uxb");
		}

        openF = fopen(inputedFileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }

        outF = fopen(internalFileName, "wb");
        if( jOpen(outF) == FILE_CANNOT_OPEN )
        {
            return;
        }

		printf("処理中...\n");
        genXDEC2(openF, outF);
    }
    else if ( (ftNum == 4 ) || (ftNum == 3) || (ftNum == 2) ) //入力がVer1(xeut, xebn, xett)
    {
		if(ftNum != 3) //入力がxebnでない
		{
			strcat(internalFileName, ".txt");
		}
		else //入力がxebn
		{
			strcat(internalFileName, ".uxb");
		}
        printf("内蔵キー利用：0\nキーファイル利用：1\n");
        scanf("%d", &isfromKeyFile);
        fseek(stdin, (long)0, SEEK_SET);

        if(isfromKeyFile != 0)
        {
            if(readKeyFile(keyFromFile, &keySizeFromFile) == V1KEY_IDERR)
			{
				return;	
			}
			else
			{
				openF = fopen(inputedFileName, "rb");
                if(jOpen(openF) == FILE_CANNOT_OPEN)
                {
                    return;
                }

				outF = fopen(internalFileName, "wb");
                if(jOpen(outF) == FILE_CANNOT_OPEN)
                {
                    return;
                }

				printf("処理中...\n");
				genXEC(keyFromFile, keySizeFromFile, openF, outF);
			}
        }
        else
        {
            openF = fopen(inputedFileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

            outF = fopen(internalFileName, "wb");
            if(jOpen(outF) == FILE_CANNOT_OPEN)
            {
                return;
            }

            printf("処理中...\n");
            genXEC(keyNumber, DEFAULT_KEYSIZE, openF, outF);
        }
    }
	else if ( (ftNum == 0) || (ftNum == 1) ) //入力がふつうのファイル
	{
		printf("バージョンは？\nVer.1：1\nVer.2：2\nVer.3：3\nVer.4：4\nVer.5：5\n");
		scanf("%d", &verSelect);
		fseek(stdin, (long)0, SEEK_SET);

		if(verSelect == 1)
		{
			if(ftNum == 1)
			{
				strcat(internalFileName, ".xeut");
			}
			else
			{
				strcat(internalFileName, ".xebn");
			}
            
			printf("内蔵キー利用：0\nキーファイル利用：1\n");
			scanf("%d", &isfromKeyFile);
			fseek(stdin, (long)0, SEEK_SET);

			if(isfromKeyFile == 0)
			{
				printf("処理中...\n");
				genXEC(keyNumber, DEFAULT_KEYSIZE, openF, outF);
			}
			else
			{
				if(readKeyFile(keyFromFile, &keySizeFromFile) == V1KEY_IDERR)
				{
					return;	
				}
				else
				{
					openF = fopen(inputedFileName, "rb");
                    if(jOpen(openF) == FILE_CANNOT_OPEN)
                    {
                        return;
                    }

					outF = fopen(internalFileName, "wb");
                    if(jOpen(outF) == FILE_CANNOT_OPEN)
                    {
                        return;
                    }

					printf("処理中...\n");
					genXEC(keyFromFile, keySizeFromFile, openF, outF);
				}
			}
		}
		else if(verSelect == 2)
		{
            V2seed = rand();

			if(ftNum == 1)
			{
				strcat(internalFileName, ".xeu2");
			}
			else
			{
				strcat(internalFileName, ".xeb2");
			}

			openF = fopen(inputedFileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			outF = fopen(internalFileName, "wb");
            if(jOpen(outF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			printf("処理中...\n");
			genXENC2(V2seed, openF, outF);
		}
		else if(verSelect == 3)
		{
			openF = fopen(inputedFileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			strcat(internalFileName, ".xeb3");
			outF = fopen(internalFileName, "wb");
            if(jOpen(outF) == FILE_CANNOT_OPEN)
            {
                return;
            }

            V3seed = genRand32();

			printf("処理中...\n");
			genXENC3(openF, outF, V3seed, ftype);
		}
		else if(verSelect == 4)
		{
			openF = fopen(inputedFileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			strcat(internalFileName, ".xeb4");
			outF = fopen(internalFileName, "wb");
            if(jOpen(outF) == FILE_CANNOT_OPEN)
            {
                return;
            }

            V4seed = genRand32();

			printf("処理中...\n");
			genXENC4(openF, outF, V4seed, ftype);
		}
   		else if(verSelect == 5)
		{
			openF = fopen(inputedFileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			strcat(internalFileName, ".xeb5");
			outF = fopen(internalFileName, "wb");
            if(jOpen(outF) == FILE_CANNOT_OPEN)
            {
                return;
            }

            V5seed = genRand32();

			printf("処理中...\n");
			genXENC5(openF, outF, V5seed, ftype);
		}

	}
	else
	{
        printf("不明なエラーが発生しました。\n"); 
        return;       
    }

	fclose(openF);
	fclose(outF);
}

int main(int argc, char *argv[])
{
	char inputedFileName_Main[MAXFN] = { 0 };
	int ctrMain = 0;
    int defaultSeed = 0;

    defaultSeed = (int)time(NULL);
    srand(defaultSeed);
    setRand32(defaultSeed);

    if(argc < 2)
	{
		printf("入力ファイル名は？");
		scanf("%2047s", inputedFileName_Main);
		fseek(stdin, (long)0, SEEK_SET);
		body(inputedFileName_Main);
	}
	else
	{
		ctrMain = argc - 1;
		while(ctrMain > 0)
		{
            system("cls");
			body(argv[ctrMain]);
			ctrMain--;
		}
	}
	
	printf("終了\n");	
	system("pause");
	exit(EXIT_SUCCESS);

	return 0;
}