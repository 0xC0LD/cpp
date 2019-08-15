#include <iostream>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	if (argc == 1) { std::cerr << "USAGE: " << argv[0] << " <number>" << std::endl; return 1; }
	
	long long int n, t1 = 0, t2 = 1, nextTerm = 0;
	
	n = atoi(argv[1]);
	
	for (long long int i = 1; i <= n; ++i) {
		nextTerm = t1 + t2;
		t1 = t2;
		t2 = nextTerm;
		std::cout << nextTerm << std::endl;
	}
	
	return 0;
}