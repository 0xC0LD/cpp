// create socket and wait for a connection
SOCKET CreateChildSocket(const SOCKET& mainCallback, int port, DWORD flags) {
	
	std::string port_s = std::to_string(port);
	
	// create socket
	SOCKET listening = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, flags);
	if (listening == INVALID_SOCKET)
	{ echoNsend(mainCallback, "[-] PORT[" + port_s + "] unabel to create socket", true); return INVALID_SOCKET; }
	else
	{ echoNsend(mainCallback, "[+] PORT[" + port_s + "] created socket"); }
	
	// bind socket to ip:port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // could also use inet_pton
	bind(listening, (sockaddr*)&hint, sizeof(hint));
	listen(listening, SOMAXCONN); // tell winsock the socket is for listening
	
	// wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);
	echoNsend(mainCallback, "[*] PORT[" + port_s + "] listening for a connection...");
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize); // wait for connection
	if (clientSocket == INVALID_SOCKET)
	{ echoNsend(mainCallback, "[-] PORT[" + port_s + "] unabel to start listening", true); return INVALID_SOCKET; }

	// get/print client info
	char* ClientIP = inet_ntoa(client.sin_addr);
    int ClientPort = ntohs(client.sin_port);
	echoNsend(mainCallback, "[+] PORT[" + port_s + "] client connected: " + std::string(ClientIP) + ":" + std::to_string(ClientPort));
	
	// close the listening socket
	closesocket(listening);
	
	return clientSocket;
}

int CloseChildSocket(const SOCKET& mainCallback, int port, SOCKET& socket) {
	
	std::string port_s = std::to_string(port);
	
	echoNsend(mainCallback, "[*] PORT[" + port_s + "] closing socket...", true);
	int ret = closesocket(socket);
	echoNsend(mainCallback, "[*] PORT[" + port_s + "] closed socket", true);
	
	return ret;
}