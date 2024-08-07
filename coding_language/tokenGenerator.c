#include <stdlib.h>

#include "tokenGenerator.h"
#include "globals.h"

int remainingIdx = 0;
int tknCounterPrime = 0;

char* arbPtr = "arbit";

void addTokenToken(Token** tknArrPtr, TokenType typeIn, char* dataPtrIn) {

	int endToken = 0;

	if (typeIn == END) {

		endToken = 1;

	}

	Token token;
	token.type = typeIn;
	token.dataPtr = dataPtrIn;

	tknCounterPrime++;

	Token* tempArr = realloc(*tknArrPtr, sizeof(Token) * (tknCounterPrime + endToken));

	if (tempArr == NULL) {

		printf("ERROR. FAILED TO REALLOCATE MEMORY");
		exit(1);

	}

	tempArr[tknCounterPrime - 1] = token;

	*tknArrPtr = tempArr;

}

bool varDecCheck(char** tempTknArr, int* iptr) {

	if (remainingIdx < 6) {

		return false;

	} else if (strcmp(tempTknArr[*iptr], "Forge") == 0 &&
				strcmp(tempTknArr[*iptr + 1], "anew") == 0 &&
			    strcmp(tempTknArr[*iptr + 2], "a") == 0 &&
			    strcmp(tempTknArr[*iptr + 3], "variable") == 0 &&
			    strcmp(tempTknArr[*iptr + 4], "known") == 0 &&
			    strcmp(tempTknArr[*iptr + 5], "as") == 0) 
	{
		*iptr += 6;
		return true;

	} else {

		return false;

	}
}

bool varInitCheck(char** tempTknArr, int* iptr) {

	if (remainingIdx < 7) {

		return false;

	} else if (strcmp(tempTknArr[*iptr], "Let") == 0 &&
			   strcmp(tempTknArr[*iptr + 2], "be") == 0 &&
			   strcmp(tempTknArr[*iptr + 3], "ascribed") == 0 &&
			   strcmp(tempTknArr[*iptr + 4], "the") == 0 &&
			   strcmp(tempTknArr[*iptr + 5], "value") == 0 &&
			   strcmp(tempTknArr[*iptr + 6], "of") == 0) 
	{
		*iptr += 7;
		return true;

	} else {

		return false;

	}
}

bool printCheck(char** tempTknArr, int* iptr) {

	if (remainingIdx < 5) {

		return false;

	} else if (strcmp(tempTknArr[*iptr], "Exclaim") == 0 &&
			   strcmp(tempTknArr[*iptr], "unto") == 0 &&
			   strcmp(tempTknArr[*iptr], "the") == 0 &&
			   strcmp(tempTknArr[*iptr], "world") == 0) 
	{

		*iptr += 5;
		return true;
	
	} else {

		return false;

	}
}

TokenType valueChecker(char** tempTknArr, int* iptr) {

	if (strcmp(tempTknArr[*iptr], "QuoteA") == 0) {

		return STRING;

	} else {

		return NUMBER;

	}
}

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
			int singleCharAdjust = 0;

			while (!isspace(strPtr[strIdx])) {

				if (strPtr[strIdx] != ':') {

					charCounter++;

				} else {

					singleCharAdjust = 1;

				}

				strIdx++;
			}

			if (charCounter > 0) {

				char* ptr = malloc(charCounter + 1);
				strncpy(ptr, strPtr + strIdx - charCounter - singleCharAdjust, charCounter);
				ptr[charCounter] = '\0';

				tknCounter++;

				char** tempArr = realloc(tokArr, sizeof(char*) * tknCounter);

				if (tempArr == NULL) {

					printf("ERROR. FAILED TO REALLOCATE MEMORY");
					exit(1);

				}

				tempArr[tknCounter - 1] = ptr;

				tokArr = tempArr;

				if (singleCharAdjust > 0) {

					tknCounter++;

					char* colon = ":";
					char** tempArr = realloc(tokArr, sizeof(char*) * tknCounter);

					if (tempArr == NULL) {

						printf("ERROR. FAILED TO REALLOCATE MEMORY");
						exit(1);
					}

					tempArr[tknCounter - 1] = colon;

					tokArr = tempArr;

				}
			}
		}

		strIdx++;

	}

	for (int i = 0; i < tknCounter; i++) {

		remainingIdx = tknCounter - i;

		if (varDecCheck(tokArr, &i)) {

			addTokenToken(tknArrPtr, VAR_DEC, arbPtr);
			addTokenToken(tknArrPtr, VAR_REF, tokArr[i]);
			
		} else if (varInitCheck(tokArr, &i)) {

			TokenType tempType;
			char* tempValue;

			if (valueChecker(tokArr, &i) == STRING) {

				tempType = STRING;
				tempValue = tokArr[i + 1];

			} else {

				tempType = NUMBER;
				tempValue = tokArr[i];

			}
			
			addTokenToken(tknArrPtr, VAR_REF, tokArr[i - 6]);
			addTokenToken(tknArrPtr, VAR_INIT, arbPtr);
			addTokenToken(tknArrPtr, tempType, tempValue);
			
		} else if (strcmp(tokArr[i], "Whilst") == 0) {

			addTokenToken(tknArrPtr, WHILE, arbPtr);
			
		} else if (strcmp(tokArr[i], ":") == 0) {

			addTokenToken(tknArrPtr, COLON, arbPtr);

		} 
	}

	addTokenToken(tknArrPtr, END, arbPtr);

	free(tokArr);

}