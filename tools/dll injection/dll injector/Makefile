CC    = mingw32-gcc
CC32  = i686-w64-mingw32-gcc
CC64  = x86_64-w64-mingw32-gcc
FLAGS = -Wall -static -Os -s main.c
EXE = ldll

all: main.c 
	$(CC)   $(FLAGS) -o $(EXE)
	$(CC32) $(FLAGS) -o $(EXE)32
	$(CC64) $(FLAGS) -o $(EXE)64
	
clean:
	del "*.exe"