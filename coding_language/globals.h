#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum {

	VAR_DEC,			// 0
	VAR_REF,			// 1
	VAR_INIT,			// 2			
	WHILE,				// 3
	COLON,				// 4
	LESS_THAN, 			// 5
	GREATER_THAN,		// 6
	EQUAL_TO,           // 7
	PRINT,				// 8
	NUMBER,				// 9
	STRING,				// 10
	STATEMENT_END,      // 11
	FILE_END,			// 12
	INVALID             // 13

} TokenType;

static char const* TokenTypeCast[] = {
	
	"VAR_DEC",
	"VAR_REF",
	"VAR_INIT",
	"WHILE",
	"COLON",
	"LESS_THAN",
	"GREATER_THAN",
	"EQUAL_TO",
	"PRINT",
	"NUMBER",
	"STRING",
	"STATEMENT_END",
	"FILE_END",
	"INVALID"
};

typedef struct {

	TokenType type;
	char* dataPtr;

} Token;

#endif 
