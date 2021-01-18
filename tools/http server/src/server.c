#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <winsock2.h>

#include "server.h"

/* TODO:
**   - add colors to logging system
**   - make custom 404 pages / and other error codes
**   - multi-threading, thread pools, add other ports and stuff...
**   - handle other requests (UNK, PUT, POST, etc.)
**   - Message body information 
**   - use SSL (HTTPS)
*/

BOOL running = TRUE;

void log_bannerLine() {
	for (int i = 0; i < 100; i++) {
		flog("#");
	}
	flog("\n");
}

#define LOG_IP 1 // log just the ips to another file

char* getTimeStr() {
	time_t now = time(0);
	struct tm* sTm = gmtime(&now);
	char timeStr[TINYSIZ] = {0};
	strftime(timeStr, TINYSIZ, "%Y-%m-%d %H:%M:%S", sTm);
	return strdup(timeStr);
}

int main() {
	
	tee_init("output.log");
	flog_init("server.log");
	
	#if LOG_IP
	FILE* log_ip = fopen("clients.log", "a+");
	#endif
	
	if (chdir("site")) { teeNflog("[x]: cd 'site'"); return 1; }
	
	while (running) {
		
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR) { teeNflog("[X] WSAStartup() failed\n"); }
		
		// get current date and time
		char* tt = getTimeStr();
		teeNflog("%s | [>] Server Begin.\n", tt);
		free(tt);
		
		while (running) {
			
			// Fill in the address structure
			struct sockaddr_in local;
			local.sin_family      = AF_INET;
			local.sin_addr.s_addr = INADDR_ANY;
			local.sin_port        = htons(DEFAULT_PORT);
			struct sockaddr_in client_addr;
			
			SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
			if (sock == INVALID_SOCKET) { tee("[X] socket() failed\n"); continue; }
			if (bind(sock, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR) { teeNflog("[X] bind() failed\n"); closesocket(sock); continue; }
			if (listen(sock, SOMAXCONN) == SOCKET_ERROR) { teeNflog("[X] listen() failed\n"); closesocket(sock); continue; }
			
			// set timeout
			DWORD timeout = SERVER_RECV_TIMEOUT; // 4min timeout
			setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
			
			int count = 0;
			while (running) {
				int addr_len = sizeof(client_addr);
				SOCKET msg_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len);
				if (msg_sock == INVALID_SOCKET) { teeNflog("[X] accept() failed\n"); break; }
				
				// get time
				char* timeStr = getTimeStr();
				
				// count
				count++;
				
				// get ip
				char* ip = inet_ntoa(client_addr.sin_addr);
				u_short port = htons(client_addr.sin_port);
				
				// print stuff
				tee("%s | %d \t %s:%d", timeStr, count, ip, port);
				
				// log ip (no dupes)
				#if LOG_IP
				if (log_ip) {
					fseek(log_ip, 0, SEEK_SET);
					int g = 0;
					char buffer[SMALLSIZ];
					while (fgets(buffer, SMALLSIZ-1, log_ip)) {
						buffer[strcspn(buffer, "\n")] = 0; // remove newline
						if (!strcmp(buffer, ip)) { g = 1; break; }
					}
					if (!g) {
						fseek(log_ip, 0, SEEK_END);
						fprintf(log_ip, "%s\n", ip);
						fflush(log_ip);
					}
				}
				#endif
				
				log_bannerLine();
				flog(">> INDEX.....: %d\n", count);
				flog(">> TIME......: %s\n", timeStr);
				flog(">> IP........: %s\n", ip);
				flog(">> PORT......: %d\n", port);
				
				REQUEST* request = GetRequest(msg_sock);
				if (request == NULL) {
					tee("\n");
					flog(">> REQUEST...: NULL\n");
					log_bannerLine();
					closesocket(msg_sock);
					continue;
				}
				const char* req = request2str(&request->type);
				const char* val = request->value;
				
				tee("%s '%s'", req, val);
				flog(">> REQUEST...: %s\n", req);
				flog(">> VALUE.....: %s\n", val);
				
				
				RESPONSE* response = GetResponse(request);
				if (response == NULL) {
					tee("\n");
					flog(">> RESPONSE..: NULL\n");
					log_bannerLine();
					closesocket(msg_sock);
					continue;
				}
				int r = SendResponse(msg_sock, response);
				tee("\n");
				log_bannerLine();
				
				// clean up
				free(timeStr);
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
	flog_shutdown();
	
}