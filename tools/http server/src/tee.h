#ifndef TEE_H
#define TEE_H

extern FILE* tee_init(const char*);
extern int tee_shutdown();
extern void tee(char const*, ...);

#endif