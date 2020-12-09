CC    = mingw32-gcc
CC32  = i686-w64-mingw32-gcc
CC64  = x86_64-w64-mingw32-gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS = -lwininet
EXE   = exip

all:
	$(CC) $(FLAGS) main.c -o $(EXE) $(LIBS)

clean:
	del "*.exe"