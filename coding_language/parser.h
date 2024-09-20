#ifndef PARSER_H
#define PARSER_H

#include "globals.h"

// The M_NODE is the main structure used during the AST generation
// It gets its name from the M shape created by its three branches 
// coming from a source of data

typedef struct node_struct{

	TokenType type;
	char* dataPtr;

	struct node_struct* next;
	struct node_struct* A;
	struct node_struct* B;

} M_Node;

M_Node* ASTGenerator(Token* tknArr);

#endif
