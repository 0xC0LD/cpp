#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

// TODO: free all string mem allocs

int main() {

    while (1) {
	    WSADATA wsaData;
	    if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR) { print_error("WSAStartup()"); continue; }
	
        // Fill in the address structure
        struct sockaddr_in local;
        local.sin_family      = AF_INET;
        local.sin_addr.s_addr = INADDR_ANY;
        local.sin_port        = htons(DEFAULT_PORT);
        struct sockaddr_in client_addr;
        
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) { print_error("socket()"); goto cleanup_goto; }
        if (bind(sock, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR) { print_error("bind()"); goto cleanup_goto; }

        listen_goto:
        if (listen(sock, 5) == SOCKET_ERROR) { print_error("listen()"); goto cleanup_goto; }

        printf("[?] waiting for connection...\n");

        int count = 0;
        while (1) {
            int addr_len = sizeof(client_addr);
            SOCKET msg_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len);
            if (msg_sock == INVALID_SOCKET) { print_error("accept()"); break; }

            printf("[>] counter: %d\n", ++count);
            printf("[>] client: %s:%d\n", inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port));

            REQUEST* request = GetRequest(msg_sock);
            if (request == NULL) { continue; }
            printf("[>] client requested: %s '%s'\n", request2str(&request->type), request->value);

            RESPONSE* response = GetResponse(request);
            if (response != NULL) { 
                int sent = SendResponse(msg_sock, response);
                if (sent ==  0) break;
                if (sent == -1) goto listen_goto;
            }
            
            closesocket(msg_sock);
        }

        cleanup_goto:
        closesocket(sock);
        WSACleanup();
    }
}