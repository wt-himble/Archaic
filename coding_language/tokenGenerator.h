#ifndef TOKEN_GEN_H
#define TOKEN_GEN_H

#include <stdbool.h>

#include "globals.h"

void tokenGenerator(char* srcPtr, Token** tknArrPtr);

bool varDecCheck(char** tempTknArr, int* iptr);
bool varInitCheck(char** tempTknArr, int* iptr);
bool printCheck(char** tempTknArr, int* iptr);
bool isNumber(char* str);

TokenType valueChecker(char** tempTknArr, int* iptr);

#endif

