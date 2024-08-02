#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum {

	VAR_PREC,
	VAR_DEC

} TokenType;

typedef struct {

	TokenType type;
	char* dataPtr;

} Token;

#endif 
