#ifndef INFERENCE
#define INFERENCE

#include "parser.h";

typedef struct varStruct {

	char* name;
	TokenType type;
	char* data;

} varData;

void RunAST(M_Node* rootNode);

#endif INFERENCE