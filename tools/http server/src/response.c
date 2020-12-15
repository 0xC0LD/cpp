#include <stdio.h>
#include <winsock2.h>
#include "server.h"

char* get_full_path(char* name) {
	char filename[1024] = {0};
	getcwd(filename, 1024);
	// replace slashses
	for (int i = 0; name[i]; i++)
		if (name[i] == '/')
			name[i] = '\\';
	
	strcat(filename, name);
	return strdup(filename);
}

RESPONSE* GetResponse(REQUEST* request) {

	RESPONSE* response = malloc(sizeof(RESPONSE));

	if (request->type == GET) {
		response->error    = 0;
		response->filename = request->value;
		response->filepath = get_full_path(request->value);
		response->header   = get_header(response);
		return response;
	}

	if (request->type == POST) { fprintf(stderr, " -- unimplemented request type: POST"); }
	if (request->type == PUT)  { fprintf(stderr, " -- unimplemented request type: PUT"); }
	if (request->type == UNK)  { fprintf(stderr, " -- unknown request"); }

	free(response);
	return NULL;
}

int SendResponse(SOCKET sock, RESPONSE* response) {
	if (response->error) { send(sock, DEFAULT_ERROR_404, strlen(DEFAULT_ERROR_404), 0); return 1; }
	
	FILE* f = fopen(response->filepath, "rb");
	if (!f) { send(sock, DEFAULT_ERROR_500, strlen(DEFAULT_ERROR_500), 0); return 1; }
	
	// send header
	int r = send(sock, response->header, strlen(response->header), 0);
	if (r == SOCKET_ERROR) {
		print_error("send()");
		fprintf(stderr, " -- error sending header, reconnecting...");
		return -1;
	}
	printf(" -- header sent");

	// send data (file)
	char buf[1024] = {0};
	int result = 0;
	while ((result = fread(buf, 1, 1024, f)) > 0) {
		int msg_len = send(sock, buf, result, 0);
		if (msg_len == SOCKET_ERROR) {
			print_error("send()");
			fprintf(stderr, " -- error sending data, reconnecting...");
			return -1;
		}
		else if (!msg_len) { printf(" -- client closed connection"); return 0; }
	}
	
	printf(" -- '%s' sent", response->filepath);
	fclose(f);
	
	return 1;
}