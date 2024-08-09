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

		*iptr += 3;
		return subRoot;

	} else {

		printf("Expected conditional statement");
		exit(2);

	}
}

void addReturnNode(M_Node returnNode, M_Node** returnArray) {

	M_Node** tempReturnArray = realloc(returnArray, sizeof(M_Node*) * numOfReturnNodes);

	if (tempReturnArray == NULL) {

		printf("ERROR. FAILED TO REALLOCATE MEMORY");
		exit(1);

	}

	tempReturnArray[numOfReturnNodes - 1] = &returnNode;
	returnArray = tempReturnArray;

}


M_Node* ASTGenerator(Token* tknArrPtr) {

	M_Node* root;
	M_Node** returnNodeArray = NULL;
	
	int idx = 0;

	while (tknArrPtr[idx].type != FILE_END) {

		M_Node newNode;

		if (tknArrPtr[idx].type == WHILE) {

			M_Node newNode;
			newNode.type = WHILE;
			newNode.dataPtr = tknArrPtr[idx].dataPtr;

			M_Node condSubTree = createCondSubTree(tknArrPtr, &idx);

			newNode.A = &condSubTree;

			numOfReturnNodes++;

			addReturnNode(newNode, returnNodeArray);
	
		}

		idx++;

	}
}


