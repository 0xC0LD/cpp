#include <stdio.h>
#include <winsock2.h>
#include "server.h"

/*
GET     - The GET method requests a representation of the specified resource. Requests using GET should only retrieve data.
HEAD    - The HEAD method asks for a response identical to that of a GET request, but without the response body.
POST    - The POST method is used to submit an entity to the specified resource, often causing a change in state or side effects on the server.
PUT     - The PUT method replaces all current representations of the target resource with the request payload.
DELETE  - The DELETE method deletes the specified resource.
CONNECT - The CONNECT method establishes a tunnel to the server identified by the target resource.
OPTIONS - The OPTIONS method is used to describe the communication options for the target resource.
TRACE   - The TRACE method performs a message loop-back test along the path to the target resource.
PATCH   - The PATCH method is used to apply partial modifications to a resource. 
*/


int get_request_type(char* buf) {
	char retval[10] = {0};
	sscanf(buf, "%10s", retval);
	if (!strcmp(retval, "GET"))     { return GET;     }
	if (!strcmp(retval, "HEAD"))    { return HEAD;    }
	if (!strcmp(retval, "POST"))    { return POST;    }
	if (!strcmp(retval, "PUT"))     { return PUT;     }
	if (!strcmp(retval, "DELETE"))  { return DELETE;  }
	if (!strcmp(retval, "CONNECT")) { return CONNECT; }
	if (!strcmp(retval, "OPTIONS")) { return OPTIONS; }
	if (!strcmp(retval, "TRACE"))   { return TRACE;   }
	if (!strcmp(retval, "PATCH"))   { return PATCH;   }
	return UNK;
}

const char* request2str(const int* val) {
	switch (*val) {
		case GET:  return "GET";  break;
		case POST: return "POST"; break;
		case PUT:  return "PUT";  break;
	}
	return "UNK";
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
	printf(" -- recv: %d", msg_len);
	
	//printf(" -- msg: \n```\n%s\n```\n", buf);

	if (msg_len == 0) { return NULL; }
	REQUEST* request = malloc(sizeof(REQUEST));
	request->length = msg_len;
	request->type   = get_request_type(buf);
	request->value  = get_request_value(buf);
	return request;
}