#ifndef PARSER_H
#define PARSER_H

#include "globals.h"

typedef struct node_struct{

	TokenType type;
	char* dataPtr;

	struct node_struct* next;
	struct node_struct* A;
	struct node_struct* B;

} M_Node;

M_Node* ASTGenerator(Token* tknArr);

M_Node createCondSubTree(Token* tknArrPtr, int* iptr);

#endif
