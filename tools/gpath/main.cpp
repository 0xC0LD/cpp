#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	
	char* str = getenv("PATH");
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ';') {
			str[i] = '\n';
		}
	}
	
	printf(str);
	
	return 0;
}
