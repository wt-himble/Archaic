#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum {

	VAR_DEC,			// 0
	VAR_REF,			// 1
	VAR_INIT,			// 2			
	WHILE,				// 3
	IF,                 // 4
	ELSE,               // 5
	COLON,				// 6
	LESS_THAN, 			// 7
	GREATER_THAN,		// 8
	EQUAL_TO,           // 9
	UNEQUAL_TO,         // 10
	PRINT,				// 11
	NUMBER,				// 12
	STRING,				// 13
	STATEMENT_END,      // 14
	FILE_END,			// 15
	INVALID,            // 16
	ADD,                // 17
	SUBTRACT            // 18

} TokenType;

static char const* TokenTypeCast[] = {
	
	"VAR_DEC      ",
	"VAR_REF      ",
	"VAR_INIT     ",
	"WHILE        ",
	"IF           ",
	"ELSE         ",
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
	"INVALID      ",
	"ADD          ",
	"SUBTRACT     "
};

typedef struct {

	TokenType type;
	char* dataPtr;

} Token;

#endif 
