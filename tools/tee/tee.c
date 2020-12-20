#include <stdio.h>
#include <stdarg.h>

static FILE* tee_file = NULL;
FILE* tee_init(const char* file) {
	tee_file = fopen(file, "a");
	return tee_file;
}

// redirect
//freopen("bdi.log", "a+", stdout); // redirect std to file
//freopen("CON", "w", stdout); // undo
void tee(char const* fmt, ...) { 
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    va_start(ap, fmt);
    vfprintf(tee_file, fmt, ap);
    va_end(ap);
}