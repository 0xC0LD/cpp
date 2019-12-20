#include <stdio.h>
#include <conio.h>
#include <shlwapi.h>
#include <tlhelp32.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	
	if (argc != 3) {
		fprintf(stderr, "USAGE: %s <process name | id> <dll>\n", argv[0]);
		return 1;
	}
	
	DWORD pID = NULL;
	const char* input = argv[1];
	
	// check if input is number (id) or process name
	bool isID = true;
	for (int i = 0; i < sizeof(input); i++) {
		if (!isdigit(input[i])) {
			isID = false;
		}
	}
	
	if (isID) {
		pID = atoi(input);
		printf("using id: %lu\n", pID);
	}
	else {
		// retrieve process ID
		HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (thSnapShot == INVALID_HANDLE_VALUE) { fprintf(stderr, "error: unable to create toolhelp snapshot\n"); return false; } 
	
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		
		printf("searching for process: \"%s\"\n", input);
		
		// go through processes and match the name
		BOOL retval = Process32First(thSnapShot, &pe);
		while (retval) {
			if (StrStrI(pe.szExeFile, input)) { printf("found process id: %lu (%s)\n", pe.th32ProcessID, pe.szExeFile); pID = pe.th32ProcessID; }
			retval = Process32Next(thSnapShot, &pe);
		}
		
		if (pID == NULL) {
			fprintf(stderr, "error: process with name: \"%s\" not found\n", input);
			return 1;
		}
	}
	
	
	// get the dll's full path name
	char buf[MAX_PATH] = {0};
	GetFullPathName(argv[2], MAX_PATH, buf, NULL);
	printf("using dll: \"%s\"\n", buf);
	
	
	printf("injecting dll...\n");
	
	char buf2[50] = {0};
	
	HANDLE Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if (!Proc) {
		sprintf(buf2, "error: OpenProcess() failed: %d\n", GetLastError());
		printf(buf2);
		return 1;
	} 
	
	LPVOID LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	
	// Allocate space in the process for our DLL
	LPVOID RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(buf), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
	// Write the string name of our DLL in the memory allocated 
	WriteProcessMemory(Proc, (LPVOID)RemoteString, buf, strlen(buf), NULL);
	
	// Load our DLL
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);
	
	printf("dll injected\n");
	
	CloseHandle(Proc);
	return 0; 
} 

