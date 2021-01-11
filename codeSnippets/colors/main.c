#include <stdio.h>
#include <windows.h>   // WinApi header

int main() {
	
	// get console handle
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// get color for backup
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	
	// print all colors
	for(int k = 1; k < 255; k++) {
		SetConsoleTextAttribute(hConsole, k); // set color
		printf("%3d ", k);
	}
	
	// reset color
	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
	
	return 0;
}