#include <winsock2.h>
#include <stdio.h>
#include "server.h"

void print_error(const char *s) { fprintf(stderr, "[X] error: %s -> %d\n", s, WSAGetLastError()); }