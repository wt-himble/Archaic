#include <stdlib.h>

#include "tokenGenerator.h"

bool isVarDef(char* strPtr, int strIdx) {

	char tempArray[31];

	strncpy(tempArray, strPtr + strIdx + 1, 31 - strIdx);
	tempArray[30] = '\0';

	if (strcmp(tempArray, "et there be a variable called ") == 0) {

		return true;
		free(tempArray);

	} else {

		return false;
		free(tempArray);

	}
}

void tokenGenerator(char* strPtr, char* tknArrPtr) {

	int strIdx = 0;

	while (strPtr[strIdx] != '\0') {

		if (strPtr[strIdx] == 'L') {

			if (isVarDef(strPtr, strIdx)) {

				strIdx += 31;

				Token* tempTknPtr = realloc(tknArrPtr, sizeof(Token) * 2);

				Token A;
				A.type = VAR_PREC;
				A.dataPtr = NULL;

				Token B;
				B.type = VAR_DEC;

				int charCounter = 0;

				while (strPtr[strIdx] != ';') {

					charCounter++;

				}

				B.dataPtr = malloc(charCounter + 1);

				strncpy(B.dataPtr, strPtr + strIdx, charCounter);

				B.dataPtr[-1] = '\0';

				printf("This is the name of the variable found: %s", B.dataPtr);
			}
		}

		strIdx++;
	}
}