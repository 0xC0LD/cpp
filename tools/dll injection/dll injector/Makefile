CC = g++
FLAGS = -Wall -static -Os -s main.cpp
EXE = ldll

all: main.cpp 
	$(CC)   $(FLAGS) -o $(EXE)
	$(CC)32 $(FLAGS) -o $(EXE)32
	$(CC)64 $(FLAGS) -o $(EXE)64
	
clean:
	del "*.exe"