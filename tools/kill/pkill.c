#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>

BOOL TerminateProcessEx(DWORD dwProcessId, UINT uExitCode) {
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
	BOOL  bInheritHandle  = FALSE;
	HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	if (hProcess == NULL) { return FALSE; }
	BOOL result = TerminateProcess(hProcess, uExitCode);
	CloseHandle(hProcess);
	return result;
}

int kill(long unsigned int id) {
	HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (thSnapShot == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "failed to get snapshot handle\n");
		return 0;
	} 
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL retval = Process32First(thSnapShot, &pe);
	int killed = 0;
	int failed = 0;
	while (retval) {
		if (pe.th32ProcessID == id) {
			printf("> %s [%ld]\n", pe.szExeFile, pe.th32ProcessID);
			if (TerminateProcessEx(pe.th32ProcessID, 0)) { killed++; } else { failed++; }
		}
		retval = Process32Next(thSnapShot, &pe);
	}
	
	printf("\n");
	printf("killed: %d\n", killed);
	printf("failed: %d\n", failed);
	CloseHandle(thSnapShot);
	return killed;
}

int main(int argc, char* argv[]) {
	
	if (argc == 1) {
		printf("USAGE: %s <id>\n", argv[0]);
		return 1;
	}
	
	kill(atoi(argv[1]));
	return 0;
}
