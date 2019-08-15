#include <windows.h>
#include <wininet.h>
#include <string>
#include <iostream>

int main() {
    HINTERNET net = InternetOpen("external ip retriever", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    HINTERNET conn = InternetOpenUrl(net, "http://myexternalip.com/raw", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    char buf[4096];
    DWORD read;
    InternetReadFile(conn, buf, sizeof(buf)/sizeof(buf[0]), &read);
    InternetCloseHandle(net);    
    std::cout << std::string(buf, read) << std::endl;
	return 0;
}