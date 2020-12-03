// get public ip
std::string getExip() {
	
	// get external ip
	HINTERNET net = InternetOpen("external ip retriever", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    HINTERNET conn = InternetOpenUrl(net, "http://myexternalip.com/raw", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    char buf[4096];
    DWORD read;
    InternetReadFile(conn, buf, sizeof(buf)/sizeof(buf[0]), &read);
    InternetCloseHandle(net);
	return std::string(buf, read);
}

// get ascii clipboard text
std::string GetClipboardText() {
	
	// Try opening the clipboard
	if (!OpenClipboard(nullptr)) { return std::string("ERROR: opening clipboard."); }

	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr) { return std::string("ERROR: not ascii text."); }
	
	// Lock the handle to get the actual text pointer
	char * pszText = static_cast<char*>( GlobalLock(hData) );
	if (pszText == nullptr) { return std::string("ERROR: geting text pointer."); }

	
	std::string text(pszText); // Save text in a string class instance
	GlobalUnlock(hData);       // Release the lock
	CloseClipboard();          // Release the clipboard
	
	return text;
}

std::string getCD() { return ("[>] %CD% = " + std::string(getcwd(NULL, 0))); }