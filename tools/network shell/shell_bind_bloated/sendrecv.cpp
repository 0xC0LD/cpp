int sendFile(SOCKET* mainCallback, std::string filePath, bool deleteFile = false) {
	
	// open file
	std::ifstream is(filePath.c_str(), std::ifstream::binary);
	if (!is) { echoNsend(*mainCallback, "[-] failed to read file: " + filePath, true); return 1; }
	
	// get length of file:
	is.seekg (0, is.end);
	int length = is.tellg();
	is.seekg (0, is.beg);
	char* buffer = new char[length]; // allocate memory
	is.read(buffer, length); // read data as a block
	is.close();
	
	echoNsend(*mainCallback, "[+] read " + std::to_string(length) + " bytes");
	
	SOCKET clientSocket = CreateChildSocket(*mainCallback, PORT_SEND, WSA_FLAG_OVERLAPPED);
	if (clientSocket == INVALID_SOCKET) { return 1; }
	
	// send file
	int sendRet = send(clientSocket, buffer, length, 0);
	if (sendRet == SOCKET_ERROR) { echoNsend(*mainCallback, "[-] socket error", true);                         } 
	else                         { echoNsend(*mainCallback, "[+] sent " + std::to_string(sendRet) + " bytes"); }
	
	delete[] buffer; // delete buffer
	
	if (deleteFile) { remove(filePath.c_str()); }
	
	CloseChildSocket(*mainCallback, PORT_SEND, clientSocket); // close connection
	return 0;
}

bool recvFile_running = true;
int recvFile(SOCKET* mainCallback, std::string filePath) {
	
	SOCKET clientSocket = CreateChildSocket(*mainCallback, PORT_RECV, WSA_FLAG_OVERLAPPED);
	if (clientSocket == INVALID_SOCKET) { return 1; }
	
	char* buffer = new char[BIGSIZ];
	size_t bytesReceived = 0;
	int recv_count = 0;
	recvFile_running = true;
	
	std::thread t1([&mainCallback, &bytesReceived, &recv_count](){
		
		while (recvFile_running) {
			echoNsend(*mainCallback, "\r[+] recv: " + std::to_string(bytesReceived) + " (" + std::to_string(recv_count) + ")", false, false);
			Sleep(250);
		}
		
	});
	t1.detach();
	
	std::ofstream of(filePath.c_str(), std::ofstream::binary);
	while (true) {
		
		int ret = recv(clientSocket, buffer, BIGSIZ, 0);
		recv_count++;
		bytesReceived += ret;
		
		if (ret <= 0) { break; } // stop recv on client disconnect
		if (ret == SOCKET_ERROR) { echo("[-] recv error: " + std::to_string(WSAGetLastError())); break; }
		
		// write to file
		of.write(buffer, ret);
	}
	
	recvFile_running = false;
	
	echoNsend(*mainCallback, "\n[+] total: " + std::to_string(bytesReceived) + " (" + std::to_string(recv_count) + ")");
	
	delete[] buffer;
	of.close();
	
	CloseChildSocket(*mainCallback, PORT_RECV, clientSocket); // close connection
	
	return 0;
}