#include <iostream>
#include <windows.h>
#include <typeinfo>

HHOOK keyboardHook;
HHOOK mouseHook;

// nCode == 0 or HC_ACTION ---> do stuff
// wParam = state, key/mouse down/up
// lParam = struct

int c = 0;

LRESULT __stdcall KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	
	if(nCode == HC_ACTION) {
		
		KBDLLHOOKSTRUCT* k = (KBDLLHOOKSTRUCT*)lParam;
		std::cout << "vkCode   " << k->vkCode   << std::endl;
		std::cout << "scanCode " << k->scanCode << std::endl;
		std::cout << "flags    " << k->flags    << std::endl;
		std::cout << "time     " << k->time     << std::endl;
		
	}

	c++;
	std::cout << ": " << c << std::endl;
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

// source: https://docs.microsoft.com/en-us/windows/win32/inputdev/mouse-input
// WM_LBUTTONDOWN, WM_LBUTTONUP

LRESULT __stdcall MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	
	MOUSEHOOKSTRUCT* m = (MOUSEHOOKSTRUCT*)lParam;
	KBDLLHOOKSTRUCT* k = (KBDLLHOOKSTRUCT*)lParam;
	
	if (k != NULL) {
		std::cout << "vkCode   " << k->vkCode   << std::endl;
		std::cout << "scanCode " << k->scanCode << std::endl;
		std::cout << "flags    " << k->flags    << std::endl;
		std::cout << "time     " << k->time     << std::endl;
		
	}
	
    if (m != NULL) {
		
		std::cout << "(x, y) = (" << m->pt.x << ", " << m->pt.y << ")" << std::endl;
    }
	
	c++;
	std::cout << ": " << c << std::endl;
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

void SetHooks() {
	if (!(keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, NULL, 0))) {
        perror("ERROR: failed to install keyboard hook\n");
    }
	
    if (!(mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookCallback, NULL, 0))) {
        perror("ERROR: failed to install mouse hook\n");
    }
}

void ReleaseHooks() {
	UnhookWindowsHookEx(keyboardHook);
	UnhookWindowsHookEx(mouseHook);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SetHooks();
    MSG msg;
 
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	
    return msg.wParam;
}