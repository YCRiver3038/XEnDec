#include "XEnDec_Common.h"

void fileNameDetect(char* inputedFileName, char** nameDest, char** extDest) {

	char internalFileName[MAXFN + EXTENTION_LIMIT] = { 0 };
	char ftype[EXTENTION_LIMIT + 1] = { 0 };

	int nExt = 0;
	int ctr1 = 0;
	int ctr2 = 0;
	int nStr = 0;

	#ifdef DEBUGGING
	printf("in fileNameDetect - thrown filename to detect : %s\n", inputedFileName);
	printf("in fileNameDetect - thrown pointer to nameDest : %p\n", nameDest);
	printf("in fileNameDetect - thrown pointer to extDest : %p\n", extDest);
	#endif

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

	#ifdef DEBUGGING
	printf("in fileNameDetect - throwing internalFilename : %s\n", internalFileName);
	printf("in fileNameDetect - throwing ftype : %s\n", ftype);
	#endif

	*nameDest = internalFileName;
	*extDest = ftype;
	#ifdef DEBUGGING
	printf("in fileNameDetect - *nameDest : %s\n", *nameDest);
	printf("in fileNameDetect - *extDest : %s\n", *extDest);
	#endif

	return;
}