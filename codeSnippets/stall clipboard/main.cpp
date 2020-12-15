#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {
	
	// open clipboard (prevents other programs from using the clipboard)
	OpenClipboard(NULL);
	getch();
	
	return 0;
}