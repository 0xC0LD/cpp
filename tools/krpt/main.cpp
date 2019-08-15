#include <fstream>
#include <limits>
#include <windows.h> //SLEEP()
#include <iostream>
#include <string>
#include <stdio.h>  // printf, scanf, puts, NULL
#include <stdlib.h> // srand, rand
#include <time.h>   // time

//GET RANDOM NUMBER
int randNumGen(int max) {
	srand(time(NULL)); //initialize random seed
	return rand() % max + 1; //[1, max]
}

//WRITE TO FILE
int writeToFile(std::string filename, int lineNo, std::string toWrite) {
	std::fstream file(filename);
	if (!file) { return 1; }
	int currentLine = 0;
	while (currentLine < lineNo) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		++currentLine;
	}
	file.seekp(file.tellg());
	file << toWrite << std::endl;
	return 0;
}

int main(int argc, char* argv[]){
	
	if (argc == 1){ std::cout << "USAGE: " << argv[0] << " <file>"; return 1; }
	
	const std::string KEY = "!()#U@!J2n1k12312312"; //KEY (DON'T USE A LONG KEY, IT MAKES THE (IMAGE) FILE UNREADABLE)
	int line;
	
	for (int count = 1; count < argc; ++count) {
		
		line = randNumGen(5);
		std::cout << "line: "  << line << std::endl;
		writeToFile(argv[count], line, KEY);
	}
	
	return 0;
}