#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

/* TODO:
**   - handle other requests (UNK, PUT, POST, etc.)
**   - Message body information 
**   - use SSL (HTTPS)
**   - make a linked list of clients (https://www.learn-c.org/en/Linked_lists)
**   - make logging system
**   - make custom 404 pages / and other error codes
**   - multi-threading... add other ports and stuff...
*/

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
        if (sock == INVALID_SOCKET) { print_errorN("socket()"); goto cleanup_goto; }
        if (bind(sock, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR) { print_errorN("bind()"); Sleep(800); goto cleanup_goto; }

        listen_goto:
        if (listen(sock, 5) == SOCKET_ERROR) { print_errorN("listen()"); goto cleanup_goto; }

        printf("[?] waiting for connection...\n");

        int count = 0;
        while (1) {
            int addr_len = sizeof(client_addr);
            SOCKET msg_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len);
            if (msg_sock == INVALID_SOCKET) { print_errorN("accept()"); break; }

            count++;
            char* ip = inet_ntoa(client_addr.sin_addr);
            u_short port = htons(client_addr.sin_port);
            printf("# [%d] %s:%d", count, ip, port);

            REQUEST* request = GetRequest(msg_sock);
            if (request == NULL) { printf("\n"); closesocket(msg_sock); continue; }
            printf(" -> %s '%s'", request2str(&request->type), request->value);

            RESPONSE* response = GetResponse(request);
            if (response == NULL) { printf("\n"); closesocket(msg_sock); continue; }
            int sent = SendResponse(msg_sock, response);
            printf("\n");

            // clean up
            free(request->value);
            free(request);
            free(response->filepath);
            free(response->header);
            free(response);
            closesocket(msg_sock);

            if (sent ==  0) break;
            if (sent == -1) goto listen_goto;
        }

        cleanup_goto:
        closesocket(sock);
        WSACleanup();
    }
}