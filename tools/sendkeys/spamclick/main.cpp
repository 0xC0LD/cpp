#include <stdio.h>
#include <windows.h>

#define SPAM_DELAY 5

int gl_status1 = 0;
int gl_status2 = 0;

HHOOK mouseHook;
LRESULT __stdcall MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;
    if (key != NULL) {
		switch (key->flags) {
			case 131072: printf("sideButton1: %u\n", wParam); gl_status1 = wParam; return 1; break;
			case 65536:  printf("sideButton2: %u\n", wParam); gl_status2 = wParam; return 1; break;
		}
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

void send_vk_mouse(DWORD flags) {
	INPUT input;
	ZeroMemory(&input, sizeof(input));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = flags;
	SendInput(1, &input, sizeof(INPUT));
}

bool isSpamThreadRunning = false;
DWORD WINAPI SpamThread(void* data) {
	isSpamThreadRunning = true;
	while (isSpamThreadRunning) {
		// down = 523, up = 524
		if (gl_status1 == 523) { send_vk_mouse(MOUSEEVENTF_LEFTDOWN);  send_vk_mouse(MOUSEEVENTF_LEFTUP);  }
		if (gl_status2 == 523) { send_vk_mouse(MOUSEEVENTF_RIGHTDOWN); send_vk_mouse(MOUSEEVENTF_RIGHTUP); }
		Sleep(SPAM_DELAY);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
	// hook
	if (!(mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookCallback, NULL, 0))) { perror("ERROR: failed to install mouse hook\n"); }
	
	// create spam thread
	HANDLE thread = CreateThread(NULL, 0, SpamThread, NULL, 0, NULL);
	if (!thread) { perror("ERROR: failed to create spam click thread\n"); }
	
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
	
	isSpamThreadRunning = false;    // stop spam thread
	UnhookWindowsHookEx(mouseHook); // unhook
    return msg.wParam;
}