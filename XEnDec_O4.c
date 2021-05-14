#include "filend.h"
#include "xemod_common.h"
#include "xemod4.h"

void body(char fileName[])
{
	#ifdef DEBUGGING
		int tempctr = 0;
	#endif
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

	fileExt = (char*)calloc(EXTENTION_LIMIT, sizeof(char));
	if(!fileExt){
		printf("メモリが確保できませんでした\n");
		return;
	}

	#ifdef DEBUGGING
	printf("in body() - filename to be analyzed : %s\n", fileName);
	printf("in body() - throwing address of nameWoExt to fileNameDetect (address:%p)\n", &nameWoExt);
	printf("in body() - throwing address of fileExt to fileNameDetect (address:%p)\n", &fileExt);
	#endif
	
	fileNameDetect(fileName, &nameWoExt, &fileExt);

	#ifdef DEBUGGING
	printf("in body() - received filename from fileNameDetect:%s\n", nameWoExt);
	printf("in body() - received extension from fileNameDetect:%s\n", fileExt);
	#endif

	#ifdef DEBUGGING
	printf("in body() - filename before detecting file type : %s\n", nameWoExt);
	printf("address:%p\n", nameWoExt);
	printf("RAW : ");
	for(tempctr = 0; (nameWoExt[tempctr] != 0) && (tempctr < MAXFN); tempctr++){
		printf("%02x ", nameWoExt[tempctr]);
	}
	printf("\ncounted:%d\n", tempctr);

	printf("in body() - extention before detecting file type : %s\n", fileExt);
	printf("address:%p\n", fileExt);
	printf("RAW : ");
	for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
		printf("%02x ", fileExt[tempctr]);
	}
	printf("\ncounted:%d\n", tempctr);
	#endif

	ftNumRet = fileTypeDetect(&fileExt);

	#ifdef DEBUGGING
	printf("in body() - filename after detecting file type : %s\n", nameWoExt);
	printf("address:%p\n", nameWoExt);
	printf("RAW : ");
	for(tempctr = 0; (nameWoExt[tempctr] != 0) && (tempctr < MAXFN); tempctr++){
		printf("%02x ", nameWoExt[tempctr]);
	}
	printf("\ncounted:%d\n", tempctr);

	printf("in body() - extention before detecting file type : %s\n", fileExt);
	printf("address:%p\n", fileExt);
	printf("RAW : ");
	for(tempctr = 0; tempctr < EXTENTION_LIMIT; tempctr++){
		printf("%02x ", fileExt[tempctr]);
	}
	printf("\ncounted:%d\n", tempctr);
	#endif


	/*種別ごとの取扱いかた------------------------------------------*/
	if (ftNumRet == 9) //入力がVer4(xeb4)
	{
		#ifdef DEBUGGING
		printf("in body() - detected file type : %d - xeb4\n", ftNumRet);
		printf("in body() - file to be opened as input : %s\n", fileName);
		#endif

		openF = fopen(fileName, "rb");
		#ifdef DEBUGGING
		printf("in body() - throwing pointer openF(value:%p) to jOpen()\n", openF);
		#endif
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
			#ifdef DEBUGGING
			printf("in body() - thrown file name:%s\n", fileName);
			#endif
            return;
        }

		printf("処理中...\n");
		genXDEC4(openF, nameWoExt);
	}
	else if ( ftNumRet == 0 ) //入力がふつうのファイル
	{
		#ifdef DEBUGGING
		printf("in body() - detected file type : %d - normal file\n", ftNumRet);
		printf("in body() - file to be opened as input : %s\n", fileName);
		printf("RAW : ");
		for(tempctr = 0; (fileName[tempctr] != 0) && (tempctr < MAXFN); tempctr++){
			printf("%02x ", fileName[tempctr]);
		}
		printf("\ncounted:%d\n", tempctr);

		#endif

        openF = fopen(fileName, "rb");
		#ifdef DEBUGGING
		printf("in body() - throwing pointer openF(value:%p) to jOpen()\n", openF);
		#endif
		if(jOpen(openF) == FILE_CANNOT_OPEN)
        {
			#ifdef DEBUGGING
			printf("in body() - thrown file name:%s\n", fileName);
			#endif
            return;
        }
	
		#ifdef DEBUGGING
		printf("in body() - filename before concatenate : %s\n", nameWoExt);
		printf("RAW : ");
		for(tempctr = 0; (nameWoExt[tempctr] != 0) && (tempctr < MAXFN); tempctr++){
			printf("%02x ", nameWoExt[tempctr]);
		}
		printf("\ncounted:%d\n", tempctr);
		#endif
	
        strcat(nameWoExt, ".xeb4");

		#ifdef DEBUGGING
		printf("in body() - file to be opened as output : %s\n", nameWoExt);
		printf("RAW : ");
		for(tempctr = 0; (nameWoExt[tempctr] != 0) && (tempctr < MAXFN); tempctr++){
			printf("%02x ", nameWoExt[tempctr]);
		}
		printf("\ncounted:%d\n", tempctr);
		#endif

        outF = fopen(nameWoExt, "wb");
		#ifdef DEBUGGING
		printf("in body() - throwing pointer outF(value:%p) to jOpen()\n", outF);
		#endif

        if(jOpen(outF) == FILE_CANNOT_OPEN)
        {
			#ifdef DEBUGGING
			printf("in body() - thrown file name:%s\n", nameWoExt);
			printf("RAW : ");
			for(tempctr = 0; (nameWoExt[tempctr] != 0) && (tempctr < MAXFN); tempctr++){
				printf("%02x ", nameWoExt[tempctr]);
			}
			printf("\ncounted:%d\n", tempctr);
			#endif
            return;
        }

        V4seed = genRand32();

        printf("処理中...\n");
		
		#ifdef DEBUGGING
		printf("in body() - entering genXENC4()\n");
		#endif

        genXENC4(openF, outF, V4seed, fileExt);

		#ifdef DEBUGGING
		printf("in body() - exited from genXENC4()\n");
		#endif

	}
	else
	{
        printf("スキップしました。\n"); 
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
	#ifdef DEBUGGING
	printf("in body() - closiong files\n");
	#endif

	if (openF != NULL){
		fclose(openF);
	}
	if(outF != NULL){
		fclose(outF);
	}

	#ifdef DEBUGGING
	printf("in body() - file closed\n");
	#endif
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