#include <iostream>
#include <stdlib.h>

int main() {
	
	std::string str = getenv("PATH");
	std::string split;
	
	for (char& c : str) {
		if (c == ';') {
			std::cout << split << std::endl;
			split = "";
		}
		else {
			split = split + c;
		}
	}
	
	return 0;
}
