CC    = mingw32-gcc
CC32  = i686-w64-mingw32-gcc
CC64  = x86_64-w64-mingw32-gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
LIB   = -lws2_32

all:
	$(CC) $(FLAGS) send.c -o send $(LIB)
	$(CC) $(FLAGS) recv.c -o recv $(LIB)

clean:
	del "*.exe"