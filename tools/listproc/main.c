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


int main() {
	
	HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (thSnapShot == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "failed to get snapshot handle\n");
		return 0;
	} 
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL retval = Process32First(thSnapShot, &pe);
	while (retval) {
		printf("%ld : %s\n", pe.th32ProcessID, pe.szExeFile);
		retval = Process32Next(thSnapShot, &pe);
	}
	
	CloseHandle(thSnapShot);
	
	return 0;
}
