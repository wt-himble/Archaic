#include <stdlib.h>

#include "tokenGenerator.h"
#include "globals.h"

int remainingIdx = 0;

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

	int tknCounterPrime = 0;

	for (int i = 0; i < tknCounter; i++) {

		remainingIdx = tknCounter - i;

		if (varDecCheck(tokArr, &i)) {

			tknCounterPrime += 2;
	
			Token varDec;
			varDec.type = VAR_DEC;
			varDec.dataPtr = NULL;

			Token varRef;
			varRef.type = VAR_REF;
			varRef.dataPtr = tokArr[i];

			Token* tempArr = realloc(*tknArrPtr, sizeof(Token) * tknCounterPrime);

			if (tempArr == NULL) {

				printf("ERROR. FAILED TO REALLOCATE MEMORY");
				exit(1);

			}

			tempArr[tknCounterPrime - 2] = varDec;
			tempArr[tknCounterPrime - 1] = varRef;

			*tknArrPtr = tempArr;
			
		} else if (varInitCheck(tokArr, &i)) {

			tknCounterPrime += 3;

			Token varRef;
			varRef.type = VAR_REF;
			varRef.dataPtr = tokArr[i - 6];

			Token varInit;
			varInit.type = VAR_INIT;
			varInit.dataPtr = NULL;

			Token value;
			value.type = valueChecker(tokArr, &i);
			
			if (value.type == STRING) {

				value.dataPtr = tokArr[i + 1];
				i += 2;

			} else {

				value.dataPtr = tokArr[i];

			}

			Token* tempArr = realloc(*tknArrPtr, sizeof(Token) * tknCounterPrime);

			if (tempArr == NULL) {

				printf("ERROR. FAILED TO REALLOCATE MEMORY");
				exit(1);

			}

			tempArr[tknCounterPrime - 3] = varRef;
			tempArr[tknCounterPrime - 2] = varInit;
			tempArr[tknCounterPrime - 1] = value;

			*tknArrPtr = tempArr;

		} else if (strcmp(tokArr[i], "Whilst") == 0) {

			tknCounterPrime++;

			Token whileToken;
			whileToken.type = WHILE;
			whileToken.dataPtr = NULL;

			Token* tempArr = realloc(*tknArrPtr, sizeof(Token) * tknCounterPrime);

			if (tempArr == NULL) {

				printf("ERROR. FAILED TO REALLOCATE MEMORY");
				exit(1);

			}

			tempArr[tknCounterPrime - 1] = whileToken;

			*tknArrPtr = tempArr;
			
		} else if (strcmp(tokArr[i], ":") == 0) {

			tknCounterPrime++;

			Token colonToken;
			colonToken.type = COLON;
			colonToken.dataPtr = NULL;

			Token* tempArr = realloc(*tknArrPtr, sizeof(Token) * tknCounterPrime);

			if (tempArr == NULL) {

				printf("ERROR. FAILED TO REALLOCATE MEMORY");
				exit(1);
			}

			tempArr[tknCounterPrime - 1] = colonToken;

			*tknArrPtr = tempArr;

		} else if (printCheck(tokArr, &i)) {

			tknCounterPrime += 2;

			Token printToken;
			printToken.type = PRINT;
			printToken.dataPtr = NULL;

		}
	}

	Token* tempArr = realloc(*tknArrPtr, sizeof(Token) * (tknCounterPrime + 1));

	if (tempArr == NULL) {

		printf("ERROR. FAILED TO REALLOCATE MEMORY");
		exit(1);

	}

	Token endToken;
	endToken.type = END;
	endToken.dataPtr = NULL;

	tempArr[tknCounterPrime] = endToken;

	*tknArrPtr = tempArr;

	free(tokArr);

}