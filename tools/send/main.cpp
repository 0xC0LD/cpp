#include <iostream>
#include <fstream>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	if (argc != 4) {
		std::cout << "USAGE: " << argv[0] << " <ip> <port> <file>" << std::endl;
		return 1;
	}
	
	// open file
	std::string filePath = argv[3];
	std::ifstream is(filePath, std::ifstream::binary);
	if (!is) { std::cout << "[-] failed to read file: " << filePath << std::endl; return 1; }
	
	// get length of file:
	is.seekg (0, is.end);
	int length = is.tellg();
	is.seekg (0, is.beg);
	char* buffer = new char[length]; // allocate memory
	is.read(buffer, length); // read data as a block
	is.close();
	
	std::cout << "[+] read: " << length << std::endl;
	
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	// create socket
	SOCKET mySocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);  
	addr.sin_port = htons(atoi(argv[2]));    
	
	// connect, if it fails sleep then retry
	if (WSAConnect(mySocket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
	{ return 1; }
	
	// send file
	int sendRet = send(mySocket, buffer, length, 0);
	if (sendRet == SOCKET_ERROR) { std::cout << "[-] socket error" << std::endl;     } 
	else                         { std::cout << "[+] sent: " << sendRet << std::endl; }
	
	delete[] buffer; // delete buffer
	
	closesocket(mySocket);
	
	WSACleanup();
	
	return 0;
}