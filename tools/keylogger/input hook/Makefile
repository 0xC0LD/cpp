CC = gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
EXE = keylog

OBJ = capture.o

all: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) main.c -o $(EXE)
	$(CC) $(FLAGS) $(OBJ) main.c -o $(EXE)h -mwindows

clean:
	del "*.exe"