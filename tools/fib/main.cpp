#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	if (argc == 1) { fprintf(stderr, "USAGE: %s <number>\n", argv[0]); return 1; }
	
	long long int n, t1 = 0, t2 = 1, nextTerm = 0;
	n = atoi(argv[1]);
	
	for (long long int i = 1; i <= n; ++i) {
		nextTerm = t1 + t2;
		t1 = t2;
		t2 = nextTerm;
		printf("%lli\n", nextTerm);
	}
	
	return 0;
}