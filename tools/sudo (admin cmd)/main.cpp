#include <iostream>
#include <string>
#include <windows.h>
#include <direct.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <future>
//#define MY_ICON 101

void SudoPrint(int type) {
	
	switch(type) {
		
		case 1: {
		    std::cout << R"(               _                     )" << std::endl;
		    std::cout << R"( ___ _   _  __| | ___   _____  _____ )" << std::endl;
		    std::cout << R"(/ __| | | |/ _` |/ _ \ / _ \ \/ / _ \)" << std::endl;
		    std::cout << R"(\__ | |_| | (_| | (_) |  __/>  |  __/)" << std::endl;
		    std::cout << R"(|___/\__,_|\__,_|\___(_\___/_/\_\___|)" << std::endl;
			
			break;
		}
		
		case 2: {
			std::cout << R"(           _                   )" << std::endl;
			std::cout << R"( ___ _ _ _| |___   ___ _ _ ___ )" << std::endl;
			std::cout << R"(|_ -| | | . | . |_| -_|_'_| -_|)" << std::endl;
			std::cout << R"(|___|___|___|___|_|___|_,_|___|)" << std::endl;
			
			break;
		}
		
		case 3: {
			std::cout << R"(                   __                    )" << std::endl;
			std::cout << R"(   _______  ______/ ____   ___  _  _____ )" << std::endl;
			std::cout << R"(  / ___/ / / / __  / __ \ / _ \| |/_/ _ \)" << std::endl;
			std::cout << R"( (__  / /_/ / /_/ / /_/ _/  ___>  </  __/)" << std::endl;
			std::cout << R"(/____/\__,_/\__,_/\____(_\___/_/|_|\___/ )" << std::endl;
			
			break;
		}
		
		case 4: {
			std::cout << R"(            _                   )" << std::endl;
			std::cout << R"( ____  _ __| |___   _____ _____ )" << std::endl;
			std::cout << R"((_-| || / _` / _ \_/ -_\ \ / -_))" << std::endl;
			std::cout << R"(/__/\_,_\__,_\___(_\___/_\_\___|)" << std::endl;
			
			break;
		}
		
		case 5: {
			std::cout << R"( _    _| _   _   _)" << std::endl;
			std::cout << R"(_\|_|(_|(_)o}_><}_)" << std::endl;
			
			break;
		}
		
		case 6: {
			std::cout << R"(+-+-+-+-+-+-+-+-+)" << std::endl;
			std::cout << R"(|s|u|d|o|.|e|x|e|)" << std::endl;
			std::cout << R"(+-+-+-+-+-+-+-+-+)" << std::endl;
			
			break;
		}
		
		default: {
			std::cout << R"(+-+-+-+-+-+-+-+-+)" << std::endl;
			std::cout << R"(|s|u|d|o|.|e|x|e|)" << std::endl;
			std::cout << R"(+-+-+-+-+-+-+-+-+)" << std::endl;
			
			break;
		}
	}
	
	// Font Name: Ogre
	//                _                     
	//  ___ _   _  __| | ___   _____  _____ 
	// / __| | | |/ _` |/ _ \ / _ \ \/ / _ \
	// \__ | |_| | (_| | (_) |  __/>  |  __/
	// |___/\__,_|\__,_|\___(_\___/_/\_\___|
	//                                      
	// 
	// 
	
	// Font Name: Rectangles
	//            _                   
	//  ___ _ _ _| |___   ___ _ _ ___ 
	// |_ -| | | . | . |_| -_|_'_| -_|
	// |___|___|___|___|_|___|_,_|___|
	//                                
	// 
	// 
	
	// Font Name: Slant
	//                    __                    
	//    _______  ______/ ____   ___  _  _____ 
	//   / ___/ / / / __  / __ \ / _ \| |/_/ _ \
	//  (__  / /_/ / /_/ / /_/ _/  ___>  </  __/
	// /____/\__,_/\__,_/\____(_\___/_/|_|\___/ 
	//                                          
	// 
	// 
	
	// Font Name: Small
	// 
	//              _                   
	//   ____  _ __| |___   _____ _____ 
	//  (_-| || / _` / _ \_/ -_\ \ / -_)
	//  /__/\_,_\__,_\___(_\___/_\_\___|
	//                                  
	// 
	// 
	
	// Font Name: Two Point
	//
	//  _    _| _   _   _
	// _\|_|(_|(_)o}_><}_
	// 
	// 
	
	// Font Name: Digital
	//
	//  +-+-+-+-+-+-+-+-+
	//  |s|u|d|o|.|e|x|e|
	//  +-+-+-+-+-+-+-+-+
	//
}

int main(int argc, char* argv[]) {
	
	//CHNAGE DIR
	//chdir("C:\\Windows\\System32");
	
	bool exit = false;
	
	for(int i = 1; i < argc; i++) {
		
		//run args as a command
		system(argv[i]);
		
		//find exit in args and exit exe
		if (argv[i] == std::string("exit")) {
			exit = true;
		}
	}
	
	if (exit != true) {
		srand(time(0));
		SudoPrint(rand() % 6 + 1);
		std::cout << std::endl;
		DWORD exitcode;
		WinExec("cmd.exe /K", SW_SHOW);
		system("color 07");
	}
	
	return 0;
}




