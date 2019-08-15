#include "main.h"

DWORD WINAPI HackThread(HMODULE hModule) {
	
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	
	std::cout << "DLL PAYLOAD STARTED" << std::endl;
	
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle("program.exe");
	// uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x10f4f4);
	// *(int*)(*localPlayerPtr + 0xf8) = 1337;
	
	while(true) {
		Sleep(10);
		
		//A
		if (GetAsyncKeyState(65) & 1) {
			int* w = (int*)0x71febc;
			*w = 10000;
		}
		if (GetAsyncKeyState(VK_END) & 1) { break; }
	}
	
	
	//cleanup & eject
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	
	return 0;
}




BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {

	if (fdwReason == DLL_PROCESS_ATTACH) {
		
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
		
	}

	return 1;
}

//MessageBox(NULL, "DLL_PROCESS_ATTACH", "DLL_PROCESS_ATTACH", MB_ICONERROR | MB_OK);