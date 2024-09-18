#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "globals.h"
#include "parser.h"

int numOfReturnNodes = 0;

int idx = 0;

M_Node* CondSubTreeGenerator(Token TokOp, Token TokA, Token TokB) {

	M_Node* Op = malloc(sizeof(M_Node));
	M_Node* A = malloc(sizeof(M_Node));
	M_Node* B = malloc(sizeof(M_Node));

	Op->type = TokOp.type;
	Op->dataPtr = TokOp.dataPtr;

	A->type = TokA.type;
	A->dataPtr = TokA.dataPtr;

	B->type = TokB.type;
	B->dataPtr = TokB.dataPtr;

	Op->A = A;
	Op->B = B;

	return Op;

}

M_Node* ASTGenerator(Token* tknArr) {

	M_Node* rootNode = NULL;
	M_Node* prevNodePtr = NULL;

	while (tknArr[idx].type != FILE_END) {

		M_Node* currentNode = malloc(sizeof(M_Node));

		switch (tknArr[idx].type) {

		case WHILE:

		{
			currentNode->type = WHILE;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			currentNode->A = CondSubTreeGenerator(tknArr[idx + 2], tknArr[idx + 1], tknArr[idx + 3]);

			idx += 3;

		} break;

		case IF:

		{
			currentNode->type = IF;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			currentNode->A = CondSubTreeGenerator(tknArr[idx + 2], tknArr[idx + 1], tknArr[idx + 3]);

			idx += 3;

		} break;

		case PRINT:

		{
			currentNode->type = PRINT;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			M_Node* printNode = malloc(sizeof(M_Node));

			printNode->type = tknArr[idx + 1].type;
			printNode->dataPtr = tknArr[idx + 1].dataPtr;

			currentNode->A = printNode;

			idx++;

		} break;

		case VAR_DEC:

		{
			currentNode->type = VAR_DEC;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			M_Node* varRef = malloc(sizeof(M_Node));

			varRef->type = tknArr[idx + 1].type;
			varRef->dataPtr = tknArr[idx + 1].dataPtr;

			currentNode->A = varRef;

			idx++;

		} break;

		case VAR_INIT:

		{
			currentNode->type = VAR_INIT;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			M_Node* varRef = malloc(sizeof(M_Node));
			M_Node* varVal = malloc(sizeof(M_Node));

			varRef->type = tknArr[idx + 1].type;
			varRef->dataPtr = tknArr[idx + 1].dataPtr;

			varVal->type = tknArr[idx + 2].type;
			varVal->dataPtr = tknArr[idx + 2].dataPtr;

			currentNode->A = varRef;
			currentNode->B = varVal;

			idx += 2;


		} break;

		case ELSE:

		{
			currentNode->type = ELSE;
			currentNode->dataPtr = tknArr[idx].dataPtr;

		} break;

		case ADD:

		{
			currentNode->type = ADD;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			M_Node* valA = malloc(sizeof(M_Node));
			M_Node* valB = malloc(sizeof(M_Node));

			valA->type = tknArr[idx + 1].type;
			valA->dataPtr = tknArr[idx + 1].dataPtr;

			valB->type = tknArr[idx + 2].type;
			valB->dataPtr = tknArr[idx + 2].dataPtr;

			currentNode->A = valA;
			currentNode->B = valB;

			idx += 2;

		} break;

		case SUBTRACT:

		{
			currentNode->type = SUBTRACT;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			M_Node* valA = malloc(sizeof(M_Node));
			M_Node* valB = malloc(sizeof(M_Node));

			valA->type = tknArr[idx + 1].type;
			valA->dataPtr = tknArr[idx + 1].dataPtr;

			valB->type = tknArr[idx + 2].type;
			valB->dataPtr = tknArr[idx + 2].dataPtr;

			currentNode->A = valA;
			currentNode->B = valB;

			idx += 2;

		} break;

		case STATEMENT_END:

		{
			currentNode->type = STATEMENT_END;
			currentNode->dataPtr = tknArr[idx].dataPtr;

		} break;

		}

		if (rootNode == NULL) {

			rootNode = currentNode;
			prevNodePtr = currentNode;

		} else {

			prevNodePtr->next = currentNode;
			prevNodePtr = currentNode;

		}

		idx++;

	}

	M_Node* fileEnd = malloc(sizeof(M_Node));
	fileEnd->type = FILE_END;

	// Generates the end of the file. This M_Node will be used during inference to determine if the end of the file has been reached. 

	if (prevNodePtr) {

		prevNodePtr->next = fileEnd;

		printf("End of file generated...\n");
		printf("Final M_Node is of type %s\n", TokenTypeCast[prevNodePtr->type]);

	} else {

		printf("End of file expected");

	}

	M_Node* focusNode = rootNode;

	printf("\nOperations as they are linked:\n\n");
	
	while (focusNode->type != FILE_END) {

		printf("%s ", TokenTypeCast[focusNode->type]);
		printf("The next M_Node is: \n");

		focusNode = focusNode->next;

	}


}

	




