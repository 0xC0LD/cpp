#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {
	if (!OpenClipboard(nullptr)) { fprintf(stderr, "ERROR: failed to open clipboard\n"); return 1; }
	HANDLE hData = GetClipboardData(CF_TEXT);
	
	if (hData == nullptr) { fprintf(stderr, "ERROR: invalid text\n"); return 1; }
	char* pszText = static_cast<char*>(GlobalLock(hData));
	
	if (pszText == nullptr) { fprintf(stderr, "ERROR: failed to get text pointer\n"); return 1; }
	GlobalUnlock(hData);
	CloseClipboard();
	
	printf("%s\n", pszText);
	
	return 0;
}
