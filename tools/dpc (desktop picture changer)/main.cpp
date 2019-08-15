#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <sstream>

int main(int argc, char* argv[]){
	
	if (argc == 1) { std::cerr << "USAGE: dpc.exe <filename.jpg/jpeg/png/...>"; return 1; }
	
	char* path = argv[1];
	
	//SET IMAGE
	if ((SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, path, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE)) == 0){
		
		std::cout << "ERROR: failed to set image \"" << path << "\" as desktop background..." << std::endl;
		
		return 1;
	}
	
	std::cout << "SUCCESS: the image \"" << path << "\" has been set as background!" << std::endl;
	
	return 0;
}

