#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define INT2VOIDP(i) (void*)(uintptr_t)(i)

BOOL IsProcessRunning(DWORD& pid) {
    HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
    DWORD ret = WaitForSingleObject(process, 0);
    CloseHandle(process);
    return ret == WAIT_TIMEOUT;
}

int main(int argc, char* argv[]){
	
	if (argc == 1) {
		fprintf(stderr, "USAGE: %s <PID> <mem_address> <value>\n", argv[0]);
		return 1;
	}
	
	DWORD pid = atoi(argv[1]);
	int address_ = strtol(argv[2], NULL, 0);
	LPVOID address = INT2VOIDP(address_);
	int newValue = atoi(argv[3]);
	
	printf("PID = %lud\n", pid);
	printf("adr = %d - %d\n", address_, (int)address);
	printf("val = %d\n", newValue);
	
	if (IsProcessRunning(pid)) { printf("# process found\n");                        }
	else                       { fprintf(stderr, "# process not found\n"); return 1; }
		
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (handle != NULL) { printf("# handle created with OpenProcess()\n");                           }
	else                { fprintf(stderr, "# failed to create handle with OpenProcess\n"); return 1; }
	
	
	if (WriteProcessMemory(handle, address, &newValue, sizeof(newValue), 0) != 0) { printf("# WriteProcessMemory() successful");              }
	else                                                                          { fprintf(stderr, "# WriteProcessMemory failed"); return 1; }

	
	return 0;
}