#include "filend.h"
#include "xemod_common.h"
#include "xemod1.h"
#include "xemod2.h"
#include "xemod3.h"
#include "xemod4.h"
#include "xemod5.h"

void body(char fileName[])
{
	FILE *openF = NULL;
	FILE *outF = NULL;
    int seedNumber = 0;
	int verSelect = 0;

	int isfromKeyFile = 0;
    unsigned int keySizeFromFile = 0;
    unsigned char keyFromFile[MAX_KEYSIZE] = { 0 };

	char* nameWoExt = NULL;
	char* fileExt = NULL;
	int ftNum = 0;

	nameWoExt = (char*)calloc((MAXFN+EXTENTION_LIMIT), sizeof(char));
	if(!nameWoExt){
		printf("メモリが確保できませんでした\n");
		return;
	}

	fileExt = (char*)calloc((MAXFN+EXTENTION_LIMIT), sizeof(char));
	if(!fileExt){
		printf("メモリが確保できませんでした\n");
		return;
	}

	fileNameDetect(fileName, &nameWoExt, &fileExt);
	ftNum = fileTypeDetect(&fileExt);

	/*種別ごとの取扱いかた------------------------------------------*/
	if (ftNum == 10) //入力がVer5(xeb5)
	{
		openF = fopen(fileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }
		
        printf("処理中...\n");
		genXDEC5(openF, nameWoExt);
	}
    else if (ftNum == 9) //入力がVer4(xeb4)
	{
		openF = fopen(fileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }

		printf("処理中...\n");
		genXDEC4(openF, nameWoExt);
	}
	else if (ftNum == 8) //入力がVer3(xeb3)
	{
		openF = fopen(fileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }

		printf("処理中...\n");
		genXDEC3(openF, nameWoExt);
	}
    else if ( (ftNum == 7) || (ftNum == 6) || (ftNum == 5) ) //入力がVer2(xeu2, xeb2, xet2)
    {
		if(ftNum != 6) //入力がxeb2でない
		{
			strcat(nameWoExt, ".txt");
		}
		else
		{
			strcat(nameWoExt, ".uxb");
		}

        openF = fopen(fileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }

        outF = fopen(nameWoExt, "wb");
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
			strcat(nameWoExt, ".txt");
		}
		else //入力がxebn
		{
			strcat(nameWoExt, ".uxb");
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
				openF = fopen(fileName, "rb");
                if(jOpen(openF) == FILE_CANNOT_OPEN)
                {
                    return;
                }

				outF = fopen(nameWoExt, "wb");
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
            openF = fopen(fileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

            outF = fopen(nameWoExt, "wb");
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
				strcat(nameWoExt, ".xeut");
			}
			else
			{
				strcat(nameWoExt, ".xebn");
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
					openF = fopen(fileName, "rb");
                    if(jOpen(openF) == FILE_CANNOT_OPEN)
                    {
                        return;
                    }

					outF = fopen(nameWoExt, "wb");
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
            seedNumber = rand();

			if(ftNum == 1)
			{
				strcat(nameWoExt, ".xeu2");
			}
			else
			{
				strcat(nameWoExt, ".xeb2");
			}

			openF = fopen(fileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			outF = fopen(nameWoExt, "wb");
            if(jOpen(outF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			printf("処理中...\n");
			genXENC2(seedNumber, openF, outF);
		}
		else if(verSelect == 3)
		{
			openF = fopen(fileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			strcat(nameWoExt, ".xeb3");
			outF = fopen(nameWoExt, "wb");
            if(jOpen(outF) == FILE_CANNOT_OPEN)
            {
                return;
            }

            seedNumber = genRand32();

			printf("処理中...\n");
			genXENC3(openF, outF, seedNumber, fileExt);
		}
		else if(verSelect == 4)
		{
			openF = fopen(fileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			strcat(nameWoExt, ".xeb4");
			outF = fopen(nameWoExt, "wb");
            if(jOpen(outF) == FILE_CANNOT_OPEN)
            {
                return;
            }

            seedNumber = genRand32();

			printf("処理中...\n");
			genXENC4(openF, outF, seedNumber, fileExt);
		}
   		else if(verSelect == 5)
		{
			openF = fopen(fileName, "rb");
            if(jOpen(openF) == FILE_CANNOT_OPEN)
            {
                return;
            }

			strcat(nameWoExt, ".xeb5");
			outF = fopen(nameWoExt, "wb");
            if(jOpen(outF) == FILE_CANNOT_OPEN)
            {
                return;
            }

            seedNumber = genRand32();

			printf("処理中...\n");
			genXENC5(openF, outF, seedNumber, fileExt);
		}
	}
	else
	{
        printf("不明なエラーが発生しました。\n"); 
        return;       
    }

	#ifdef DEBUGGING
	printf("in body() - freeing allocated memory:");
	#endif

	if(nameWoExt != NULL){
		free(nameWoExt);
	}
	if(fileExt != NULL){
		free(fileExt);
	}

	#ifdef DEBUGGING
	printf("done\n");
	#endif

	if (openF != NULL){
		fclose(openF);
	}
	if(outF != NULL){
		fclose(outF);
	}
}

int main(int argc, char *argv[])
{
	char fileName_Main[MAXFN] = { 0 };
	int ctrMain = 0;
    int defaultSeed = 0;

    defaultSeed = (int)time(NULL);
    srand(defaultSeed);
    setRand32(defaultSeed);

    if(argc < 2)
	{
		printf("入力ファイル名は？");
		scanf("%2047s", fileName_Main);
		fseek(stdin, (long)0, SEEK_SET);
		body(fileName_Main);
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