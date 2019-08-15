#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <stdlib.h>

//LETTERS
#define VK_KEY_A 65
#define VK_KEY_B 66
#define VK_KEY_C 67
#define VK_KEY_D 68
#define VK_KEY_E 69
#define VK_KEY_F 70
#define VK_KEY_G 71
#define VK_KEY_H 72
#define VK_KEY_I 73
#define VK_KEY_J 74
#define VK_KEY_K 75
#define VK_KEY_L 76
#define VK_KEY_M 77
#define VK_KEY_N 78
#define VK_KEY_O 79
#define VK_KEY_P 80
#define VK_KEY_Q 81
#define VK_KEY_R 82
#define VK_KEY_S 83
#define VK_KEY_T 84
#define VK_KEY_U 85
#define VK_KEY_V 86
#define VK_KEY_W 87
#define VK_KEY_X 88
#define VK_KEY_Y 89
#define VK_KEY_Z 90

//NUMS
#define VK_KEY_0 48
#define VK_KEY_1 49
#define VK_KEY_2 50
#define VK_KEY_3 51
#define VK_KEY_4 52
#define VK_KEY_5 53
#define VK_KEY_6 54
#define VK_KEY_7 55
#define VK_KEY_8 56
#define VK_KEY_9 57


//KEYBOARD
void send_vk_keyboard(WORD vkey) {
	
	// VIRTUAL KEYS: http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
	// STACK OVERFLOW: https://stackoverflow.com/questions/1021175/sendinput-keyboard-letters-c-c
	
	INPUT input; 
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
	SendInput(1, &input, sizeof(INPUT));
	
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

//KEYBOARD + SHIFT
void send_vk_keyboard_shift(WORD vkey) {
	
	// VIRTUAL KEYS: http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
	// STACK OVERFLOW: https://stackoverflow.com/questions/1021175/sendinput-keyboard-letters-c-c
	
	//KEY
	INPUT input; 
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	
	//SHIFT
	INPUT shift;
	shift.type = INPUT_KEYBOARD;
	shift.ki.wScan = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
	shift.ki.time = 0;
	shift.ki.dwExtraInfo = 0;
	shift.ki.wVk = VK_LSHIFT;
	
	//HOLD SHIFT
	shift.ki.dwFlags = 0;
	SendInput(1, &shift, sizeof(INPUT));
	
	//PRESS KEY
	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	
	//RELEASE SHIFT
	shift.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &shift, sizeof(INPUT));
}

//MOUSE
void send_vk_mouse(WORD vkey) {
	
	INPUT input;
	
	// left down 
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));
	
	// left up
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &input, sizeof(INPUT));
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

bool g_Exit = false;
void endSpam() {
	
	while(g_Exit == false) {
		Sleep(50);
		
		if (GetAsyncKeyState(VK_KEY_Q) != 0) {
			std::cout << "# 'q' pressed exiting..." << std::endl;
			g_Exit = true;
			break;
		}
	}
	
	exit(0);
}

int main(int argc, char* argv[]) {
	
	if (argc < 3) {
		std::cerr << "USAGE: " << argv[0] << " <delay (ms)> <spam string>" << std::endl;
		std::cerr << "  / == VK_RETURN                           " << std::endl;
		std::cerr << "  < == VK_BACK                             " << std::endl;
		std::cerr << "  + == VK_LBUTTON                          " << std::endl;
		std::cerr << "  ; == VK_MENU + VK_F4                     " << std::endl;
		std::cerr << "  } == VK_CONTROL + VK_KEY_V               " << std::endl;
		std::cerr << "  _ == VK_LWIN + VK_KEY_D                  " << std::endl;
		std::cerr << "  > == VK_LWIN + VK_KEY_R                  " << std::endl;
		std::cerr << std::endl;
		return 1;
	}
	
	//start end module
	std::thread t1(endSpam);
	t1.detach();
	
	std::cout << "# press 'q' to exit..."  << std::endl;
	std::cout << "# starting spam in 3..." << std::endl; Sleep(1000);
	std::cout << "# starting spam in 2..." << std::endl; Sleep(1000);
	std::cout << "# starting spam in 1..." << std::endl; Sleep(1000);
	
	std::cout << "# spam started, press 'q' to exit..." << std::endl;
	
	int sleep_char = 10;
	int sleep_line = atoi(argv[1]);
	
	while(!g_Exit) {
		
		std::string SEND = argv[2];
		
		for(char& c : SEND) {
			switch(c) {
				
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
				
				case 'A': send_vk_keyboard_shift(VK_KEY_A); break;
				case 'B': send_vk_keyboard_shift(VK_KEY_B); break;
				case 'C': send_vk_keyboard_shift(VK_KEY_C); break;
				case 'D': send_vk_keyboard_shift(VK_KEY_D); break;
				case 'E': send_vk_keyboard_shift(VK_KEY_E); break;
				case 'F': send_vk_keyboard_shift(VK_KEY_F); break;
				case 'G': send_vk_keyboard_shift(VK_KEY_G); break;
				case 'H': send_vk_keyboard_shift(VK_KEY_H); break;
				case 'I': send_vk_keyboard_shift(VK_KEY_I); break;
				case 'J': send_vk_keyboard_shift(VK_KEY_J); break;
				case 'K': send_vk_keyboard_shift(VK_KEY_K); break;
				case 'L': send_vk_keyboard_shift(VK_KEY_L); break;
				case 'M': send_vk_keyboard_shift(VK_KEY_M); break;
				case 'N': send_vk_keyboard_shift(VK_KEY_N); break;
				case 'O': send_vk_keyboard_shift(VK_KEY_O); break;
				case 'P': send_vk_keyboard_shift(VK_KEY_P); break;
				case 'Q': send_vk_keyboard_shift(VK_KEY_Q); break;
				case 'R': send_vk_keyboard_shift(VK_KEY_R); break;
				case 'S': send_vk_keyboard_shift(VK_KEY_S); break;
				case 'T': send_vk_keyboard_shift(VK_KEY_T); break;
				case 'U': send_vk_keyboard_shift(VK_KEY_U); break;
				case 'V': send_vk_keyboard_shift(VK_KEY_V); break;
				case 'W': send_vk_keyboard_shift(VK_KEY_W); break;
				case 'X': send_vk_keyboard_shift(VK_KEY_X); break;
				case 'Y': send_vk_keyboard_shift(VK_KEY_Y); break;
				case 'Z': send_vk_keyboard_shift(VK_KEY_Z); break;
				
				//DEPEND ON KEYBOARD
				case ')': send_vk_keyboard_shift(VK_KEY_0); break;
				case '!': send_vk_keyboard_shift(VK_KEY_1); break;
				case '@': send_vk_keyboard_shift(VK_KEY_2); break;
				case '#': send_vk_keyboard_shift(VK_KEY_3); break;
				case '$': send_vk_keyboard_shift(VK_KEY_4); break;
				case '%': send_vk_keyboard_shift(VK_KEY_5); break;
				case '^': send_vk_keyboard_shift(VK_KEY_6); break;
				case '&': send_vk_keyboard_shift(VK_KEY_7); break;
				case '*': send_vk_keyboard_shift(VK_KEY_8); break;
				case '(': send_vk_keyboard_shift(VK_KEY_9); break;
				
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
				
				case ' ': send_vk_keyboard(VK_SPACE); break;
				
				// -_=+[{]};:'"\|,<.>/?
				
				//SPECIAL CHARS
				case '/': send_vk_keyboard(VK_RETURN); break;
				case '<': send_vk_keyboard(VK_BACK);   break;
				case '+': send_vk_mouse(VK_LBUTTON);   break;
				case ';': combo_alt_f4();              break;
				case '_': combo_win_d();               break;
				case '>': combo_win_r();               break;
				case '}': combo_ctrl_v();              break;
				
			}
			
			Sleep(sleep_char);
		}
		
		Sleep(sleep_line);
	}
	
	return 0;
}

























