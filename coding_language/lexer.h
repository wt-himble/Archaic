#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

#include "globals.h"

void tokenGenerator(char* srcPtr, Token** tknArrPtr);
void addToken(Token** tknArrPtr, TokenType typeIn, char* dataPtrIn);

bool varDecCheck(char** tempTknArr, int* iptr);
bool varInitCheck(char** tempTknArr, int* iptr);
bool printCheck(char** tempTknArr, int* iptr);
bool endStatementCheck(char** tempTknArr, int* iptr);
bool addCheck(char** tempTknArr, int* iptr);
bool subtractCheck(char** tempTknArr, int* iptr);
bool containsLetter(char* str);

TokenType equalityStatementCheck(char** tempTknArr, int* iptr);
TokenType valueChecker(char** tempTknArr, int* iptr);

#endif

