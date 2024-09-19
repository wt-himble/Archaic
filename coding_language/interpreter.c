#include <stdlib.h>

#include "interpreter.h"

void RunAST(M_Node* rootNode) {

	printf("%s\n", TokenTypeCast[rootNode->type]);
	printf("%s\n", TokenTypeCast[rootNode->next->type]);

}






