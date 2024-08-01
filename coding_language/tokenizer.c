#include <stdio.h>
#include "globals.h"

int main() {

	printf("Initializing program...");

	FILE *f;

	f = fopen("test_source.txt", "r");

	if (f == NULL) {

		printf("\nFile failed to open.");

	}
}