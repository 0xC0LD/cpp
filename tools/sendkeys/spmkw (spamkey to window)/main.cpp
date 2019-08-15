#include <iostream>
#include <string>
#include <windows.h>
#include "SendKeys.h"
#include <stdlib.h>
#include <thread>

bool g_Exit = false;
void endSpam() {
	
	while(g_Exit == false) {
		Sleep(50);
		
		if (GetAsyncKeyState(81) != 0) {
			std::cout << "# 'q' pressed exiting..." << std::endl;
			g_Exit = true;
			break;
		}
	}
	
	exit(0);
}

int main(int argc, char *argv[]) {
	
	if (argc < 4) {
		std::cout << std::endl;
		std::cout << "USAGE: " << argv[0] << " <delay (ms)> <window name> <string to spam>" << std::endl;
		std::cout << std::endl;
		std::cout << "=========================================================" << std::endl;
		std::cout << "| KEY               | CODE                              |" << std::endl;
		std::cout << "|===================+===================================|" << std::endl;
		std::cout << "| ESC               | {ESC}                             |" << std::endl;
		std::cout << "| ENTER             | {ENTER} or ~                      |" << std::endl;
		std::cout << "| BACKSPACE         | {BACKSPACE}, {BS}, or {BKSP}      |" << std::endl;
		std::cout << "| PRINT SCREEN      | {PRTSC} (reserved for future use) |" << std::endl;
		std::cout << "| BREAK             | {BREAK}                           |" << std::endl;
		std::cout << "| HELP              | {HELP}                            |" << std::endl;
		std::cout << "| INS or INSERT     | {INS}                             |" << std::endl;
		std::cout << "| DEL or DELETE     | {DELETE} or {DEL}                 |" << std::endl;
		std::cout << "| HOME              | {HOME}                            |" << std::endl;
		std::cout << "| END               | {END}                             |" << std::endl;
		std::cout << "| PAGE DOWN         | {PGDN}                            |" << std::endl;
		std::cout << "| PAGE UP           | {PGUP}                            |" << std::endl;
		std::cout << "| SCROLL LOCK       | {SCROLL}                          |" << std::endl;
		std::cout << "| CAPS LOCK         | {CAPSLOCK}                        |" << std::endl;
		std::cout << "| NUM LOCK          | {NUMLOCK}                         |" << std::endl;
		std::cout << "| UP ARROW          | {UP}                              |" << std::endl;
		std::cout << "| DOWN ARROW        | {DOWN}                            |" << std::endl;
		std::cout << "| RIGHT ARROW       | {RIGHT}                           |" << std::endl;
		std::cout << "| LEFT ARROW        | {LEFT}                            |" << std::endl;
		std::cout << "| ^                 | {CARET}                           |" << std::endl;
		std::cout << "| ~                 | {TILDE}                           |" << std::endl;
		std::cout << "| { }               | {LEFTBRACE} {RIGHTBRACE}          |" << std::endl;
		std::cout << "| ( )               | {LEFTPAREN} {RIGHTPAREN}          |" << std::endl;
		std::cout << "| Left/Right WINKEY | {LWIN} {RWIN}                     |" << std::endl;
		std::cout << "| WINKEY            | {WIN} equivalent to {LWIN}        |" << std::endl;
		std::cout << "| WINKEY            | @                                 |" << std::endl;
		std::cout << "| TAB               | {TAB}                             |" << std::endl;
		std::cout << "| SHIFT             | +                                 |" << std::endl;
		std::cout << "| CTRL              | ^                                 |" << std::endl;
		std::cout << "| ALT               | %                                 |" << std::endl;
		std::cout << "| F1                | {F1}                              |" << std::endl;
		std::cout << "| F2                | {F2}                              |" << std::endl;
		std::cout << "| F3                | {F3}                              |" << std::endl;
		std::cout << "| F4                | {F4}                              |" << std::endl;
		std::cout << "| F5                | {F5}                              |" << std::endl;
		std::cout << "| F6                | {F6}                              |" << std::endl;
		std::cout << "| F7                | {F7}                              |" << std::endl;
		std::cout << "| F8                | {F8}                              |" << std::endl;
		std::cout << "| F9                | {F9}                              |" << std::endl;
		std::cout << "| F10               | {F10}                             |" << std::endl;
		std::cout << "| F11               | {F11}                             |" << std::endl;
		std::cout << "| F12               | {F12}                             |" << std::endl;
		std::cout << "| F13               | {F13}                             |" << std::endl;
		std::cout << "| F14               | {F14}                             |" << std::endl;
		std::cout << "| F15               | {F15}                             |" << std::endl;
		std::cout << "| F16               | {F16}                             |" << std::endl;
		std::cout << "| Keypad add        | {ADD}                             |" << std::endl;
		std::cout << "| Keypad subtract   | {SUBTRACT}                        |" << std::endl;
		std::cout << "| Keypad multiply   | {MULTIPLY}                        |" << std::endl;
		std::cout << "| Keypad divide     | {DIVIDE}                          |" << std::endl;
		std::cout << "| +                 | {PLUS}                            |" << std::endl;
		std::cout << "| @                 | {AT}                              |" << std::endl;
		std::cout << "| APPS              | {APPS}                            |" << std::endl;
		std::cout << "=========================================================" << std::endl;
		std::cout << std::endl;
		return 1;
	}
	
	//start end module
	std::thread t1(endSpam);
	t1.detach();
	
	std::cout << "# press 'q' to exit..." << std::endl;
	std::cout << "# starting spam in 3..." << std::endl; Sleep(1000);
	std::cout << "# starting spam in 2..." << std::endl; Sleep(1000);
	std::cout << "# starting spam in 1..." << std::endl; Sleep(1000);
	std::cout << "# spam started, press 'q' to exit..." << std::endl;
	
	int sleep = atoi(argv[1]);
	char* app = argv[2];
	char* txt = argv[3];
	
	//setup
	CSendKeys sk;
	sk.AppActivate(app);

	while(!g_Exit) {
		sk.SendKeys(txt);
		Sleep(sleep);
	}
	
	return 0;
}
