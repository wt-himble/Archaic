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

	while (tknArr[idx].type != FILE_END) {

		M_Node currentNode;
		M_Node* nextNodePtr = NULL;
		bool subLoop = false;

		switch (tknArr[idx].type) {

		case WHILE:

		{
			currentNode.type = WHILE;
			currentNode.dataPtr = tknArr[idx].dataPtr;

			currentNode.A = CondSubTreeGenerator(tknArr[idx + 2], tknArr[idx + 1], tknArr[idx + 3]);

			subLoop = true;

		} break;


		case IF:

		{
			currentNode.type = IF;
			currentNode.dataPtr = tknArr[idx].dataPtr;

			currentNode.A = CondSubTreeGenerator(tknArr[idx + 2], tknArr[idx + 1], tknArr[idx + 3]);

			subLoop = true;

		} break;

			case PRINT:





				break;

			case VAR_DEC:

				
				break;

			case VAR_INIT:

			
				break;

			case ELSE:

			
				break;

			case ADD:

				break;

			case SUBTRACT: 

			
				break;

		}

		if (subLoop) {

			nextNodePtr = currentNode.B;

		} else {

			nextNodePtr = currentNode.next;

		}

		idx++;


	}
}




