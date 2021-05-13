#include "XEnDec_Common.h"
#include "xemod_common.h"

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
