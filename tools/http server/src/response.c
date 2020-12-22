#include <stdio.h>
#include <unistd.h>
#include <winsock2.h>
#include <windows.h>
#include <shlwapi.h>
#include "server.h"

BOOL FileExists(LPCTSTR szPath) {
	DWORD dwAttrib = GetFileAttributes(szPath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

RESPONSE* GetResponse(REQUEST* request) {

	RESPONSE* response = malloc(sizeof(RESPONSE));

	switch (request->type) {
		case RT_GET: {
			response->error    = 200;
			response->filename = request->value;
			// get cwd
			char CWD[MAX_PATH] = {0};
			getcwd(CWD, MAX_PATH-1);
			// append req to cwd
			char REQ[MAX_PATH] = {0};
			strcat(REQ, CWD);
			strcat(REQ, request->value);
			// get full file path
			char FullFilePath[MAX_PATH] = {0};
			TCHAR** lppPart = {NULL};
			GetFullPathNameA(REQ, MAX_PATH, FullFilePath, lppPart);
			response->filepath = strdup(FullFilePath);
			return response;
			break;
		}
		case RT_HEAD:    tee(" -- unimplemented request type: HEAD");    break;
		case RT_POST:    tee(" -- unimplemented request type: POST");    break;
		case RT_PUT:     tee(" -- unimplemented request type: PUT");     break;
		case RT_DELETE:  tee(" -- unimplemented request type: DELETE");  break;
		case RT_CONNECT: tee(" -- unimplemented request type: CONNECT"); break;
		case RT_OPTIONS: tee(" -- unimplemented request type: OPTIONS"); break;
		case RT_TRACE:   tee(" -- unimplemented request type: TRACE");   break;
		case RT_PATCH:   tee(" -- unimplemented request type: PATCH");   break;
		
		case RT_UNK:
		default: tee(" -- unknown request"); break;
	}
	
	return NULL;
}


char* get_content_type(const char* name) {
    char* extension = strchr(name, '.');
    if      (!strcmp(extension, ".html")) { return "text/html";       }
    else if (!strcmp(extension, ".ico"))  { return "image/webp";      }
    else if (!strcmp(extension, ".css"))  { return "text/css";        }
    else if (!strcmp(extension, ".jpg"))  { return "image/jpeg";      }
    else if (!strcmp(extension, ".js"))   { return "text/javascript"; }
    return "*/*";
}

const char* DEFAULT_ERROR_403 = "HTTP/1.1 403 Forbidden\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>403 Forbidden</title></head><body><h1>Forbidden</h1>The requested URL is forbidden.</body></html>";
const char* DEFAULT_ERROR_404 = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>404 Not Found</title></head><body><h1>Not Found</h1>The requested URL was not found on this server.</body></html>";
const char* DEFAULT_ERROR_500 = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";

int SendDefHeader(SOCKET sock, int code) {
	
	int ret = 0;
	tee(" -> ");
	switch (code) {
		case 403: ret = send(sock, DEFAULT_ERROR_403, strlen(DEFAULT_ERROR_403), 0); break;
		case 404: ret = send(sock, DEFAULT_ERROR_404, strlen(DEFAULT_ERROR_404), 0); break;
		case 500: ret = send(sock, DEFAULT_ERROR_500, strlen(DEFAULT_ERROR_500), 0); break;
	}
	tee("%d", code);
	
	return ret;
}

int SendResponse(SOCKET sock, RESPONSE* response) {
	
	/// stuff to test
	// test if file exists
	if (!FileExists(response->filepath)) { return SendDefHeader(sock, 404); }
	
	// test if file is in cwd
	char CWD[MAX_PATH] = {0};
	getcwd(CWD, MAX_PATH-1);
	if (!StrStrI(response->filepath, CWD)) { return SendDefHeader(sock, 403); }
	
	FILE* f = fopen(response->filepath, "rb");
	if (!f) { return SendDefHeader(sock, 500); }
	
	// 200 header
	char header[1024];
	sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", get_content_type(response->filename));
	
	tee(" -> ");
	int s = send(sock, header, strlen(header), 0);
	if (s == SOCKET_ERROR) { return s; }
	tee("200");
	
	// send data (file)
	char buf[1024] = {0};
	int result = 0;
	while ((result = fread(buf, 1, 1024, f)) > 0) {
		int msg_len = send(sock, buf, result, 0);
		if (msg_len == SOCKET_ERROR || msg_len == 0) {
			fclose(f);
			tee(" -- reset");
			return SOCKET_ERROR;
		}
	}
	fclose(f);
	
	tee(" -> sent: '%s'", response->filepath);
	return 1;
}