#include <iostream>
#include <conio.h>
#include <windows.h>

int main() {
	
	if (!OpenClipboard(nullptr)) { std::cerr << "ERROR: failed to open clipboard"   << std::endl; }
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr)        { std::cerr << "ERROR: invalid text"               << std::endl; }
	char* pszText = static_cast<char*>(GlobalLock(hData));
	if (pszText == nullptr)      { std::cerr << "ERROR: failed to get text pointer" << std::endl; }
	
	std::string text(pszText);
	GlobalUnlock(hData);
	CloseClipboard();
	
	std::cout << text << std::endl;
	
	return 0;
}