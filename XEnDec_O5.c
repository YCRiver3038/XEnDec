#include "xemod5.c"
#include "filend.h"
#include "xemod_common.h"

void body(char fileName[])
{
	FILE *openF = NULL;
	FILE *outF = NULL;
	int V5seed = 0;    

	char* nameWoExt = NULL;
	char* fileExt = NULL;
	int ftNumRet = 0;

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

	ftNumRet = fileTypeDetect(fileExt);

	/*種別ごとの取扱いかた------------------------------------------*/
	if (ftNumRet == 10) //入力がVer5(xeb5)
	{
		openF = fopen(fileName, "rb");
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
            return;
        }
		
        printf("処理中...\n");
		genXDEC5(openF, nameWoExt);
	}
	else if ( ftNumRet == 0 ) //入力がふつうのファイル
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

        V5seed = genRand32();

        printf("処理中...\n");
        genXENC5(openF, outF, V5seed, fileExt);
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