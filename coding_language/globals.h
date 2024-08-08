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
	UNEQUAL_TO,         // 8
	PRINT,				// 9
	NUMBER,				// 10
	STRING,				// 11
	STATEMENT_END,      // 12
	FILE_END,			// 13
	INVALID             // 14

} TokenType;

static char const* TokenTypeCast[] = {
	
	"VAR_DEC      ",
	"VAR_REF      ",
	"=            ",
	"WHILE        ",
	"COLON        ",
	"<            ",
	">            ",
	"==           ",
	"!=           ",
	"PRINT        ",
	"NUMBER       ",
	"STRING       ",
	"STATEMENT_END",
	"FILE_END     ",
	"INVALID      "
};

typedef struct {

	TokenType type;
	char* dataPtr;

} Token;

#endif 
