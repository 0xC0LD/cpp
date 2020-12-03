CC = gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS = -lwininet
EXE = exip

all:
	$(CC) $(FLAGS) main.c -o $(EXE) $(LIBS)

clean:
	del "*.exe"