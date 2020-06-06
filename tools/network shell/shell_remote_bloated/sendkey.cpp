#include <iostream>
#include <string>
#include <list>

#include <windows.h>
#include "vk.h"

enum KB{
	NORMAL = 0x00,
	SHIFT  = 0x01,
	CTRL   = 0x02,
	WIN    = 0x04,
	ALT    = 0x08,
};

void send_vk_keyboard(WORD vkey, KB flags = NORMAL) {
	
	// SHIFT
	INPUT shift;
	INPUT ctrl;
	INPUT alt;
	INPUT win;
	
	if (flags & SHIFT) {
		shift.type = INPUT_KEYBOARD;
		shift.ki.wScan = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
		shift.ki.time = 0;
		shift.ki.dwExtraInfo = 0;
		shift.ki.wVk = VK_LSHIFT;
		shift.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
		SendInput(1, &shift, sizeof(INPUT));
	}
	
	if (flags & CTRL) {
		ctrl.type = INPUT_KEYBOARD;
		ctrl.ki.wScan = MapVirtualKey(VK_LCONTROL, MAPVK_VK_TO_VSC);
		ctrl.ki.time = 0;
		ctrl.ki.dwExtraInfo = 0;
		ctrl.ki.wVk = VK_LCONTROL;
		ctrl.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
		SendInput(1, &ctrl, sizeof(INPUT));
	}
	
	if (flags & ALT) {
		alt.type = INPUT_KEYBOARD;
		alt.ki.wScan = MapVirtualKey(VK_LMENU, MAPVK_VK_TO_VSC);
		alt.ki.time = 0;
		alt.ki.dwExtraInfo = 0;
		alt.ki.wVk = VK_LMENU;
		alt.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
		SendInput(1, &alt, sizeof(INPUT));
	}
	
	if (flags & WIN) {
		win.type = INPUT_KEYBOARD;
		win.ki.wScan = MapVirtualKey(VK_LWIN, MAPVK_VK_TO_VSC);
		win.ki.time = 0;
		win.ki.dwExtraInfo = 0;
		win.ki.wVk = VK_LWIN;
		win.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
		SendInput(1, &win, sizeof(INPUT));
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
	
	if (flags & SHIFT) {
		shift.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &shift, sizeof(INPUT));
	}
	
	if (flags & CTRL) {
		ctrl.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ctrl, sizeof(INPUT));
	}
	
	if (flags & ALT) {
		alt.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &alt, sizeof(INPUT));
	}
	
	if (flags & WIN) {
		win.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &win, sizeof(INPUT));
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

std::string getSendkeyHelp() {
	return std::string()
	+ "  \\n - ENTER" + "\n"
	+ "  \\b - BACKSPACE" + "\n"
	+ "  \\e - ESCAPE" + "\n"
	+ "  \\a - ALT" + "\n"
	+ "  \\c - CTRL" + "\n"
	+ "  \\w - WINDOWS" + "\n"
	+ "  \\d - DEL" + "\n"
	+ "\n"
	+ "  \\t - ALT + F4" + "\n"
	+ "  \\h - WIN + D" + "\n"
	+ "  \\r - WIN + R" + "\n"
	+ "\n"
	+ "  \\1 - LMB" + "\n"
	+ "  \\2 - MMB" + "\n"
	+ "  \\3 - RMB" + "\n"
	+ "\n"
	+ "  \\v - CTRL + V" + "\n"
	;
}

int sendkey(std::string str) {
	
	std::list<int> keys;
	
	bool nextIsSpecial = false;
	for (unsigned int i = 0; i < str.length(); i++) {
		
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
				case 'a': keys.push_back(303); break; // ALT
				case 'w': keys.push_back(304); break; // WIN / MOD
				case 'd': keys.push_back(305); break; // DEL
				
				// keyboard combos
				case 't': keys.push_back(400); break; // ALT + F4
				case 'h': keys.push_back(401); break; // WIN + D / show desktop / hide all windows
				case 'r': keys.push_back(402); break; // WIN + R / run box
				
				// mouse buttons
				case '1': keys.push_back(500); break; // LMB
				case '2': keys.push_back(501); break; // MMB
				case '3': keys.push_back(502); break; // RMB
				
				case 's': keys.push_back(600); break; // CTRL + A
				case 'c': keys.push_back(601); break; // CTRL + C
				case 'v': keys.push_back(602); break; // CTRL + V
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
			
			case 'A': send_vk_keyboard(VK_KEY_A, SHIFT); break;
			case 'B': send_vk_keyboard(VK_KEY_B, SHIFT); break;
			case 'C': send_vk_keyboard(VK_KEY_C, SHIFT); break;
			case 'D': send_vk_keyboard(VK_KEY_D, SHIFT); break;
			case 'E': send_vk_keyboard(VK_KEY_E, SHIFT); break;
			case 'F': send_vk_keyboard(VK_KEY_F, SHIFT); break;
			case 'G': send_vk_keyboard(VK_KEY_G, SHIFT); break;
			case 'H': send_vk_keyboard(VK_KEY_H, SHIFT); break;
			case 'I': send_vk_keyboard(VK_KEY_I, SHIFT); break;
			case 'J': send_vk_keyboard(VK_KEY_J, SHIFT); break;
			case 'K': send_vk_keyboard(VK_KEY_K, SHIFT); break;
			case 'L': send_vk_keyboard(VK_KEY_L, SHIFT); break;
			case 'M': send_vk_keyboard(VK_KEY_M, SHIFT); break;
			case 'N': send_vk_keyboard(VK_KEY_N, SHIFT); break;
			case 'O': send_vk_keyboard(VK_KEY_O, SHIFT); break;
			case 'P': send_vk_keyboard(VK_KEY_P, SHIFT); break;
			case 'Q': send_vk_keyboard(VK_KEY_Q, SHIFT); break;
			case 'R': send_vk_keyboard(VK_KEY_R, SHIFT); break;
			case 'S': send_vk_keyboard(VK_KEY_S, SHIFT); break;
			case 'T': send_vk_keyboard(VK_KEY_T, SHIFT); break;
			case 'U': send_vk_keyboard(VK_KEY_U, SHIFT); break;
			case 'V': send_vk_keyboard(VK_KEY_V, SHIFT); break;
			case 'W': send_vk_keyboard(VK_KEY_W, SHIFT); break;
			case 'X': send_vk_keyboard(VK_KEY_X, SHIFT); break;
			case 'Y': send_vk_keyboard(VK_KEY_Y, SHIFT); break;
			case 'Z': send_vk_keyboard(VK_KEY_Z, SHIFT); break;
			
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
			
			case ')': send_vk_keyboard(VK_KEY_0, SHIFT); break;
			case '!': send_vk_keyboard(VK_KEY_1, SHIFT); break;
			case '@': send_vk_keyboard(VK_KEY_2, SHIFT); break;
			case '#': send_vk_keyboard(VK_KEY_3, SHIFT); break;
			case '$': send_vk_keyboard(VK_KEY_4, SHIFT); break;
			case '%': send_vk_keyboard(VK_KEY_5, SHIFT); break;
			case '^': send_vk_keyboard(VK_KEY_6, SHIFT); break;
			case '&': send_vk_keyboard(VK_KEY_7, SHIFT); break;
			case '*': send_vk_keyboard(VK_KEY_8, SHIFT); break;
			case '(': send_vk_keyboard(VK_KEY_9, SHIFT); break;
			
			case ';' : send_vk_keyboard(VK_OEM_1);   break;
			case '/' : send_vk_keyboard(VK_OEM_2);   break;
			case '`' : send_vk_keyboard(VK_OEM_3);   break;
			case '[' : send_vk_keyboard(VK_OEM_4);   break;
			case '\\': send_vk_keyboard(VK_OEM_5);   break;
			case ']' : send_vk_keyboard(VK_OEM_6);   break;
			case '\'': send_vk_keyboard(VK_OEM_7);   break;
			
			case ':': send_vk_keyboard(VK_OEM_1, SHIFT); break;
			case '?': send_vk_keyboard(VK_OEM_2, SHIFT); break;
			case '~': send_vk_keyboard(VK_OEM_3, SHIFT); break;
			case '{': send_vk_keyboard(VK_OEM_4, SHIFT); break;
			case '|': send_vk_keyboard(VK_OEM_5, SHIFT); break;
			case '}': send_vk_keyboard(VK_OEM_6, SHIFT); break;
			case '"': send_vk_keyboard(VK_OEM_7, SHIFT); break;
			
			case '-': send_vk_keyboard(VK_OEM_MINUS); break;
			case '=': send_vk_keyboard(VK_OEM_PLUS,  NORMAL); break;
			
			case '_': send_vk_keyboard(VK_OEM_MINUS, SHIFT); break;
			case '+': send_vk_keyboard(VK_OEM_PLUS,  SHIFT); break;
			
			case ',': send_vk_keyboard(VK_OEM_COMMA);  break;
			case '<': send_vk_keyboard(VK_OEM_COMMA, SHIFT); break;
			
			case '.': send_vk_keyboard(VK_OEM_PERIOD);  break;
			case '>': send_vk_keyboard(VK_OEM_PERIOD, SHIFT); break;
			
			
			case 300: send_vk_keyboard(VK_RETURN); break; // enter
			case 301: send_vk_keyboard(VK_BACK,   NORMAL); break; // backspace
			case 302: send_vk_keyboard(VK_ESCAPE); break; // escape
			case 303: send_vk_keyboard(VK_LMENU,  NORMAL); break; // ALT
			case 304: send_vk_keyboard(VK_LWIN,   NORMAL); break; // WIN / MOD
			case 305: send_vk_keyboard(VK_DELETE); break; // DEL
			
			case 400: send_vk_keyboard(VK_F4, ALT);    break; // ALT + F4
			case 401: send_vk_keyboard(VK_KEY_D, WIN); break; // WIN + D
			case 402: send_vk_keyboard(VK_KEY_R, WIN); break; // WIN + R
			
			case 500: send_vk_mouse(VK_LBUTTON); break; // LMB
			case 501: send_vk_mouse(VK_MBUTTON); break; // MMB
			case 502: send_vk_mouse(VK_RBUTTON); break; // RMB
			
			case 600: break; // CTRL + 
			case 601: break;
			case 602: break;
		}
		
		Sleep(10);
	}
	
	return 0;
}

























