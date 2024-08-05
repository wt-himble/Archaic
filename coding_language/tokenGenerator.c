#include <stdlib.h>

#include "tokenGenerator.h"
#include "globals.h"

bool varDecVerify(char** tknArrPtr, int tknIdx) {

	bool valid = true;

	if (strcmp(tknArrPtr[tknIdx + 1], "there") != 0 ||
		strcmp(tknArrPtr[tknIdx + 2], "be") != 0 ||
		strcmp(tknArrPtr[tknIdx + 3], "a") != 0 ||
		strcmp(tknArrPtr[tknIdx + 4], "variable") != 0 ||
		strcmp(tknArrPtr[tknIdx + 5], "called") != 0) {

		valid = false;

	}

	return valid;
}

void tokenGenerator(char* strPtr, Token** tknArrPtr) {

	int strIdx = 0;
	int tempTknCounter = 0;
	int tknCounter = 0;

	char** tokArr = NULL;

	while (strPtr[strIdx] != '\0') {

		int charCounter = 0;

		while (strPtr[strIdx] != ' ' && strPtr[strIdx] != '\n') {

			charCounter++;
			strIdx++;

		}

		char** tempArr = realloc(tokArr, sizeof(char*) * (tempTknCounter+1));

		if (tempArr == NULL) {

			printf("ERROR. MEMORY FAILED TO REALLOCATE.");
			exit(1);

		}

		char* p = malloc(charCounter + 1);
		strncpy(p, strPtr + strIdx - charCounter, charCounter);
		p[charCounter] = '\0';

		tempArr[tempTknCounter] = p;

		tokArr = tempArr;

		tempTknCounter++;
		strIdx++;

	}

	for (int i = 0; i < tempTknCounter; i++) {

		if (strcmp(tokArr[i], "Let") == 0) {

			if (varDecVerify(tokArr, i)) {

				i += 6;
				tknCounter += 2;

				printf("Variable declaration found. Variable reference is: %s\n", tokArr[i]);

				Token A;
				A.type = VAR_DEC;
				A.dataPtr = NULL;

				Token B;
				B.type = VAR_REF;
				B.dataPtr = tokArr[i];

				Token* tempArr = realloc(*tknArrPtr, sizeof(Token) * tknCounter);

				if (tempArr == NULL) {

					printf("ERROR. FAILED TO REALLOCATE MEMORY");
					exit(1);

				}

				tempArr[tknCounter - 2] = A;
				tempArr[tknCounter - 1] = B;

				*tknArrPtr = tempArr;

			} 
		}
	}
}

//
//void tokenGenerator(char* strPtr, Token** tknArrPtr) {
//
//	int strIdx = 0;
//	int numOfTokens = 0;
//
//	while (strPtr[strIdx] != '\0') {
//
//		switch (strPtr[strIdx]) {
//
//			case 'L':
//
//				if (isVarDec(strPtr, strIdx)) {
//
//					strIdx += 31;
//					numOfTokens += 2;
//
//					Token* tempTknPtr = realloc(*tknArrPtr, sizeof(Token) * numOfTokens);
//
//					if (tempTknPtr == NULL) {
//
//						printf("\nERROR. Failed to reallocate memory in token array");
//
//					} else {
//
//						Token A;
//						A.type = VAR_DEC;
//						A.dataPtr = NULL;
//
//						Token B;
//						B.type = VAR_REF;
//
//						int charCounter = 0;
//
//						while (strPtr[strIdx] != ';') {
//
//							charCounter++;
//							strIdx++;
//
//						}
//
//						B.dataPtr = malloc(charCounter + 1);
//
//						strncpy(B.dataPtr, strPtr + strIdx - charCounter, charCounter);
//
//						B.dataPtr[charCounter] = '\0';
//
//						tempTknPtr[numOfTokens - 2] = A;
//						tempTknPtr[numOfTokens - 1] = B;
//
//						*tknArrPtr = tempTknPtr;
//
//						printf("Variable declaration found. Variable reference is: %s\n", tempTknPtr[numOfTokens - 1].dataPtr);
//
//					}
//				}
//
//				break;
//
//			case 'W':
//
//				if (isWhile(strPtr, strIdx)) {
//
//					strIdx += 7;
//					numOfTokens += 4;
//
//					Token* tempTknPtr = realloc(*tknArrPtr, sizeof(Token) * numOfTokens);
//
//					if (tempTknPtr == NULL) {
//
//						printf("ERROR. Failed to reallocate memory in token array.");
//
//					} else {
//
//						Token A;
//						A.type = WHILE;
//						A.dataPtr = NULL;
//
//						Token B;
//						B.type = VAR_REF;
//
//						Token C;
//						C.dataPtr = NULL;
//
//						Token D;
//
//						int charCounter = 0;
//
//						while (strPtr[strIdx] != ' ') {
//
//							charCounter++;
//							strIdx++;
//
//						}
//
//						B.dataPtr = malloc(charCounter + 1);
//						strncpy(B.dataPtr, strPtr + strIdx - charCounter, charCounter);
//						B.dataPtr[charCounter] = '\0';
//
//						
//
//
//
//
//
//
//					}
//
//					
//
//
//
//				}
//
//				
//
//			
//		}
//
//		strIdx++;
//
//	}
//	
//}