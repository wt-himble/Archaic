#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum {

	VAR_DEC,		// 0
	VAR_REF,		// 1
	VAR_INIT,		// 2			
	WHILE,			// 3
	COLON,			// 4
	LESS_THAN, 		// 5
	PRINT,			// 6
	NUMBER,			// 7
	STRING,			// 8
	END				// 9

} TokenType;

static char const* TokenTypeCast[] = {"VAR_DEC",
								      "VAR_REF",
							          "EQUALS ",
							          "WHILE  ",
							          "COLON  ",
							          "LESS_THAN",
							          "PRINT  ",
							          "NUMBER ",
							          "STRING ",
							          "END"
};

typedef struct {

	TokenType type;
	char* dataPtr;

} Token;

#endif 
