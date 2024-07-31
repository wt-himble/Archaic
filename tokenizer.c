#include <stdio.h>

int main() {

	FILE *f;

	f = fopen("example_source.txt", "r");

	char string[100];

	fgets(string, 100, f);

	printf("%s", string);
	
}