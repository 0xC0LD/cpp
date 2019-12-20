#include <stdio.h>
#include <list>
#include <thread>

#include <windows.h>
#include "vk.h"

void send_vk_keyboard(WORD vkey, bool holdShift = false) {
	
	// SHIFT
	INPUT shift;
	
	if (holdShift) {
		shift.type = INPUT_KEYBOARD;
		shift.ki.wScan = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
		shift.ki.time = 0;
		shift.ki.dwExtraInfo = 0;
		shift.ki.wVk = VK_LSHIFT;
	
		shift.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
		SendInput(1, &shift, sizeof(INPUT));
	}
	
	INPUT input; 
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	
	input.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	
	if (holdShift) {
		shift.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &shift, sizeof(INPUT));
	}
}

void send_vk_mouse(WORD vkey) {
	
	INPUT input;
	
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT)); // send left key down
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT)); // send left key up
}

//WINDOWS KEY + D = SHOW DESKTOP
void combo_win_d() {

	//91 = VK_LWIN
	//68 = VK_KEY_D
	WORD input_word = VK_LWIN;
	INPUT input; 
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(input_word, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = input_word;
	
	WORD input_word2 = VK_KEY_D;
	INPUT input2; 
	input2.type = INPUT_KEYBOARD;
	input2.ki.wScan = MapVirtualKey(input_word2, MAPVK_VK_TO_VSC);
	input2.ki.time = 0;
	input2.ki.dwExtraInfo = 0;
	input2.ki.wVk = input_word2;
	
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
	
	input2.ki.dwFlags = 0;
	SendInput(1, &input2, sizeof(INPUT));
	input2.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input2, sizeof(INPUT));
	
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	
}
//WINDOWS KEY + R = RUNBOX
void combo_win_r() {
	
	//91 = VK_LWIN
	//76 = VK_KEY_L
	WORD input_word = VK_LWIN;
	INPUT input; 
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(input_word, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = input_word;
	
	WORD input_word2 = VK_KEY_R;
	INPUT input2; 
	input2.type = INPUT_KEYBOARD;
	input2.ki.wScan = MapVirtualKey(input_word2, MAPVK_VK_TO_VSC);
	input2.ki.time = 0;
	input2.ki.dwExtraInfo = 0;
	input2.ki.wVk = input_word2;
	
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
	
	input2.ki.dwFlags = 0;
	SendInput(1, &input2, sizeof(INPUT));
	input2.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input2, sizeof(INPUT));
	
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	
}
//ALT + F4 = CLOSE TAB
void combo_alt_f4() {
	
	//18  = VK_MENU (ALT)
	//115 = VK_F4
	WORD input_word = VK_MENU;
	INPUT input; 
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(input_word, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = input_word;
	
	WORD input_word2 = VK_F4;
	INPUT input2; 
	input2.type = INPUT_KEYBOARD;
	input2.ki.wScan = MapVirtualKey(input_word2, MAPVK_VK_TO_VSC);
	input2.ki.time = 0;
	input2.ki.dwExtraInfo = 0;
	input2.ki.wVk = input_word2;
	
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
	
	input2.ki.dwFlags = 0;
	SendInput(1, &input2, sizeof(INPUT));
	input2.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input2, sizeof(INPUT));
	
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}
//CTRL + V = PASTE
void combo_ctrl_v() {
	
	WORD input_word = VK_CONTROL;
	INPUT input; 
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(input_word, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = input_word;
	
	WORD input_word2 = VK_KEY_V;
	INPUT input2; 
	input2.type = INPUT_KEYBOARD;
	input2.ki.wScan = MapVirtualKey(input_word2, MAPVK_VK_TO_VSC);
	input2.ki.time = 0;
	input2.ki.dwExtraInfo = 0;
	input2.ki.wVk = input_word2;
	
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
	
	input2.ki.dwFlags = 0;
	SendInput(1, &input2, sizeof(INPUT));
	input2.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input2, sizeof(INPUT));
	
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

const char* getSendkeyHelp() {
	return 
	"  \\n - ENTER\n"
	"  \\b - BACKSPACE\n"
	"  \\e - ESCAPE\n"
	"  \\a - ALT\n"
	"  \\c - CTRL\n"
	"  \\w - WINDOWS\n"
	"  \\d - DEL\n"
	"\n"
	"  \\t - ALT + F4\n"
	"  \\h - WIN + D\n"
	"  \\r - WIN + R\n"
	"\n"
	"  \\1 - LMB\n"
	"  \\2 - MMB\n"
	"  \\3 - RMB\n"
	"\n"
	"  \\v - CTRL + V\n"
		 ;
}

int sendkey(const char* str) {
	
	std::list<int> keys;
	
	bool nextIsSpecial = false;
	for (int i = 0; i < strlen(str); i++) {
		
		if (nextIsSpecial && str[i] == '\\') {
			keys.push_back(str[i]);
			nextIsSpecial = false;
			continue;
		}
		
		if (str[i] == '\\') {
			nextIsSpecial = true;
			continue;
		}
		
		if (nextIsSpecial) {
			switch(str[i]) {
				
				// special keyboard
				case 'n': keys.push_back(300); break; // enter
				case 'b': keys.push_back(301); break; // backspace
				case 'e': keys.push_back(302); break; // escape
				case 'a': keys.push_back(303); break; // alt
				case 'c': keys.push_back(304); break; // ctrl
				case 'w': keys.push_back(305); break; // windows / mod
				case 'd': keys.push_back(306); break; // delete
				
				// keyboard combos
				case 't': keys.push_back(400); break; // alt + F4
				case 'h': keys.push_back(401); break; // show desktop hide all
				case 'r': keys.push_back(402); break; // run box
				
				// mouse buttons
				case '1': keys.push_back(500); break; // LMB
				case '2': keys.push_back(501); break; // MMB
				case '3': keys.push_back(502); break; // RMB
				
				case 'v': keys.push_back(600); break; // CTRL + V
			}
			nextIsSpecial = false;
			continue;
		}
		
			
		keys.push_back((int)str[i]);
	}
	
	for (std::list<int>::const_iterator iterator = keys.begin(), end = keys.end(); iterator != end; ++iterator) {
		switch(*iterator) {
			
			case ' ': send_vk_keyboard(VK_SPACE); break;
			
			case 'a': send_vk_keyboard(VK_KEY_A); break;
			case 'b': send_vk_keyboard(VK_KEY_B); break;
			case 'c': send_vk_keyboard(VK_KEY_C); break;
			case 'd': send_vk_keyboard(VK_KEY_D); break;
			case 'e': send_vk_keyboard(VK_KEY_E); break;
			case 'f': send_vk_keyboard(VK_KEY_F); break;
			case 'g': send_vk_keyboard(VK_KEY_G); break;
			case 'h': send_vk_keyboard(VK_KEY_H); break;
			case 'i': send_vk_keyboard(VK_KEY_I); break;
			case 'j': send_vk_keyboard(VK_KEY_J); break;
			case 'k': send_vk_keyboard(VK_KEY_K); break;
			case 'l': send_vk_keyboard(VK_KEY_L); break;
			case 'm': send_vk_keyboard(VK_KEY_M); break;
			case 'n': send_vk_keyboard(VK_KEY_N); break;
			case 'o': send_vk_keyboard(VK_KEY_O); break;
			case 'p': send_vk_keyboard(VK_KEY_P); break;
			case 'q': send_vk_keyboard(VK_KEY_Q); break;
			case 'r': send_vk_keyboard(VK_KEY_R); break;
			case 's': send_vk_keyboard(VK_KEY_S); break;
			case 't': send_vk_keyboard(VK_KEY_T); break;
			case 'u': send_vk_keyboard(VK_KEY_U); break;
			case 'v': send_vk_keyboard(VK_KEY_V); break;
			case 'w': send_vk_keyboard(VK_KEY_W); break;
			case 'x': send_vk_keyboard(VK_KEY_X); break;
			case 'y': send_vk_keyboard(VK_KEY_Y); break;
			case 'z': send_vk_keyboard(VK_KEY_Z); break;
			
			case 'A': send_vk_keyboard(VK_KEY_A, true); break;
			case 'B': send_vk_keyboard(VK_KEY_B, true); break;
			case 'C': send_vk_keyboard(VK_KEY_C, true); break;
			case 'D': send_vk_keyboard(VK_KEY_D, true); break;
			case 'E': send_vk_keyboard(VK_KEY_E, true); break;
			case 'F': send_vk_keyboard(VK_KEY_F, true); break;
			case 'G': send_vk_keyboard(VK_KEY_G, true); break;
			case 'H': send_vk_keyboard(VK_KEY_H, true); break;
			case 'I': send_vk_keyboard(VK_KEY_I, true); break;
			case 'J': send_vk_keyboard(VK_KEY_J, true); break;
			case 'K': send_vk_keyboard(VK_KEY_K, true); break;
			case 'L': send_vk_keyboard(VK_KEY_L, true); break;
			case 'M': send_vk_keyboard(VK_KEY_M, true); break;
			case 'N': send_vk_keyboard(VK_KEY_N, true); break;
			case 'O': send_vk_keyboard(VK_KEY_O, true); break;
			case 'P': send_vk_keyboard(VK_KEY_P, true); break;
			case 'Q': send_vk_keyboard(VK_KEY_Q, true); break;
			case 'R': send_vk_keyboard(VK_KEY_R, true); break;
			case 'S': send_vk_keyboard(VK_KEY_S, true); break;
			case 'T': send_vk_keyboard(VK_KEY_T, true); break;
			case 'U': send_vk_keyboard(VK_KEY_U, true); break;
			case 'V': send_vk_keyboard(VK_KEY_V, true); break;
			case 'W': send_vk_keyboard(VK_KEY_W, true); break;
			case 'X': send_vk_keyboard(VK_KEY_X, true); break;
			case 'Y': send_vk_keyboard(VK_KEY_Y, true); break;
			case 'Z': send_vk_keyboard(VK_KEY_Z, true); break;
			
			case '0': send_vk_keyboard(VK_KEY_0); break;
			case '1': send_vk_keyboard(VK_KEY_1); break;
			case '2': send_vk_keyboard(VK_KEY_2); break;
			case '3': send_vk_keyboard(VK_KEY_3); break;
			case '4': send_vk_keyboard(VK_KEY_4); break;
			case '5': send_vk_keyboard(VK_KEY_5); break;
			case '6': send_vk_keyboard(VK_KEY_6); break;
			case '7': send_vk_keyboard(VK_KEY_7); break;
			case '8': send_vk_keyboard(VK_KEY_8); break;
			case '9': send_vk_keyboard(VK_KEY_9); break;
			
			case ')': send_vk_keyboard(VK_KEY_0, true); break;
			case '!': send_vk_keyboard(VK_KEY_1, true); break;
			case '@': send_vk_keyboard(VK_KEY_2, true); break;
			case '#': send_vk_keyboard(VK_KEY_3, true); break;
			case '$': send_vk_keyboard(VK_KEY_4, true); break;
			case '%': send_vk_keyboard(VK_KEY_5, true); break;
			case '^': send_vk_keyboard(VK_KEY_6, true); break;
			case '&': send_vk_keyboard(VK_KEY_7, true); break;
			case '*': send_vk_keyboard(VK_KEY_8, true); break;
			case '(': send_vk_keyboard(VK_KEY_9, true); break;
			
			case ';' : send_vk_keyboard(VK_OEM_1);   break;
			case '/' : send_vk_keyboard(VK_OEM_2);   break;
			case '`' : send_vk_keyboard(VK_OEM_3);   break;
			case '[' : send_vk_keyboard(VK_OEM_4);   break;
			case '\\': send_vk_keyboard(VK_OEM_5);   break;
			case ']' : send_vk_keyboard(VK_OEM_6);   break;
			case '\'': send_vk_keyboard(VK_OEM_7);   break;
			
			case ':': send_vk_keyboard(VK_OEM_1, true); break;
			case '?': send_vk_keyboard(VK_OEM_2, true); break;
			case '~': send_vk_keyboard(VK_OEM_3, true); break;
			case '{': send_vk_keyboard(VK_OEM_4, true); break;
			case '|': send_vk_keyboard(VK_OEM_5, true); break;
			case '}': send_vk_keyboard(VK_OEM_6, true); break;
			case '"': send_vk_keyboard(VK_OEM_7, true); break;
			
			case '-': send_vk_keyboard(VK_OEM_MINUS); break;
			case '=': send_vk_keyboard(VK_OEM_PLUS);  break;
			
			case '_': send_vk_keyboard(VK_OEM_MINUS, true); break;
			case '+': send_vk_keyboard(VK_OEM_PLUS,  true); break;
			
			case ',': send_vk_keyboard(VK_OEM_COMMA);        break;
			case '<': send_vk_keyboard(VK_OEM_COMMA,  true); break;
			
			case '.': send_vk_keyboard(VK_OEM_PERIOD);       break;
			case '>': send_vk_keyboard(VK_OEM_PERIOD, true); break;
			
			
			case 300: send_vk_keyboard(VK_RETURN);   break;
			case 301: send_vk_keyboard(VK_BACK);     break;
			case 302: send_vk_keyboard(VK_ESCAPE);   break;
			case 303: send_vk_keyboard(VK_LMENU);    break;
			case 304: send_vk_keyboard(VK_LCONTROL); break;
			case 305: send_vk_keyboard(VK_LWIN);     break;
			case 306: send_vk_keyboard(VK_DELETE);   break;
			
			case 400: combo_alt_f4(); break;
			case 401: combo_win_d();  break;
			case 402: combo_win_r();  break;
			
			case 500: send_vk_mouse(VK_LBUTTON); break;
			case 501: send_vk_mouse(VK_MBUTTON); break;
			case 502: send_vk_mouse(VK_RBUTTON); break;
			
			case 600: combo_ctrl_v(); break;
			
		}
		
		Sleep(10);
	}
	
	return 0;
}

bool g_Exit = false;
void endSpam() {
	
	while(g_Exit == false) {
		Sleep(50);
		
		if (GetAsyncKeyState(VK_END) != 0) {
			printf("# [END] pressed, exiting...\n");
			g_Exit = true;
			break;
		}
	}
	
	exit(0);
}

int main(int argc, char* argv[]) {
	
	if (argc < 2) {
		fprintf(stderr, "USAGE: %s <stringToSend>\n", argv[0]);
		fprintf(stderr, "%s\n", getSendkeyHelp());
		return 1;
	}
	
	// start quit thread
	std::thread t1(endSpam);
	t1.detach();
	
	printf("# press the [END] key on your keyboard to stop the spam...\n");
	printf("# starting spam in 3...\n"); Sleep(1000);
	printf("# starting spam in 2...\n"); Sleep(1000);
	printf("# starting spam in 1...\n"); Sleep(1000);
	
	while (!g_Exit) {
		sendkey(argv[1]);
	}
	
	return 0;
}




















