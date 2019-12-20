#include <stdio.h>
#include "md5.h"

int main(int argc, char* argv[]){
	if (argc == 1)  { fprintf(stderr, "USAGE: %s <text>", argv[0]); return 1; }
	for (int i = 1; i < argc; i++) { printf("%s\n", md5(argv[i]).c_str()); }
    return 0;
}