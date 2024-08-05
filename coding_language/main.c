#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "tokenGenerator.h"

int main() {

	// ********** Getting data from source file ********** //

	FILE* f;
	char* srcBuffer = 0;

	f = fopen("test_source.txt", "rb");

	if (f) {

		fseek(f, 0, SEEK_END);
		long fileSize = ftell(f);
		fseek(f, 0, SEEK_SET);

		srcBuffer = malloc(fileSize + 1);

		if (srcBuffer) {

			fread(srcBuffer, 1, fileSize, f);

		} else {

			printf("ERROR. FAILED TO ALLOCATE MEMORY.");

		}

		fclose(f);

		srcBuffer[fileSize] = '\0';

	} else {

		printf("ERROR. FAILED TO OPEN FILE.");

	} 

	// ********** Creating tokens ********** //

	Token* tokenArray = NULL;

	tokenGenerator(srcBuffer, &tokenArray);

}