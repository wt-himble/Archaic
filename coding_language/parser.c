#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "globals.h"
#include "parser.h"

int idx = 0;

M_Node** retNodes = NULL;
int retNodeCounter = 0;
bool retNodeCheck = false;
bool subLoop = false;
bool statementEnd = false;
bool retNodeActive = false;
bool fileEnd = false;

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

void AddRetNode(M_Node* currentNodePtr) {

	retNodeCounter++;
	//printf("Added return node. Number of return nodes is now: %d\n", retNodeCounter);

	M_Node** tempRetNodeArray = realloc(retNodes, sizeof(M_Node*) * retNodeCounter);

	tempRetNodeArray[retNodeCounter - 1] = currentNodePtr;

	if (tempRetNodeArray == NULL) {

		printf("Failed to allocate memory for return node");
		exit(1);

	}

	retNodes = tempRetNodeArray;

}

M_Node* ASTGenerator(Token* tknArr) {

	M_Node* rootNode = NULL;
	M_Node* prevNodePtr = NULL;

	while (true) {

		M_Node* currentNode = malloc(sizeof(M_Node));

		switch (tknArr[idx].type) {

		case WHILE:

		{
			currentNode->type = WHILE;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			currentNode->A = CondSubTreeGenerator(tknArr[idx + 2], tknArr[idx + 1], tknArr[idx + 3]);

			retNodeCheck = true;

			idx += 3;

		} break;

		case IF:

		{
			currentNode->type = IF;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			currentNode->A = CondSubTreeGenerator(tknArr[idx + 2], tknArr[idx + 1], tknArr[idx + 3]);

			retNodeCheck = true;

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

			retNodeCheck = true;

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

			statementEnd = true;

		} break;

		case FILE_END:

		{
			currentNode->type = FILE_END;
			currentNode->dataPtr = tknArr[idx].dataPtr;

			fileEnd = true;
		}

		}

		if (retNodeActive) {

			prevNodePtr = retNodes[retNodeCounter - 1];

			//printf("Return node activated. Returning to node of type %s\n", TokenTypeCast[prevNodePtr->type]);

			retNodeCounter--;

			//printf("Removed return node. Number of return nodes is now %d\n", retNodeCounter);

			retNodeActive = false;

		}

		if (rootNode == NULL) {

			rootNode = currentNode;
			prevNodePtr = currentNode;

		} else if (subLoop == true) {

			prevNodePtr->B = currentNode;
			prevNodePtr = currentNode;
			subLoop = false;

		} else {

			prevNodePtr->next = currentNode;
			prevNodePtr = currentNode;

		}

		if (retNodeCheck) {

			retNodeCheck = false;
			AddRetNode(currentNode);

			subLoop = true;

		}

		if (statementEnd) {

			statementEnd = false;

			retNodeActive = true;

		}

		if (fileEnd) {

			break;


		} else {

			idx++;

		}
	}

	return rootNode;
}

	




