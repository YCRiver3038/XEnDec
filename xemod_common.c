#include "XEnDec_Common.h"

int randNum = 2885;

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

int fileTypeDetect(char* fext){
/*-拡張子によるファイル種別の判定(大小文字区別なし)-------*/
	int ftNum = 0;

	/*-xett-----------------------------------------------*/
	if (strcasecmp(".xett", fext) == 0) { ftNum = 2; }
	/*-xebn-----------------------------------------------*/
	else if (strcasecmp(".xebn", fext) == 0) { ftNum = 3; }
	/*-xeut-----------------------------------------------*/
	else if (strcasecmp(".xeut", fext) == 0) { ftNum = 4; }
	/*-xet2-----------------------------------------------*/
	else if (strcasecmp(".xet2", fext) == 0) { ftNum = 5; }
	/*-xeb2-----------------------------------------------*/
	else if (strcasecmp(".xeb2", fext) == 0) { ftNum = 6; }
	/*-xeu2-----------------------------------------------*/
	else if (strcasecmp(".xeu2", fext) == 0) { ftNum = 7; }
	/*-xeb3-----------------------------------------------*/
	else if (strcasecmp(".xeb3", fext) == 0) { ftNum = 8;	}
	/*-xeb4-----------------------------------------------*/
	else if (strcasecmp(".xeb4", fext) == 0) { ftNum = 9;	}
	/*-xeb5-----------------------------------------------*/
	else if (strcasecmp(".xeb5", fext) == 0) { ftNum = 10;}
	/*-uxb------------------------------------------------*/
	else if (strcasecmp(".uxb", fext) == 0) 
	{
        ftNum = FILE_ALREADY_DECRYPTED;
		printf("指定されたファイルは、既に復号されています。\n");/*英語化準備：(Specified file has already been decrypted.)*/
		return ftNum;
	}	
	/*-ふつうのファイル-----------------------------------*/
	else { ftNum = 0; }

	/*-種別の判定終了-----------------------------------------*/
    return ftNum;
}