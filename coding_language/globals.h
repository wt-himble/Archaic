#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum {

	VAR_DEC,
	VAR_REF,
	VAR_INIT,
	WHILE,
	COLON,
	LESS_THAN,
	PRINT,
	NUMBER,
	STRING,
	END

} TokenType;

typedef struct {

	TokenType type;
	char* dataPtr;

} Token;

#endif 
