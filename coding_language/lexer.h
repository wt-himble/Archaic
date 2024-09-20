#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

#include "globals.h"

void tokenGenerator(char* srcPtr, Token** tknArrPtr);

#endif

