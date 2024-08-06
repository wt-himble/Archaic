#include <stdlib.h>

#include "tokenGenerator.h"
#include "globals.h"

void tokenGenerator(char* strPtr, Token** tknArrPtr) {

	int strIdx = 0;
	int tknCounter = 0;

	char** tokArr = NULL;

	while (strPtr[strIdx] != '\0') {

		if (strPtr[strIdx] == '"') {

			int charCounter = 0;

			char* quoteA = "QuoteA";

			while (true) {

				strIdx++;

				if (strPtr[strIdx] == '"') {

					break;

				}

				charCounter++;
			}

			char* text = malloc(charCounter + 1);
			strncpy(text, strPtr + strIdx - charCounter, charCounter);
			text[charCounter] = '\0';

			char* quoteB = "QuoteB";

			tknCounter += 3;

			char** tempArr = realloc(tokArr, sizeof(char*) * tknCounter);

			if (tempArr == NULL) {

				printf("ERROR. FAILED TO REALLOCATE MEMORY");
				exit(1);

			}

			tempArr[tknCounter - 3] = quoteA;
			tempArr[tknCounter - 2] = text;
			tempArr[tknCounter - 1] = quoteB;
			
			tokArr = tempArr;
			
		} else {

			int charCounter = 0;

			while (!isspace(strPtr[strIdx])) {

				strIdx++;
				charCounter++;
			
			}

			if (charCounter > 0) {

				char* ptr = malloc(charCounter + 1);
				strncpy(ptr, strPtr + strIdx - charCounter, charCounter);
				ptr[charCounter] = '\0';

				tknCounter++;

				char** tempArr = realloc(tokArr, sizeof(char*) * tknCounter);

				if (tempArr == NULL) {

					printf("ERROR. FAILED TO REALLOCATE MEMORY");
					exit(1);

				}

				tempArr[tknCounter - 1] = ptr;

				tokArr = tempArr;

			}
		}

		strIdx++;

	}

	for (int i = 0; i < tknCounter; i++) {

		printf("%s\n", tokArr[i]);

	}
}

/*else {

			while (!isspace(strPtr[strIdx])) {

				if (charCounter > 0) {

					char* ptr = malloc(charCounter + 1);
					strncpy(ptr, strPtr + strIdx - charCounter, charCounter);
					ptr[charCounter] = '\0';

					tknCounter++;

					char** tempArr = realloc(tokArr, sizeof(char*) * tknCounter);

					if (tempArr == NULL) {

						printf("ERROR. FAILED TO REALLOCATE MEMORY");
						exit(1);

					}

					tempArr[tknCounter - 1] = ptr;

					tokArr = tempArr;

				} else {

					strIdx++;
				}
			}
		}
	}*/

//
//	for (int i = 0; i < tempTknCounter; i++) {
//
//		if (strcmp(tokArr[i], "Let") == 0) {
//
//			if (varDecVerify(tokArr, i)) {
//
//				i += 6;
//				tknCounter += 2;
//
//				printf("Variable declaration found. Variable reference is: %s\n", tokArr[i]);
//
//				Token A;
//				A.type = VAR_DEC;
//				A.dataPtr = NULL;
//
//				Token B;
//				B.type = VAR_REF;
//				B.dataPtr = tokArr[i];
//
//				Token* tempArr = realloc(*tknArrPtr, sizeof(Token) * tknCounter);
//
//				if (tempArr == NULL) {
//
//					printf("ERROR. FAILED TO REALLOCATE MEMORY");
//					exit(1);
//
//				}
//
//				tempArr[tknCounter - 2] = A;
//				tempArr[tknCounter - 1] = B;
//
//				*tknArrPtr = tempArr;
//
//			} 
//
//		} else if (strcmp(tokArr[i], "Whilst") == 0) {
//
//			tknCounter++;
//
//			printf("While loop found.");
//
//			Token A;
//			A.type = WHILE;
//			A.dataPtr = NULL;
//
//			Token* tempArr = realloc(*tknArrPtr, sizeof(Token) * tknCounter);
//
//			if (tempArr == NULL) {
//
//				printf("ERROR. FAILED TO REALLOCATE MEMORY");
//				exit(1);
//
//			}
//
//			tempArr[tknCounter - 1] = A;
//
//			*tknArrPtr = tempArr;
//
//		}
//	}
//}

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