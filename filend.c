#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DEBUGGING

#define MAXFN (INT32_MAX - 1)
#define EXTENTION_LIMIT (INT32_MAX - 1)

void fileNameDetect(char* inputedFileName, char** nameDest, char** extDest) {

	char* internalFileName = NULL;
	char* ftype = NULL;

	int32_t nStr = 0;
	int32_t nExt = 0;

	int32_t ctr1 = 0;
	int32_t ctr2 = 0;

	int32_t nDestSize = 0;
	int32_t eDestSize = 0;

	#ifdef DEBUGGING
	printf("in fileNameDetect - thrown filename to detect : %s\n", inputedFileName);
	printf("in fileNameDetect - thrown pointer to nameDest : %p\n", nameDest);
	printf("in fileNameDetect - thrown pointer to extDest : %p\n", extDest);
	#endif

	/*拡張子の抽出------------------------------*/
	nStr = 0;
	while (inputedFileName[nStr] != '\0'){ //ファイル名の長さを検出：インクリメントの結果、終端を示す0x00を"含まない"長さがnStrに記録される。(配列のインデックスは0スタートのため)
		nStr++;
		if(nStr > MAXFN){
			printf("ファイル名が長過ぎます。\n");
			return;
		}
	}
	nDestSize = nStr; //ファイル名の長さを格納

	nExt = 0;
	while (inputedFileName[nStr] != '.'){ //拡張子を除いたファイル名の長さを検出：終端文字'\0'から遡り参照し、区切り文字までnStrをデクリメント
		nStr--;
		nExt++; 
		if (nStr < 0){ //拡張子の無いパターン：拡張子を除いたファイル名の長さを検出したつもりが、ファイル名の長さが検出された状態
			nStr = nExt - 1; //nExtはファイル名の長さより1多くなっている。→結果的に終端文字を含む長さになっている。
			nExt = 0;
			break;
		}
	} 
	/* 区切文字がある場合、nStrをデクリメントし同時にnExtをインクリメントした結果、inputedFileName[nStr]は区切り文字を指している
	  - すなわちnStrが区切文字のインデックスを示している。
	    また、nExtは終端文字を"含まず"、区切文字を"含んだ"文字列の長さを示している。(.ext→4) */

	internalFileName = (char*)calloc(nStr + 1, sizeof(char));
	if(internalFileName == NULL){
		printf("メモリが確保できませんでした。\n");
		return;
	}
	memset(internalFileName, 0, (nStr + 1));

	ftype = (char*)calloc(nExt + 1, sizeof(char));
	if(ftype == NULL){
		printf("メモリが確保できませんでした。\n");
		return;
	}
	memset(ftype, 0, (nExt + 1));

	//文字列のコピー
	for(ctr1 = 0; ctr1 < nStr; ctr1++){
		internalFileName[ctr1] = inputedFileName[ctr1];
	}
	for(ctr2 = 0; ctr2 < nExt; ctr2++){
		ftype[ctr2] = inputedFileName[nStr + ctr2];
	}

    /*----------------------------------------------------*/

	#ifdef DEBUGGING
	printf("in fileNameDetect - throwing internalFilename : %s\n", internalFileName);
	printf("in fileNameDetect - throwing ftype : %s\n", ftype);
	#endif

	for (ctr1 = 0; (internalFileName[ctr1] != '\0'); ctr1++){
		(*nameDest)[ctr1] = internalFileName[ctr1];
	}
	for (ctr1 = 0; (ftype[ctr1] != '\0'); ctr1++){
		(*extDest)[ctr1] = ftype[ctr1];
	}

	#ifdef DEBUGGING
	printf("in fileNameDetect - *nameDest : %s\n", *nameDest);
	printf("in fileNameDetect - *extDest : %s\n", *extDest);
	#endif

	if(internalFileName != NULL){
		free(internalFileName);
	}
	if(ftype != NULL){
		free(ftype);
	}

	return;
}