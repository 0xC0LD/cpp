#ifndef SERVER_H
#define SERVER_H

typedef struct {
    int  type;
    char* value;
    int length;
} REQUEST;

typedef struct {
    char* header;
    char* filename;
	char* filepath;
    int  error;
} RESPONSE;

#define REQUEST_SIZE 4096
#define DEFAULT_PORT 80

#undef DELETE
enum response_types { UNK, GET, POST, PUT };

extern const char* DEFAULT_ERROR_404;
extern const char* DEFAULT_ERROR_500;

extern char* getcwd(char*, unsigned int);
extern char* get_header(RESPONSE*);
extern REQUEST* GetRequest(SOCKET);
extern RESPONSE* GetResponse(REQUEST*);
extern int SendResponse(SOCKET, RESPONSE*);
extern void print_error(const char*);
extern void print_errorN(const char*);
extern const char* request2str(const int*);

#endif // SERVER_H