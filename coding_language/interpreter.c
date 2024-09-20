#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "interpreter.h"

varData** variables = NULL;
int variableCounter = 0;
bool subLoopActive = false;
bool returnNodeActive = false;
bool ifElseLoop = false;
bool ifFailed = false;

M_Node** returnNodeArray = NULL;
int returnNodeCounter = 0;

varData* GetVariableData(char* varName) {

	varData* varData = malloc(sizeof(varData));

	for (int i = 0; i < variableCounter; i++) {

		if (strcmp(varName, variables[i]->name) == 0) {

			varData->name = variables[i]->name;
			varData->type = variables[i]->type;
			varData->data = variables[i]->data;

		}
	}

	return varData;
}

void AddReturnNode(M_Node* currentNodePtr) {

	returnNodeCounter++;

	M_Node** tempRetNodeArray = realloc(returnNodeArray, sizeof(M_Node*) * returnNodeCounter);

	tempRetNodeArray[returnNodeCounter - 1] = currentNodePtr;

	if (tempRetNodeArray == NULL) {

		printf("Failed to allocate memory for return node");
		exit(1);

	}

	returnNodeArray = tempRetNodeArray;

}

void AddVariable(varData* newVar) {

	variableCounter++;

	varData** tempArray = realloc(variables, sizeof(varData*) * variableCounter);

	if (tempArray == NULL) {

		printf("Failed to allocate memory for new variable reference");
		exit(1);

	}

	tempArray[variableCounter - 1] = newVar;

	variables = tempArray;

}

void RunAST(M_Node* rootNode) {

	M_Node* focusNode = rootNode;

	while (focusNode->type != FILE_END) {

		switch (focusNode->type) {

		case VAR_DEC: 
		{
			varData* newVar = malloc(sizeof(varData));

			newVar->name = focusNode->A->dataPtr;

			AddVariable(newVar);

		} break;

		case VAR_INIT:
		{
			for (int i = 0; i < variableCounter; i++) {

				if (strcmp(variables[i]->name, focusNode->A->dataPtr) == 0) {

					variables[i]->type = focusNode->B->type;
					variables[i]->data = focusNode->B->dataPtr;

				}
			}

		} break;

		case WHILE:
		{
			TokenType condType = focusNode->A->type;
			
			M_Node* A = focusNode->A->A;
			M_Node* B = focusNode->A->B;

			float ValA, ValB;

			if (A->type == VAR_REF) {

				varData* varData = GetVariableData(A->dataPtr);

				ValA = atof(varData->data);

			} else {

				ValA = atof(focusNode->A->A->dataPtr);

			}

			if (B->type == VAR_REF) {

				varData* varData = GetVariableData(B->dataPtr);

				ValB = atof(varData->data);

			} else {

				ValB = atof(focusNode->A->B->dataPtr);

			}

			switch (condType) {

			case LESS_THAN:

				if (ValA < ValB) {

					subLoopActive = true;
					AddReturnNode(focusNode);

				} break;

			case GREATER_THAN:

				if (ValA > ValB) {

					subLoopActive = true;
					AddReturnNode(focusNode);

				} break;

			case EQUAL_TO:

				if (ValA == ValB) {

					subLoopActive = true;
					AddReturnNode(focusNode);

				} break;

			case UNEQUAL_TO:

				if (ValA != ValB) {

					subLoopActive = true;
					AddReturnNode(focusNode);

				} break;
			}

		} break;

		case IF:  
		{
			TokenType condType = focusNode->A->type;

			M_Node* A = focusNode->A->A;
			M_Node* B = focusNode->A->B;

			float ValA, ValB;

			if (A->type == VAR_REF) {

				varData* varData = GetVariableData(A->dataPtr);

				ValA = atof(varData->data);

			} else {

				ValA = atof(focusNode->A->A->dataPtr);

			}

			if (B->type == VAR_REF) {

				varData* varData = GetVariableData(B->dataPtr);

				ValB = atof(varData->data);

			} else {

				ValB = atof(focusNode->A->B->dataPtr);

			}

			switch (condType) {

			case LESS_THAN:

				if (ValA < ValB) {

					subLoopActive = true;
					ifElseLoop = true;
					AddReturnNode(focusNode);

				} break;

			case GREATER_THAN:

				if (ValA > ValB) {

					subLoopActive = true;
					ifElseLoop = true;
					AddReturnNode(focusNode);

				} break;

			case EQUAL_TO:

				if (ValA == ValB) {

					subLoopActive = true;
					ifElseLoop = true;
					AddReturnNode(focusNode);

				} break;

			case UNEQUAL_TO:

				if (ValA != ValB) {

					subLoopActive = true;
					ifElseLoop = true;
					AddReturnNode(focusNode);

				} break;
			}
		
		} break;

		case ELSE:
		{
			if (ifFailed) {

				subLoopActive = true;
				ifElseLoop = true;
				AddReturnNode(focusNode);

				ifFailed = false;

			}
		}

		case STATEMENT_END:
		{
			returnNodeActive = true;

		} break;

		case PRINT:
		{
			if (focusNode->A->type == VAR_REF) {

				varData* varData = GetVariableData(focusNode->A->dataPtr);

				printf("OUT: %s\n", varData->data);

			} else {

				printf("OUT: %s\n", focusNode->A->dataPtr);

			}

		} break;

		case SUBTRACT:
		{
			float ValA, ValB;

			if (focusNode->A->type == VAR_REF) {

				varData* varData = GetVariableData(focusNode->A->dataPtr);

				ValA = atof(varData->data);
				

			} else {

				ValA = atof(focusNode->A->dataPtr);

			}

			for (int i = 0; i < variableCounter; i++) {

				if (strcmp(focusNode->B->dataPtr, variables[i]->name) == 0) {

					ValB = atof(variables[i]->data);

					float difference = ValB - ValA;

					char* updatedData = malloc(sizeof(char) * 32);

					sprintf(updatedData, "%f", difference);

					variables[i]->data = updatedData;

				}
			}

		} break;

		case ADD:
		{
			float ValA, ValB;

			if (focusNode->B->type == VAR_REF) {

				varData* varData = GetVariableData(focusNode->B->dataPtr);

				ValB = atof(varData->data);


			} else {

				ValB = atof(focusNode->B->dataPtr);

			}

			for (int i = 0; i < variableCounter; i++) {

				if (strcmp(focusNode->A->dataPtr, variables[i]->name) == 0) {

					ValA = atof(variables[i]->data);

					float difference = ValB + ValA;

					char* updatedData = malloc(sizeof(char) * 32);

					sprintf(updatedData, "%f", difference);

					variables[i]->data = updatedData;

				}
			}

		} break;

		}

		if (subLoopActive) {

			focusNode = focusNode->B;
			subLoopActive = false;

		} else if (returnNodeActive == true && !ifElseLoop) {

			focusNode = returnNodeArray[returnNodeCounter - 1];
			returnNodeActive = false;

			returnNodeCounter--;

		} else if (returnNodeActive && ifElseLoop) {

			focusNode = returnNodeArray[returnNodeCounter - 1]->next;
			returnNodeActive = false;
			ifElseLoop = false;

			returnNodeCounter--;

		} else {

			focusNode = focusNode->next;

		}
	}
}






