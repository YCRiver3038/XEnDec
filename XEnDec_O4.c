#include "xemod4.h"
#include "filend.h"
#include "xemod_common.h"

void body(char fileName[])
{
	FILE *openF = NULL;
	FILE *outF = NULL;
	int V4seed = 0;

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

	#ifdef DEBUGGING
	printf("filename to be analyzed : %s\n", fileName);
	printf("throwing address of nameWoExt: %p\n", &nameWoExt);
	printf("throwing address of fileExt: %p\n", &fileExt);
	#endif
	
	fileNameDetect(fileName, &nameWoExt, &fileExt);

	#ifdef DEBUGGING
	printf("received filename:%s\n", nameWoExt);
	printf("received extension:%s\n", fileExt);
	#endif

	#ifdef DEBUGGING
	printf("filename before detecting file type : %s\n", nameWoExt);
	#endif

	ftNumRet = fileTypeDetect(&fileExt);

	#ifdef DEBUGGING
	printf("filename after detecting file type : %s\n", nameWoExt);
	#endif


	/*種別ごとの取扱いかた------------------------------------------*/
	if (ftNumRet == 9) //入力がVer4(xeb4)
	{
		#ifdef DEBUGGING
		printf("detected file type : %d - xeb4\n", ftNumRet);
		printf("file to be opened as input : %s\n", fileName);
		#endif

		openF = fopen(fileName, "rb");
		#ifdef DEBUGGING
		printf("at body() - throwing pointer openF(value:%p) to jOpen()\n", openF);
		#endif
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
			#ifdef DEBUGGING
			printf("at body() - thrown file name:%s\n", fileName);
			#endif
            return;
        }

		printf("処理中...\n");
		genXDEC4(openF, nameWoExt);
	}
	else if ( ftNumRet == 0 ) //入力がふつうのファイル
	{
		#ifdef DEBUGGING
		printf("detected file type : %d - normal file\n", ftNumRet);
		printf("file to be opened as input : %s\n", fileName);
		#endif

        openF = fopen(fileName, "rb");
		#ifdef DEBUGGING
		printf("at body() - throwing pointer openF(value:%p) to jOpen()\n", openF);
		#endif
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
			#ifdef DEBUGGING
			printf("at body() - thrown file name:%s\n", fileName);
			#endif
            return;
        }
	
		#ifdef DEBUGGING
		printf("filename before concatenate : %s\n", nameWoExt);
		#endif
	
        strcat(nameWoExt, ".xeb4");
		#ifdef DEBUGGING
		printf("file to be opened as output : %s\n", nameWoExt);
		#endif

        outF = fopen(nameWoExt, "wb");
		#ifdef DEBUGGING
		printf("at body() - throwing pointer outF(value:%p) to jOpen()\n", outF);
		#endif

        if(jOpen(outF) == FILE_CANNOT_OPEN)
        {
			#ifdef DEBUGGING
			printf("at body() - thrown file name:%s\n", nameWoExt);
			#endif
            return;
        }

        V4seed = genRand32();

        printf("処理中...\n");
        genXENC4(openF, outF, V4seed, fileExt);
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