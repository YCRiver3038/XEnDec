#include "xemod3.c" //tempolally included

void body(char fileName[])
{
	int V3seed = 0;

	FILE *openF = NULL;
	FILE *outF = NULL;
	char internalFileName[MAXFN + EXTENTION_LIMIT] = { 0 };
	char inputedFileName[MAXFN] = { 0 };
	char ftype[EXTENTION_LIMIT + 1] = { 0 };
	int ctr1 = 0;
	int ctr2 = 0;
	int nStr = 0;
	int nExt = 0;
	int ftNum = 0;

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
	else if (stricmp(".xeb5", ftype) == 0) { ftNum = 10;}
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
    if (ftNum == 8) //入力がVer3(xeb3)
	{
		openF = fopen(inputedFileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }

		printf("処理中...\n");
		genXDEC3(openF, internalFileName);
	}
	else if ( ftNum == 0 ) //入力がふつうのファイル
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
	else
	{
        printf("スキップしました。\n"); 
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
			printf("残り：%dファイル\n", ctrMain);
			body(argv[ctrMain]);
			ctrMain--;
		}
	}
	
	printf("終了\n");	
	system("pause");
	exit(EXIT_SUCCESS);

	return 0;
}