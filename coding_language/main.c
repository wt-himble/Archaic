#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

// ********** NOTES FROM THE AUTHOR ********** //
// Welcome to Archaic, an interpreted language I developed!
// 
// Who am I? My name is wt-himble, a computer engineering student based
// out of Queen's University Canada.
//
// Archaic is meant to be a simple esoteric language, with syntax
// that reads like medieval prose. It is dynamically typed, meaning
// variables do not need to have their types declared prior to runtime.
// 
// P.S. I have yet to do any robust testing, so it's possible 
// some code may not work :)

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

	// ********** Putting it all together ********** //

	Token* tokenArray = NULL;

	tokenGenerator(srcBuffer, &tokenArray);
	M_Node* rootNode = ASTGenerator(tokenArray);
	RunAST(rootNode);
	
}
