CC    = mingw32-gcc
CC32  = i686-w64-mingw32-gcc
CC64  = x86_64-w64-mingw32-gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
EXE   = clipboard

OBJ = cry.o
all: $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) file.c -o cry_file
	$(CC) $(FLAGS) $(OBJ) str.c -o cry_str

clean:
	del "*.o" "*.exe"