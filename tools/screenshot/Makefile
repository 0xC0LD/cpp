CC    = mingw32-gcc
CC32  = i686-w64-mingw32-gcc
CC64  = x86_64-w64-mingw32-gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS  = -lgdi32 -lgdiplus
EXE   = ss

all:
	$(CC) $(FLAGS) main.c -o $(EXE) $(LIBS)

clean:
	del "*.exe"