#include <iostream>
#include "md5.h"

int main(int argc, char* argv[]){
	if (argc == 1)  { std::cout << "USAGE: " << argv[0] << " <text>" << std::endl; return 1; }
	for (int i = 1; i < argc; i++) { std::cout << md5(argv[i]) << std::endl; }
    return 0;
}