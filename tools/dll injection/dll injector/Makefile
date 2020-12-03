CC = gcc
FLAGS = -Wall -static -Os -s main.c
EXE = ldll

all: main.c 
	$(CC)   $(FLAGS) -o $(EXE)
	$(CC)32 $(FLAGS) -o $(EXE)32
	$(CC)64 $(FLAGS) -o $(EXE)64
	
clean:
	del "*.exe"