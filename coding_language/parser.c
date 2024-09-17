#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "globals.h"
#include "parser.h"

int numOfReturnNodes = 0;

int idx = 0;

M_Node* CondSubTreeGenerator(Token TokOp, Token TokA, Token TokB) {

	M_Node Op, A, B;

	Op.type = TokOp.type;
	Op.dataPtr = TokOp.dataPtr;

	A.type = TokA.type;
	A.dataPtr = TokA.dataPtr;

	B.type = TokB.type;
	B.dataPtr = TokB.dataPtr;

	Op.A = &A;
	Op.B = &B;

	return &Op;

}

M_Node* ASTGenerator(Token* tknArr) {

	M_Node* rootNode = NULL;
	M_Node* prevNodePtr = NULL;

	while (tknArr[idx].type != FILE_END) {

		M_Node currentNode;
		
		switch (tknArr[idx].type) {

		case WHILE:

		{
			currentNode.type = WHILE;
			currentNode.dataPtr = tknArr[idx].dataPtr;

			currentNode.A = CondSubTreeGenerator(tknArr[idx + 2], tknArr[idx + 1], tknArr[idx + 3]);

			idx += 3;

		} break;

		case IF:

		{
			currentNode.type = IF;
			currentNode.dataPtr = tknArr[idx].dataPtr;

			currentNode.A = CondSubTreeGenerator(tknArr[idx + 2], tknArr[idx + 1], tknArr[idx + 3]);

			idx += 3;

		} break;

		case PRINT:

		{
			currentNode.type = PRINT;
			currentNode.dataPtr = tknArr[idx].dataPtr;

			M_Node printNode;

			printNode.type = tknArr[idx + 1].type;
			printNode.dataPtr = tknArr[idx + 1].dataPtr;

			currentNode.A = &printNode;

			idx++;

		} break;

		case VAR_DEC:

		{
			currentNode.type = VAR_DEC;
			currentNode.dataPtr = tknArr[idx].dataPtr;

			M_Node varRef;

			varRef.type = tknArr[idx + 1].type;
			varRef.dataPtr = tknArr[idx + 1].dataPtr;

			currentNode.A = &varRef;

			idx++;

		} break;

		case VAR_INIT:

		{
			currentNode.type = VAR_INIT;
			currentNode.dataPtr = tknArr[idx].dataPtr;

			M_Node varRef, varVal;

			varRef.type = tknArr[idx + 1].type;
			varRef.dataPtr = tknArr[idx + 1].dataPtr;

			varVal.type = tknArr[idx + 2].type;
			varVal.dataPtr = tknArr[idx + 2].dataPtr;

			currentNode.A = &varRef;
			currentNode.B = &varVal;

			idx+=2;


		} break;

		case ELSE:

		{
			currentNode.type = ELSE;
			currentNode.dataPtr = tknArr[idx].dataPtr;

		} break;

		case ADD:

		{
			currentNode.type = ADD;
			currentNode.dataPtr = tknArr[idx].dataPtr;

			M_Node valA, valB;

			valA.type = tknArr[idx + 1].type;
			valA.dataPtr = tknArr[idx + 1].dataPtr;

			valB.type = tknArr[idx + 2].type;
			valB.dataPtr = tknArr[idx + 2].dataPtr;

			currentNode.A = &valA;
			currentNode.B = &valB;

			idx += 2;

		} break;

		case SUBTRACT:

		{
			currentNode.type = SUBTRACT;
			currentNode.dataPtr = tknArr[idx].dataPtr;

			M_Node valA, valB;

			valA.type = tknArr[idx + 1].type;
			valA.dataPtr = tknArr[idx + 1].dataPtr;

			valB.type = tknArr[idx + 2].type;
			valB.dataPtr = tknArr[idx + 2].dataPtr;

			currentNode.A = &valA;
			currentNode.B = &valB;

			idx += 2;

		} break;

		case STATEMENT_END:

		{
			currentNode.type = STATEMENT_END;
			currentNode.dataPtr = tknArr[idx].dataPtr;

		} break;

		}

		if (rootNode == NULL) {

			rootNode = &currentNode;
			prevNodePtr = &currentNode;

		} else {

			printf("%s\n", TokenTypeCast[currentNode.type]);

			prevNodePtr->next = &currentNode;
			prevNodePtr = &currentNode;

		}

		idx++;


	}
}




