#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <cstdlib>

//ICON: NULL
void MsgBoxIconNo(std::string ARG2, std::string ARG3) { 

	std::string OutPut = "MSG: ico[-] tit[" + ARG2 + "] msg[" + ARG3 + "] opt[OK]";
	std::cout << OutPut << std::endl;
	const int Msg = MessageBox(NULL, ARG3.c_str(), ARG2.c_str(), MB_OK | MB_TOPMOST );
	
	switch(Msg) { case IDOK: std::cout << "USR: OK" << std::endl; break; }
}

//ICON: ERROR
void MsgBoxIconError(std::string ARG2, std::string ARG3) {

	std::string OutPut = "MSG: ico[x] tit[" + ARG2 + "] msg[" + ARG3 + "] opt[OK]";
	std::cout << OutPut << std::endl;
	const int Msg = MessageBox(NULL, ARG3.c_str(), ARG2.c_str(), MB_OK | MB_ICONERROR | MB_TOPMOST );
	
	switch(Msg) { case IDOK: std::cout << "USR: OK" << std::endl; break; }
}

//ICON: WARNING
void MsgBoxIconWarning(std::string ARG2, std::string ARG3) {
	
	std::string OutPut = "MSG: ico[!] tit[" + ARG2 + "] msg[" + ARG3 + "] opt[OK]";
	std::cout << OutPut << std::endl;
	const int Msg = MessageBox(NULL, ARG3.c_str(), ARG2.c_str(), MB_OK | MB_ICONWARNING | MB_TOPMOST );
	
	switch(Msg) { case IDOK: std::cout << "USR: OK" << std::endl; break; }
}

//ICON: INFORMATION
void MsgBoxIconInformation(std::string ARG2, std::string ARG3) {
	
	std::string OutPut = "MSG: ico[i] tit[" + ARG2 + "] msg[" + ARG3 + "] opt[OK]";
	std::cout << OutPut << std::endl;
	const int Msg = MessageBox(NULL, ARG3.c_str(), ARG2.c_str(), MB_OK | MB_ICONINFORMATION | MB_TOPMOST );
	
	switch(Msg) { case IDOK: std::cout << "USR: OK" << std::endl; break; }
}

//ICON: QUESTION
void MsgBoxIconQuestion(std::string ARG2, std::string ARG3) {
	
	std::string OutPut = "MSG: ico[?] tit[" + ARG2 + "] msg[" + ARG3 + "] opt[YES/NO]";
	std::cout << OutPut << std::endl;
	const int Msg = MessageBox(NULL, ARG3.c_str(), ARG2.c_str(), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
	
	switch(Msg) {
		case IDYES: std::cout << "USR: YES" << std::endl; break;
		case IDNO:  std::cout << "USR: NO"  << std::endl; break;
	}
}

void MsgBoxPrankShutdown() {
	
	std::cout << "MSG: ico[i] tit[You are about to be logged off] msg[Windows will shut down in less then a minute.] opt[OK/CANCEL]" << std::endl;
	const int Msg1 = MessageBox(NULL, "Windows will shut down in less then a minute.", "You are about to be logged off", MB_OKCANCEL | MB_ICONINFORMATION | MB_TOPMOST);
	
	switch(Msg1) {
		case IDOK: std::cout << "USR: OK" << std::endl; break;
		case IDCANCEL:
		
			std::cout << "USR: CANCEL" << std::endl;
			std::cout << "MSG: ico[!] tit[You are about to be logged off] msg[Windows needs to shutdown to complete important updates.] opt[YES/NO]" << std::endl;
	
			const int Msg2 = MessageBox(NULL, "Windows needs to shutdown to complete important updates.", "You are about to be logged off", MB_YESNO | MB_ICONWARNING | MB_TOPMOST);
			switch(Msg2) {
				case IDYES: std::cout << "USR: YES" << std::endl; break;
				case IDNO:
					std::cout << "USR: NO" << std::endl;
					std::cout << "MSG: ico[?] tit[You are about to be logged off] msg[Bro. Are you fucking kidding me?] opt[YES/NO]" << std::endl;
					const int Msg3 = MessageBox(NULL, "Bro. Are you fucking kidding me?", "You are about to be logged off", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
					switch(Msg3) {
						case IDYES:
							std::cout << "USR: YES" << std::endl;
							std::cout << "MSG: ico[!] tit[You are about to be logged off] msg[Yes? Good. cus i will shutdown ur pc... fag! >:C] opt[YES/NO]" << std::endl;
							MessageBox(NULL, "Yes? Good. cus i will shutdown ur pc... fag! >:C", "You are about to be logged off", MB_OK | MB_ICONWARNING | MB_TOPMOST);
							break;
						
						case IDNO:
							std::cout << "USR: NO" << std::endl;
							
							std::cout << "MSG: ico[!] tit[You are about to be logged off] msg[No...?   well too bad you're going down mister! >:C] opt[YES/NO]" << std::endl;
							MessageBox(NULL, "No...?   well too bad you're going down mister! >:C", "You are about to be logged off", MB_OK | MB_ICONWARNING | MB_TOPMOST);
							break;
					}
					break;
			}
			break;
	}
}

//HELP
void printHelp(std::string exename) {
	std::cout << "USAGE: " << exename << " \"Switch(ex. 0)\" " << " \"Title\" " << " \"Message\""  << std::endl;
	std::cout << "SWITCHES: "                                                                      << std::endl;
	std::cout << "          0 = Icon: NULL"                                                        << std::endl;
	std::cout << "          1 = Icon: Error "	                                                   << std::endl;
	std::cout << "          2 = Icon: Warning"	                                                   << std::endl;
	std::cout << "          3 = Icon: Information"                                                 << std::endl;
	std::cout << "          4 = Icon: Question"	                                                   << std::endl;
	std::cout << "          5 = Shutdown Prank"	                                                   << std::endl;
}

int main(int argc, char* argv[]) {
	
	if (argc == 1) { printHelp(argv[0]); return 1; }
	if (argc == 2 && argv[1] == std::string("--help")) { printHelp(argv[0]); return 0; }
	
	int type = atoi(argv[1]);
	std::string title = argc >= 3 ? argv[2] : "";
	std::string msg   = argc >= 4 ? argv[3] : "";
	
	
	switch(type) {
		case 0: default: MsgBoxIconNo         (title, msg); break;
		case 1:          MsgBoxIconError      (title, msg); break;
		case 2:          MsgBoxIconWarning    (title, msg); break;
		case 3:          MsgBoxIconInformation(title, msg); break;
		case 4:          MsgBoxIconQuestion   (title, msg); break;
		case 5:          MsgBoxPrankShutdown  ();           break;
	}
	
	
	return 0;
}