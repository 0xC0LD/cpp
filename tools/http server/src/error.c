#include <stdio.h>
#include <stdbool.h>
#include <winsock2.h>
#include "server.h"

void print_ext(const int* code) {
	
	switch (*code) {
		case WSAEADDRINUSE: fprintf(stderr, " -- Address already in use."); break;
	}
	
}

void print_error(const char* s) {
	int code = WSAGetLastError();
	fprintf(stderr, " -- error: %s -> %d", s, code);
	print_ext(&code);
}
void print_errorN(const char* s) {
	int code = WSAGetLastError();
	fprintf(stderr, "# error: %s -> %d", s, code);
	print_ext(&code);
	printf("\n");
}