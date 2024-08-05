#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum {

	VAR_DEC,
	VAR_REF,
	WHILE,
	DO,
	LESS_THAN,
	INT


} TokenType;

typedef struct {

	TokenType type;
	char* dataPtr;

} Token;

#endif 
