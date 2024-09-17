#include <stdlib.h>

#include "lexer.h"
#include "globals.h"

int remainingIdx = 0;
int tknCounter = 0;
int tknCounterPrime = 0;

char* arbPtr = "arbit";

void addToken(Token** tknArrPtr, TokenType typeIn, char* dataPtrIn) {

	int endToken = 0;

	if (typeIn == FILE_END) {

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

	if (remainingIdx < 5) {

		return false;

	} else if (strcmp(tempTknArr[*iptr], "Forge") == 0 &&
				strcmp(tempTknArr[*iptr + 1], "anew") == 0 &&
			    strcmp(tempTknArr[*iptr + 2], "a") == 0 &&
			    strcmp(tempTknArr[*iptr + 3], "variable") == 0 &&
			    strcmp(tempTknArr[*iptr + 4], "known") == 0 &&
			    strcmp(tempTknArr[*iptr + 5], "as") == 0) 
	{
		*iptr += 5;

		return true;

	} else {

		return false;

	}
}

bool varInitCheck(char** tempTknArr, int* iptr) {

	if (remainingIdx < 6) {

		return false;

	} else if (strcmp(tempTknArr[*iptr], "Let") == 0 &&
			   strcmp(tempTknArr[*iptr + 2], "be") == 0 &&
			   strcmp(tempTknArr[*iptr + 3], "ascribed") == 0 &&
			   strcmp(tempTknArr[*iptr + 4], "the") == 0 &&
			   strcmp(tempTknArr[*iptr + 5], "value") == 0 &&
			   strcmp(tempTknArr[*iptr + 6], "of") == 0) 
	{
		*iptr += 6;
		return true;

	} else {

		return false;

	}
}

bool printCheck(char** tempTknArr, int* iptr) {

	if (remainingIdx < 3) {

		return false;

	} else if (strcmp(tempTknArr[*iptr], "Exclaim") == 0 &&
			   strcmp(tempTknArr[*iptr + 1], "unto") == 0 &&
			   strcmp(tempTknArr[*iptr + 2], "the") == 0 &&
			   strcmp(tempTknArr[*iptr + 3], "world") == 0) 
	{

		*iptr += 3;
		return true;
	
	} else {

		return false;

	}
}

bool endStatementCheck(char** tempTknArr, int* iptr) {

	if (remainingIdx < 3) {

		return false;

	} else if (strcmp(tempTknArr[*iptr], "Thus") == 0 &&
		strcmp(tempTknArr[*iptr + 1], "concludes") == 0 &&
		strcmp(tempTknArr[*iptr + 2], "this") == 0 &&
		strcmp(tempTknArr[*iptr + 3], "statement") == 0) {
		*iptr += 3;

		return true;

	} else {

		return false;

	}
}

TokenType equalityStatementCheck(char** tempTknArr, int* iptr) {

	if (remainingIdx < 5) {

		return INVALID;

	} else if (strcmp(tempTknArr[*iptr + 1], "of") == 0 &&
		       strcmp(tempTknArr[*iptr + 3], "value") == 0 &&
		       strcmp(tempTknArr[*iptr + 4], "compared") == 0 &&
		       strcmp(tempTknArr[*iptr + 5], "to") == 0) {
		
		if (strcmp(tempTknArr[*iptr + 2], "meager") == 0) {

			return LESS_THAN;

		} else if (strcmp(tempTknArr[*iptr + 2], "abundant") == 0) {

			return GREATER_THAN;

		} else if (strcmp(tempTknArr[*iptr + 2], "equal") == 0) {

			return EQUAL_TO;

		} else if (strcmp(tempTknArr[*iptr + 2], "unequal") == 0) {

			return UNEQUAL_TO;

		} else {

			return INVALID;

		}

	} else {

		return INVALID;

	}
}

bool addCheck(char** tempTknArr, int* iptr) {

	if (remainingIdx < 1) {

		return false;

	} else if (strcmp(tempTknArr[*iptr], "Embolden") == 0 &&
		strcmp(tempTknArr[*iptr + 2], "with") == 0) {
		*iptr += 1;
		return true;

	} else {

		return false;

	}
}

bool subtractCheck(char** tempTknArr, int* iptr) {

	if (remainingIdx < 1) {

		return false;

	} else if (strcmp(tempTknArr[*iptr], "Rend") == 0 &&
		strcmp(tempTknArr[*iptr + 2], "from") == 0) 
	{
		*iptr += 1;
		return true;

	} else {

		return false;

	}
}

bool containsLetter(char* str) {

	for (int i = 0; i < strlen(str); i++) {

		if ((str[i] > 57 || str[i] < 48) && str[i] != 46) {

			return true;

		} else {

			return false;

		}
	}
}

TokenType valueChecker(char** tempTknArr, int* iptr) {

	if (strcmp(tempTknArr[*iptr], "QuoteA") == 0) {

		return STRING;

	} else if (!containsLetter(tempTknArr[*iptr])) {

		return NUMBER;

	} else {

		return VAR_REF;

	}
}

void tokenGenerator(char* strPtr, Token** tknArrPtr) {

	//***************** Cleaning up input-text *****************//

	int strIdx = 0;

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

	//***************** Creating tokens from cleaned input-text *****************//

	for (int i = 0; i < tknCounter; i++) {

		remainingIdx = tknCounter - i;

		if (varDecCheck(tokArr, &i)) {

			addToken(tknArrPtr, VAR_DEC, arbPtr);
			
		} else if (varInitCheck(tokArr, &i)) {

			addToken(tknArrPtr, VAR_INIT, arbPtr);
			addToken(tknArrPtr, VAR_REF, tokArr[i - 5]);
			
		} else if (strcmp(tokArr[i], "Whilst") == 0) {

			addToken(tknArrPtr, WHILE, arbPtr);
			
		} else if (strcmp(tokArr[i], "Should") == 0) {

			addToken(tknArrPtr, IF, arbPtr);

		} else if (strcmp(tokArr[i], "Otherwise") == 0) {

			addToken(tknArrPtr, ELSE, arbPtr);

		} else if (printCheck(tokArr, &i)) {

			addToken(tknArrPtr, PRINT, arbPtr);

		} else if (endStatementCheck(tokArr, &i)) {

			addToken(tknArrPtr, STATEMENT_END, arbPtr);

		} else if (equalityStatementCheck(tokArr, &i) != INVALID) {

			addToken(tknArrPtr, equalityStatementCheck(tokArr, &i), arbPtr);
			i += 5;

		} else if (subtractCheck(tokArr, &i)) {

			addToken(tknArrPtr, SUBTRACT, arbPtr);
			addToken(tknArrPtr, valueChecker(tokArr, &i), tokArr[i]);
			i++;

		} else if (addCheck(tokArr, &i)) {

			addToken(tknArrPtr, ADD, arbPtr);
			addToken(tknArrPtr, valueChecker(tokArr, &i), tokArr[i]);
			i++;

		} else {

			if (valueChecker(tokArr, &i) == STRING) {

				i++;
				addToken(tknArrPtr, STRING, tokArr[i]);
				i++;

			} else {

				addToken(tknArrPtr, valueChecker(tokArr, &i), tokArr[i]);

			}
		}
	}

	addToken(tknArrPtr, FILE_END, arbPtr);

}