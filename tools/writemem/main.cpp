#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <stdint.h>

#define INT2VOIDP(i) (void*)(uintptr_t)(i)

BOOL IsProcessRunning(DWORD& pid)
{
    HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
    DWORD ret = WaitForSingleObject(process, 0);
    CloseHandle(process);
    return ret == WAIT_TIMEOUT;
}

int main(int argc, char* argv[]){
	
	if (argc == 1){
		std::cerr 	<< "error no input" 										<< std::endl
					<< "usage: " << argv[0] << " <PID> <mem_address> <value>"	<< std::endl;
		return 1;
	}
	
	//
	// char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
	// char * pEnd;
	// long int li1, li2, li3, li4;
	// li1 = strtol (szNumbers,&pEnd,10);
	// li2 = strtol (pEnd,&pEnd,16);
	// li3 = strtol (pEnd,&pEnd,2);
	// li4 = strtol (pEnd,NULL,0);
	//
	DWORD pid = atoi(argv[1]);
	int address_ = strtol(argv[2], NULL, 0);
	LPVOID address = INT2VOIDP(address_);
	int newValue = atoi(argv[3]);
	
	std::cout << "PID = " << pid << std::endl;
	std::cout << "adr = " << address_ << " - " << address << std::endl;
	std::cout << "val = " << newValue << std::endl;
	
	if (IsProcessRunning(pid)){ std::cout << "# process found" << std::endl; }
	else { std::cerr << "# process not found" << std::endl; return 1; }
		
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (handle != NULL) { std::cout << "# handle created with OpenProcess()" << std::endl; }
	else { std::cerr << "# failed to create handle with OpenProcess" << std::endl; return 1; }
	
	
	if (WriteProcessMemory(handle, address, &newValue, sizeof(newValue), 0) != 0) { std::cout << "# WriteProcessMemory() successful" << std::endl; }
	else { std::cerr << "# WriteProcessMemory failed" << std::endl; return 1; }

	
	return 0;
}