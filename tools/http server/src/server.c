#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>

#include "server.h"

/* TODO:
**   - make custom 404 pages / and other error codes
**   - multi-threading, thread pools, add other ports and stuff...
**   - handle other requests (UNK, PUT, POST, etc.)
**   - Message body information 
**   - use SSL (HTTPS)
*/

BOOL running = TRUE;
#define RETRY_MS 800

int main() {
	
	tee_init("server.log");
	FILE* recvF = fopen("recv.log", "a");
	
	if (chdir("site")) { tee("[x]: cd 'site'"); return 1; }
	
	while (running) {
		
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR) { tee("ERROR: WSAStartup() failed\n"); }
		
		tee("[>] Server Begin.\n");
		
		while (running) {
			
			// Fill in the address structure
			struct sockaddr_in local;
			local.sin_family      = AF_INET;
			local.sin_addr.s_addr = INADDR_ANY;
			local.sin_port        = htons(DEFAULT_PORT);
			struct sockaddr_in client_addr;
			
			SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
			if (sock == INVALID_SOCKET) { tee("ERROR: socket() failed\n"); continue; }
			if (bind(sock, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR) { tee("ERROR: bind() failed\n");   closesocket(sock); Sleep(RETRY_MS); continue; }
			if (listen(sock, SOMAXCONN) == SOCKET_ERROR)                              { tee("ERROR: listen() failed\n"); closesocket(sock); Sleep(RETRY_MS); continue; }
			
			int count = 0;
			while (running) {
				int addr_len = sizeof(client_addr);
				SOCKET msg_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len);
				if (msg_sock == INVALID_SOCKET) { tee("ERROR: accept() failed\n"); break; }
				
				count++;
				char* ip = inet_ntoa(client_addr.sin_addr);
				u_short port = htons(client_addr.sin_port);
				tee("# %d\t%s:%d", count, ip, port);
				
				REQUEST* request = GetRequest(msg_sock, recvF);
				if (request == NULL) { tee("\n"); closesocket(msg_sock); continue; }
				tee("%s '%s'", request2str(&request->type), request->value);
				
				RESPONSE* response = GetResponse(request);
				if (response == NULL) { tee("\n"); closesocket(msg_sock); continue; }
				int r = SendResponse(msg_sock, response);
				tee("\n");
				
				// clean up
				free(request->value);
				free(request);
				free(response->filepath);
				free(response);
				closesocket(msg_sock);
				
				if (r == SOCKET_ERROR) { break; }
			}
			
			closesocket(sock);
		}
		
		WSACleanup();
	}
	
	tee_shutdown();
	fclose(recvF);
	
}