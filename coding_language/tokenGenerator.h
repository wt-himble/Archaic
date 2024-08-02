#ifndef TOKEN_GEN_H
#define TOKEN_GEN_H

#include <stdbool.h>

#include "globals.h"

void tokenGenerator(char* srcPtr, char* tknArrPtr);
bool isVarDef(char* strPtr, int strIdx);


#endif

