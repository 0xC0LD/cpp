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

const char* request2str(const int* val) {
	switch (*val) {
		case RT_GET:     return "GET";     break;
		case RT_HEAD:    return "HEAD";    break;
		case RT_POST:    return "POST";    break;
		case RT_PUT:     return "PUT";     break;
		case RT_DELETE:  return "DELETE";  break;
		case RT_CONNECT: return "CONNECT"; break;
		case RT_OPTIONS: return "OPTIONS"; break;
		case RT_TRACE:   return "TRACE";   break;
		case RT_PATCH:   return "PATCH";   break;
	}
	return "UNK";
}

REQUEST* GetRequest(SOCKET sock) {
	// get req
	char buf[REQUEST_SIZE] = {0};
	flog(">> Receiving...\n");
	int msg_len = recv(sock, buf, REQUEST_SIZE, 0);
	tee(" -> '%d'b -> ", msg_len);
	flog(">> RECV BUFF.: %d\n", msg_len);
	if (msg_len == 0 || msg_len == SOCKET_ERROR) {
		tee("SOCKET_ERROR");
		return NULL;
	}
	
	// log it
	char buf2[REQUEST_SIZE] = {0};
	int s = 0;
	for (int i = 0; i < REQUEST_SIZE; i++) {
		if (buf[i] == '\r') { continue; }
		buf2[s] = buf[i];
		s++;
	}
	flog("%s", buf2);
	// FILE* f = flog_getFile();
	// fwrite(buf2, msg_len, 1, f);
	// fflush(f);
	
	// make req
	REQUEST* request = malloc(sizeof(REQUEST));
	request->length = msg_len;
	
	// get request
	#define REQBUFFSIZ 10
	char str1[REQBUFFSIZ];
	char str2[MAX_PATH];
	char format[32];
	sprintf(format, "%%%ds %%%ds", REQBUFFSIZ-1, MAX_PATH-1);
	sscanf(buf, format, str1, str2);
	if (str2[strlen(str2)-1] == '/') { strcat(str2, "index.html"); }
	
	enum REQUEST_TYPES type = RT_UNK;
	if      (!strcmp(str1, "GET"))     { type = RT_GET;     }
	else if (!strcmp(str1, "HEAD"))    { type = RT_HEAD;    }
	else if (!strcmp(str1, "POST"))    { type = RT_POST;    }
	else if (!strcmp(str1, "PUT"))     { type = RT_PUT;     }
	else if (!strcmp(str1, "DELETE"))  { type = RT_DELETE;  }
	else if (!strcmp(str1, "CONNECT")) { type = RT_CONNECT; }
	else if (!strcmp(str1, "OPTIONS")) { type = RT_OPTIONS; }
	else if (!strcmp(str1, "TRACE"))   { type = RT_TRACE;   }
	else if (!strcmp(str1, "PATCH"))   { type = RT_PATCH;   }
	
	request->type   = type;
	request->value  = strdup(str2);
	
	return request;
}