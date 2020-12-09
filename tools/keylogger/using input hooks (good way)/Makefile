CC    = mingw32-gcc
CC32  = i686-w64-mingw32-gcc
CC64  = x86_64-w64-mingw32-gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
EXE   = keylog

OBJ = capture.o

all: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) main.c -o $(EXE)
	$(CC) $(FLAGS) $(OBJ) main.c -o $(EXE)h -mwindows

clean:
	del "*.o" "*.exe"