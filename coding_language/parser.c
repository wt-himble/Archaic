#include <stdlib.h>
#include <stdio.h>

#include "globals.h"
#include "parser.h"

int numOfReturnNodes = 0;

M_Node createCondSubTree(Token* tknArrPtr, int* iptr) {

	M_Node subRoot;

	if (tknArrPtr[*iptr + 2].type == EQUAL_TO ||
		tknArrPtr[*iptr + 2].type == UNEQUAL_TO ||
		tknArrPtr[*iptr + 2].type == LESS_THAN ||
		tknArrPtr[*iptr + 2].type == GREATER_THAN) 
	{
		subRoot.type = tknArrPtr[*iptr + 2].type;
		subRoot.dataPtr = tknArrPtr[*iptr + 2].dataPtr;

		M_Node subRootA;

		subRootA.type = tknArrPtr[*iptr + 1].type;
		subRootA.dataPtr = tknArrPtr[*iptr + 1].dataPtr;

		M_Node subRootB;

		subRootB.type = tknArrPtr[*iptr + 3].type;
		subRootB.dataPtr = tknArrPtr[*iptr + 3].dataPtr;

		subRoot.A = &subRootA;
		subRoot.B = &subRootB;

		printf("Generated conditional operator of type: %s\n", TokenTypeCast[subRoot.type]);
		printf("A: %s\n", subRoot.A->dataPtr);
		printf("B: %s\n\n", subRoot.B->dataPtr);

		*iptr += 3;
		return subRoot;

	} else {

		printf("Expected conditional statement");
		exit(2);

	}

}

int idx = 0;

M_Node* ASTGenerator(Token* tknArr) {

	while (tknArr[idx].type != FILE_END) {

		switch (tknArr[idx].type) {

			case WHILE:

				printf("WHILE\n");
				break;

			case IF:

				printf("IF\n");
				break;

			case PRINT:

				printf("PRINT\n");
				break;

			case VAR_DEC:

				printf("VAR_DEC\n");
				break;

			case VAR_INIT:

				printf("VAR_INIT\n");
				break;

			case ELSE:

				printf("ELSE\n");
				break;

			case ADD:

				printf("ADD\n");
				break;

			case SUBTRACT: 

				printf("SUB\n");
				break;

			default:

				printf("*\n");

		}

		idx++;


	}
}




