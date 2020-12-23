#include <stdio.h>
#include <stdarg.h>
#include <winsock2.h>
#include "server.h"

void teeNflog(char const* fmt, ...) { 
    va_list ap;
    va_start(ap, fmt);
	tee(fmt, ap);
	flog(fmt, ap);
    va_end(ap);
}