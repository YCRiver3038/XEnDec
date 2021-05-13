#ifndef XENDEC_COMMON_H
#define XENDEC_COMMON_H 

#define DEBUGGING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define FILE_CANNOT_OPEN -1
#define FILE_OPENED 0
#define RAND_A 145
#define RAND_B 469
#define RAND_M 1073741827

#define DEFAULT_KEYSIZE 64
#define MAX_KEYSIZE 65536
#define MAXFN 2048
#define V1KEY_CORRECT "RNDat"
#define V2CORRECT "XENCV2"
#define V3CORRECT "XENCV3"
#define V4CORRECT "XENCV4"
#define V5CORRECT "XENCV5"
#define SIZE_V1KEY_CORRECT 5
#define SIZE_V2CORRECT 6
#define SIZE_V3CORRECT 6
#define SIZE_V4CORRECT 6
#define SIZE_V5CORRECT 6

#define KNLENGTH 4
#define EXTENTION_LIMIT 12

#define V1KEY_IDERR -1
#define V1KEY_SUCCESS 1

#define V3_IDERR -1
#define V3_SUCCESS 0

#define V4_IDERR -1
#define V4_SUCCESS 0

#define V5_IDERR -1
#define V5_SUCCESS 0
#define V5BSHIFT_ARRAY_MAX 24
#define V5BSHIFT_BSLENGTH_MAX 12

#define FILE_ALREADY_DECRYPTED -1

#endif