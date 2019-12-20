#include <iostream>
#include <windows.h>
#include <fstream>
#include "res.h"

// save file to disk from resource
int main(int argc, char* argv[]){
	HRSRC myResource = FindResource(NULL, MAKEINTRESOURCE(IDR_RCDATA1), RT_RCDATA);
	unsigned int myResourceSize = SizeofResource(NULL, myResource);
	HGLOBAL myResourceData = LoadResource(NULL, myResource);
	void* pMyExecutable = LockResource(myResourceData);
	std::ofstream f("file.txt", std::ios::out | std::ios::binary);
	f.write((char*)pMyExecutable, myResourceSize);
	f.close();
	return 0;
}
