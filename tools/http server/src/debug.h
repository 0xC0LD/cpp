#ifndef DEBUG_H
#define DEBUG_H

// really neat stuff for debugging
#ifdef DEBUG
#	define D(x) x
#else
#	define D(x)
#endif
#define UNUSED(x) (void)(x)
#define DP(x) D(printf("[DEBUG] %s", x))
#define DPL(x) D(printf("[DEBUG] %s\n", x))

// size defs (must be more then size of ping or bugs will happen with recvE)
#define BIGSIZ    8192
#define MIDSIZ    4096
#define KSIZ      1024
#define SMALLSIZ   256

#endif