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
	#ifdef DEBUGGING
	printf("at jOpen() - thrown pointer:%p\n", inputf);
	#endif
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

int fileTypeDetect(char** argfext){
/*-拡張子によるファイル種別の判定(大小文字区別なし)-------*/
	int ftNum = 0;
	int tempctr = 0;
	char* fextFunc = NULL;

	#ifdef DEBUGGING
		int isDataChanged = 0;
		char tempstr[EXTENTION_LIMIT] = ".hogeho";
		printf("\nin fileTypeDetect - entered fileTypeDetect\n");
		printf("\treceived address:%p\n", argfext);
		printf("\treceived extention:%s\n", *argfext);
	#endif

	fextFunc = (char*)calloc(EXTENTION_LIMIT, sizeof(char));
	if(fextFunc == NULL){
		printf("memory not allocated\n");
		return 0;
	}
	memset(fextFunc, 0, EXTENTION_LIMIT);

	#ifdef DEBUGGING
		printf("in fileTypeDetect - fextFunc allocated(address:%p)\n", fextFunc);
	#endif

	#ifdef DEBUGGING
		printf("in fileTypeDetect - copying *argfext into fextFunc :");
	#endif

	for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
		fextFunc[tempctr] = (*argfext)[tempctr];
	}

	#ifdef DEBUGGING
		printf("Done\n");

		printf("in fileTypeDetect - comparing *argfext and fextFunc:");
		for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
			if((*argfext)[tempctr] != fextFunc[tempctr]){
				printf("data changed!\n");
				isDataChanged = 1;
				break;
			}
		}
		if(!isDataChanged)
		{
			printf("data unchanged\n");
		}

		printf("in fileTypeDetect - *argfext:\"%s\", fextFunc:\"%s\"\n", *argfext, fextFunc);
		printf("RAW (*argfext): ");
		for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
			printf("%02x ", (*argfext)[tempctr]);
		}
		printf("\n");
		printf("RAW (fextFunc): ");
		for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
			printf("%02x ", fextFunc[tempctr]);
		}
		printf("\n");

		printf("in fileTypeDetect - testing strncasecmp (string and array):");
		strncasecmp(tempstr, &(fextFunc[0]), (EXTENTION_LIMIT-1));
		printf("Done\n");

		printf("in fileTypeDetect - comparing *argfext and fextFunc:");
		for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
			if((*argfext)[tempctr] != fextFunc[tempctr]){
				printf("data changed!\n");
				isDataChanged = 1;
				break;
			}
		}
		if(!isDataChanged)
		{
			printf("data unchanged\n");
		}

		printf("in fileTypeDetect - *argfext after test:\"%s\", fextFunc after test:\"%s\"\n", *argfext, fextFunc);
		printf("RAW (*argfext): ");
		for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
			printf("%02x ", (*argfext)[tempctr]);
		}
		printf("\n");
		printf("RAW (fextFunc): ");
		for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
			printf("%02x ", fextFunc[tempctr]);
		}
		printf("\n");

		printf("in fileTypeDetect - using fextFunc to determine filetype : %s\n", fextFunc);
		printf("RAW : ");
		for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
			printf("%02x ", fextFunc[tempctr]);
		}
		printf("\n");

	#endif
	
	/*-xett-----------------------------------------------*/
	if (strcasecmp(".xett", fextFunc) == 0) { ftNum = 2; }
	/*-xebn-----------------------------------------------*/
	else if (strcasecmp(".xebn", fextFunc) == 0) { ftNum = 3; }
	/*-xeut-----------------------------------------------*/
	else if (strcasecmp(".xeut", fextFunc) == 0) { ftNum = 4; }
	/*-xet2-----------------------------------------------*/
	else if (strcasecmp(".xet2", fextFunc) == 0) { ftNum = 5; }
	/*-xeb2-----------------------------------------------*/
	else if (strcasecmp(".xeb2", fextFunc) == 0) { ftNum = 6; }
	/*-xeu2-----------------------------------------------*/
	else if (strcasecmp(".xeu2", fextFunc) == 0) { ftNum = 7; }
	/*-xeb3-----------------------------------------------*/
	else if (strcasecmp(".xeb3", fextFunc) == 0) { ftNum = 8;	}
	/*-xeb4-----------------------------------------------*/
	else if (strcasecmp(".xeb4", fextFunc) == 0) { ftNum = 9;	}
	/*-xeb5-----------------------------------------------*/
	else if (strcasecmp(".xeb5", fextFunc) == 0) { ftNum = 10;}
	/*-uxb------------------------------------------------*/
	else if (strcasecmp(".uxb", fextFunc) == 0) 
	{
        ftNum = FILE_ALREADY_DECRYPTED;
		printf("指定されたファイルは、既に復号されています。\n");/*英語化準備：(Specified file has already been decrypted.)*/
		return ftNum;
	}	
	/*-ふつうのファイル-----------------------------------*/
	else { ftNum = 0; }

	#ifdef DEBUGGING
		printf("in fileTypeDetect - thrown extention source after processing:\"%s\"\n", fextFunc);
		printf("RAW : ");
		for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
			printf("%02x ", fextFunc[tempctr]);
		}
		printf("\n");

		printf("in fileTypeDetect - detected filetype : %d\n", ftNum);
		if(fextFunc != NULL){
			printf("in fileTypeDetect - freeing fextFunc:");
			free(fextFunc);
			printf("Done\n");
		}
		printf("exiting from fileTypeDetect\n\n");
	#endif

	/*-種別の判定終了-----------------------------------------*/
    return ftNum;
}