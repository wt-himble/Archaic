#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum {

	VAR_DEC,
	STRING_INIT,
	INT_INIT,
	WHILE

} TokenType;

typedef struct {

	TokenType type;
	char* dataPtr;

} Token;

#endif 
