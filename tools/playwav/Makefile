CC = gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS = -lwinmm
EXE = playwav

all:
	$(CC) $(FLAGS) main.c -o $(EXE) $(LIBS)

clean:
	del "*.exe"