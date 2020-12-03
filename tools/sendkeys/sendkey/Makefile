CC = gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
EXE = sendkey

OBJ = sendkeys.o

all: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) main.c -o $(EXE)

clean:
	del "*.exe"