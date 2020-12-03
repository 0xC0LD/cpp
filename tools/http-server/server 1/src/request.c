#include <winsock2.h>
#include <stdio.h>
#include "server.h"

int get_request_type(char* buf) {
	char retval[10] = {0};
	sscanf(buf, "%10s", retval);
	if (!strcmp(retval, "GET"))  { return GET;  }
	if (!strcmp(retval, "POST")) { return POST; }
	if (!strcmp(retval, "PUT"))  { return PUT;  }
	return UNK;
}

const char* request2str(const int* val) {
	switch (*val) {
		case GET:  return "GET";  break;
		case POST: return "POST"; break;
		case PUT:  return "PUT";  break;
		case UNK:  return "UNK";  break;
	}
	return "";
}

char* get_request_value(char* buf) {
	char retval[100] = {0};
	strtok(buf, " "); // 1st str token
	char* ptr2 = strtok(NULL, " "); // 2nd string token
	if (ptr2 == NULL) { return ""; } // client didn't request anything
	sscanf(ptr2, "%100s", retval); // move 2nd word to buf
	if (retval[strlen(retval)-1] == '/') { strcat(retval, "index.html"); }
	return strdup(retval);
}

REQUEST* GetRequest(SOCKET sock) {
	char buf[REQUEST_SIZE] = {0};
	int msg_len = recv(sock, buf, REQUEST_SIZE, 0);
	printf("[>] recv: %d\n", msg_len);

	#if PRINT_MESSAGE
	printf("[>] msg: \n```\n%s\n```\n", buf);
	#endif

	if (msg_len == 0) { return NULL; }
	REQUEST* request = malloc(sizeof(REQUEST));
	request->length = msg_len;
	request->type   = get_request_type(buf);
	request->value  = get_request_value(buf);
	return request;
}