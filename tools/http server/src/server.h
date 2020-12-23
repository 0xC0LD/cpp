#ifndef SERVER_H
#define SERVER_H

enum REQUEST_TYPES { RT_UNK, RT_GET, RT_HEAD, RT_POST, RT_PUT, RT_DELETE, RT_CONNECT, RT_OPTIONS, RT_TRACE, RT_PATCH };

typedef struct {
    int  type;
    char* value;
    int length;
} REQUEST;

typedef struct {
	int  error;
    char* filename;
	char* filepath;
} RESPONSE;

#define REQUEST_SIZE 4096
#define DEFAULT_PORT 80

// logging system
#include "tee.h"

extern REQUEST* GetRequest(SOCKET);
extern RESPONSE* GetResponse(REQUEST*);
extern int SendResponse(SOCKET, RESPONSE*);
extern const char* request2str(const int*);
extern void teeNflog(char const*, ...);

#endif // SERVER_H